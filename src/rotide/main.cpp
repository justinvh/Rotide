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

    ro::Terminal terminal;

    while (true) {
        std::cout << terminal.getch() << std::endl;
    };
}
