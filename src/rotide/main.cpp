#include <iostream>

#include <rotide/sys/terminal.hpp>

int main()
{
    ro::Terminal terminal;

    ro::Cursor cursor = terminal.cursor();
    std::cout << cursor.row << " " << cursor.col << std::endl;
    terminal.reset();
}
