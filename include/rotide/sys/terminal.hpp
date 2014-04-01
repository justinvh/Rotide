#ifndef ROTIDE_SYS_CONIO_HPP
#define ROTIDE_SYS_CONIO_HPP

#include <termios.h>
#include <vector>
#include <string>

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
    char32_t getch();

// Low-level methods that are not commonly used
public:
    bool activate();
    int write(const std::string& data);
    int write(TerminalCode code);
    int write(TerminalCode code, int arg1);
    int write(TerminalCode code, int arg1, int arg2);
    int read();
    char32_t read_wchar();

// Utilities for state preservation
public:
    bool apply_termios(termios state);
    termios push_state();
    termios pop_state();

public:
    std::vector<termios> term_stack;
    int tty;
};

}

#endif // ROTIDE_SYS_CONIO_HPP
