#include <iostream>
#include <locale>
#include <clocale>
#include <cwchar>

#include <rotide/sys/terminal.hpp>

int main()
{
    std::setlocale(LC_ALL, "en_US.UTF-8");

    ro::Terminal terminal;

    while (true) {
        char c = terminal.getch();
        std::cout << c;
        std::cout.flush();
    };
}
