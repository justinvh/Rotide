#define _XOPEN_SOURCE_EXTENDED 1

#include <locale.h>
#include <ncursesw/ncurses.h>

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
        wchar_t c;
        cchar_t t;

        get_wch(&c);
        setcchar(&t, &c, 0, COLOR_PAIR(3), NULL);

        if (mode == INSERT) {
            add_wch(&t);
        } else if (mode == NORMAL) {
        }

        refresh();
    }

    endwin();

    return 0;
}
