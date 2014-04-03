#ifndef ROTIDE_SYS_CONIO_HPP
#define ROTIDE_SYS_CONIO_HPP

#include <termios.h>
#include <vector>
#include <string>
#include <memory>

#include <rotide/sys/unicode.hpp>

namespace ro {

enum TerminalError {
    rd_eof = -1,
    rd_eio = -2
};

enum class TerminalCode {
    reset,
    cursor_get_position,
    cursor_set_position,
    cursor_up,
    cursor_down,
    cursor_forward,
    cursor_back,
    cursor_next_line,
    cursor_prev_line,
    cursor_set_col,
};

enum class TerminalMovement {
    absolute,
    relative
};

struct Cursor {
    Cursor(int row, int col) : row(row), col(col) {}
    int row, col;
};

class Terminal {

// High-level utility and common methods
public:
    Terminal();
    Cursor cursor(int row, int col);
    Cursor cursor();
    void cursor_forward(int cols);
    void cursor_back(int cols);
    void cursor_up(int rows);
    void cursor_down(int rows);
    void reset();
    Unicode getch();

// Low-level methods that are not commonly used
public:
    bool activate();
    int write(char c);
    int write(const std::string& data);
    int write(const Unicode& unicode);
    int write(TerminalCode code);
    int write(TerminalCode code, int arg1);
    int write(TerminalCode code, int arg1, int arg2);
    void force_write_delay(int time) { delay = time; }
    int read();
    Unicode read_wchar();

// Utilities for state preservation
public:
    bool apply_termios(termios state);
    termios push_state();
    termios pop_state();

public:
    std::vector<termios> term_stack;
    int tty;
    int delay;
};

}

#endif // ROTIDE_SYS_CONIO_HPP
