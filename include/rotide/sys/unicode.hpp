#ifndef ROTIDE_SYS_UNICODE_HPP
#define ROTIDE_SYS_UNICODE_HPP

#include <cstdlib>
#include <iostream>
#include <vector>

namespace ro {

enum class UnicodeType {
    ASCII,
    UTF8
};

class Unicode {
public:
    Unicode()
        : type(UnicodeType::ASCII)
    {
        data = (char*) calloc(5, sizeof(char));
    };

    Unicode(const Unicode& rhs)
    {
        data = (char*) calloc(5, sizeof(char));
        memcpy(data, rhs.data, sizeof(char) * 5);
        type = rhs.type;
    }

    Unicode(Unicode&& rhs)
    {
        data = rhs.data;
        type = rhs.type;
        rhs.data = nullptr;
    }

    ~Unicode()
    {
        if (data != nullptr) {
            free(data);
        }
    }

    bool operator==(char k)
    {
        if (type == UnicodeType::UTF8)
            return false;
        return data[0] == k;
    }

    bool operator==(Unicode k)
    {
        if (type != UnicodeType::ASCII)
            return false;

        return (data[0] = k.data[0] &&
                data[1] == k.data[1] &&
                data[2] == k.data[2] &&
                data[3] == k.data[3]);
    }

    char& operator[](size_t i)
    {
        if (i > 0) {
            type = UnicodeType::UTF8;
        }

        return data[i];
    }

public:
    UnicodeType type;
    char* data;
};

typedef std::vector<Unicode> UnicodeString;

}

inline
std::ostream& operator<<(std::ostream& os, const ro::Unicode& unicode)
{
    return os << unicode.data;
}

inline
std::ostream& operator<<(std::ostream& os, const ro::UnicodeString& str)
{
    for (auto unicode : str) {
        os << unicode;
    }

    return os;
}

#endif // ROTIDE_SYS_UNICODE_HPP
