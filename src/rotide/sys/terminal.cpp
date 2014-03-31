#include <map>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <rotide/sys/terminal.hpp>

namespace ro {

Cursor Terminal::cursor(int row, int col)
{
    return Cursor(0, 0);
}

Cursor Terminal::cursor()
{
    int retval, result, rows, cols, saved_errno;

    if (tty == -1) {
        return Cursor(-1, -1);
    }

    termios temporary = push_state();

    do {

        if (!apply_termios(temporary)) {
            break;
        }

        // Request cursor coordinates from the terminal.
        retval = write(TerminalCode::get_position);
        if (retval) {
            break;
        }

        // Assume coordinate reponse parsing fails.
        retval = EIO;

        // Expect an ESC.
        result = read();
        if (result != 27) {
            break;
        }

        // Expect [ after the ESC.
        result = read();
        if (result != '[') {
            break;
        }

        // Parse rows.
        rows = 0;
        result = read();
        while (result >= '0' && result <= '9') {
            rows = 10 * rows + result - '0';
            result = read();
        }

        if (result != ';') {
            break;
        }

        // Parse cols.
        cols = 0;
        result = read();
        while (result >= '0' && result <= '9') {
            cols = 10 * cols + result - '0';
            result = read();
        }

        if (result != 'R') {
            break;
        }

        retval = 0;

    } while (false);

    temporary = pop_state();
    apply_termios(temporary);

    return Cursor(rows, cols);
}

int Terminal::read()
{
    unsigned char buffer[4];
    ssize_t n;

    while (1) {
        n = ::read(tty, buffer, 1);
        if (n > (ssize_t) 0) {
            return buffer[0];
        } else if (n == (ssize_t) 0) {
            return rd_eof;
        } else if (n != (ssize_t) -1) {
            return rd_eio;
        } else if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK) {
            return rd_eio;
        }
    }
}

int Terminal::write(TerminalCode code)
{
    if (code == TerminalCode::reset) {
        return write("\033c");
    } else if (code == TerminalCode::get_position) {
        return write("\033[6n");
    } else {
        return -1;
    }
}

int Terminal::write(const std::string& data)
{
    const char* head = data.c_str();
    const char* const tail = head + data.size();
    ssize_t n;

    while (head < tail) {
        n = ::write(tty, head, (size_t)(tail - head));
        if (n > (ssize_t) 0) {
            head += n;
        } else if (n != (ssize_t) -1) {
            return EIO;
        } else if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK) {
            return errno;
        }
    }

    return 0;
}

bool Terminal::activate()
{
    const char* dev;

    dev = ttyname(STDIN_FILENO);
    if (!dev) {
        dev = ttyname(STDOUT_FILENO);
    }

    if (!dev) {
        dev = ttyname(STDERR_FILENO);
    }

    if (!dev) {
        errno = ENOTTY;
        return false;
    }

    do {
        tty = open(dev, O_RDWR | O_NOCTTY);
    } while (tty == -1 && errno == EINTR);

    return tty != -1;
}

void Terminal::reset()
{
    write(TerminalCode::reset);
}

bool Terminal::apply_termios(termios state)
{
    int result;

    do {
        result = tcsetattr(tty, TCSANOW, &state);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        return false;
    }

    return true;
}

termios Terminal::push_state()
{
    int result, saved_errno = errno;
    termios saved, temporary;

    // Save current terminal settings.
    do {
        result = tcgetattr(tty, &saved);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        errno = saved_errno;
        return saved;
    }

    term_stack.push_back(saved);

    // Get current terminal settings for basis, too.
    do {
        result = tcgetattr(tty, &temporary);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        errno = saved_errno;
        return saved;
    }

    // Disable ICANON, ECHO, and CREAD.
    temporary.c_lflag &= ~ICANON;
    temporary.c_lflag &= ~ECHO;
    temporary.c_cflag &= ~CREAD;

    return temporary;
}

termios Terminal::pop_state()
{
    termios state = term_stack.back();
    term_stack.pop_back();
    return state;
}

}
