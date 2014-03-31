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
    get_position
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
    Cursor cursor(int row, int col);
    Cursor cursor();
    void reset();

// Low-level methods that are not commonly used
public:
    bool activate();
    int write(const std::string& data);
    int write(TerminalCode code);
    int read();

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
