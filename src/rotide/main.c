#include <locale.h>
#include <curses.h>
#include <ncurses.h>

enum Mode {
    NORMAL,
    INSERT
};

int main(int argc, char** argv)
{
    enum Mode mode = INSERT;

    setlocale(LC_ALL, "en_US.UTF-8");

    initscr();
    keypad(initscr(), 1);
    curs_set(9);
    nonl();
    noecho();
    cbreak();

    while (1) {
        int c = get_wch();

        if (mode == INSERT) {
            printw("%c", c);
        } else if (mode == NORMAL) {
        }

        refresh();
    }

    endwin();

    return 0;
}
