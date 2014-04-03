#include <rotide/sys/terminal.hpp>

int main()
{
    ro::Terminal terminal;

    terminal.reset();
    terminal.write("\033[?25h");
    terminal.force_write_delay(10);

    int w = 24, h = 8;

    while (true) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                terminal.cursor_forward(1);
            }

            terminal.cursor_down(1);

            for (int j = 0; j < w; j++) {
                terminal.cursor_back(1);
            }

            terminal.cursor_down(1);
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                terminal.cursor_forward(1);
            }

            terminal.cursor_up(1);

            for (int j = 0; j < w; j++) {
                terminal.cursor_back(1);
            }

            terminal.cursor_up(1);
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                terminal.write('#');
            }

            terminal.cursor_down(1);

            for (int j = 0; j < w; j++) {
                terminal.write('#');
                terminal.cursor_back(2);
            }

            terminal.cursor_down(1);
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                terminal.write(' ');
            }

            terminal.cursor_up(1);

            for (int j = 0; j < w; j++) {
                terminal.write(' ');
                terminal.cursor_back(2);
            }

            terminal.cursor_up(1);
        }

        for (int j = 0; j < w; j++) {
            terminal.write(' ');
        }

        terminal.cursor_back(w);
    }

    return 0;
}
