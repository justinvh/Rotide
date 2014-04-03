#include <iostream>
#include <locale>
#include <clocale>
#include <cwchar>

#include <rotide/sys/terminal.hpp>

int main()
{

    std::setlocale(LC_ALL, "");
    std::cout << "LC_ALL: " << std::setlocale(LC_ALL, NULL) << std::endl;
    std::cout << "LC_CTYPE: " << std::setlocale(LC_CTYPE, NULL) << std::endl;

    int mode = 0;
    char esc = 0x1b;
    ro::Terminal terminal;
    terminal.reset();
    terminal.write("\033[?25h");

    while (true) {
        ro::Unicode ch = terminal.getch();

        if (ch == esc) {
            mode = !mode;
            continue;
        }

        if (mode == 0) {
            if (ch == 'j') {
                terminal.cursor_down(1);
            } else if (ch == 'k') {
                terminal.cursor_up(1);
            } else if (ch == 'h') {
                terminal.cursor_back(1);
            } else if (ch == 'l') {
                terminal.cursor_forward(1);
            }
            continue;
        }

        terminal.write(ch);
    };
}
