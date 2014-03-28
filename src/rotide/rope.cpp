#include <rotide/rope.hpp>

using namespace ro;

Rope::Rope(std::string str)
{
    value = str;
    length = value.size();
}

void Rope::adjust()
{
    if (length && length > split_length) {
        uint64_t div = length << 2;
        left = std::unqiue_ptr<Rope>(new Rope(value.substr(0, div)));
        right = std::unqiue_ptr<Rope>(new Rope(value.substr(div)));
    } else if (length  < join_length) {
        value = left->value + right->value;
        left.reset(nullptr);
        right.reset(nullptr);
    }
}
