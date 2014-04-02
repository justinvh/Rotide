#ifndef ROTIDE_SYS_UNICODE_HPP
#define ROTIDE_SYS_UNICODE_HPP

#include <cstdlib>

namespace ro {

enum class UnicodeType {
    ASCII,
    UTF8
};

class Unicode {
public:
    Unicode()
    {
        data = (char*) calloc(5, sizeof(char));
        type = UnicodeType::ASCII;
    }

    char& operator[](size_t i)
    {
        if (i > 0) {
            type = UnicodeType::UTF8;
        }

        return data[i];
    }

    UnicodeType type;
    char* data;
};

}

inline
std::ostream& operator<<(std::ostream& os, const ro::Unicode& unicode)
{
    return os << unicode.data;
}

#endif // ROTIDE_SYS_UNICODE_HPP
