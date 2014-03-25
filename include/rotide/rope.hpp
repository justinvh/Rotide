#pragma once
#ifndef ROTIDE_ROPE_HPP
#define ROTIDE_ROPE_HPP

#include <stdint>
#include <string>

namespace ro {

/**
 * The most fundamental datastructure to Rotide is a rope.
 *
 * A Rope is more simply described as a binary tree with leaf nodes
 * as strings.
 */
class Rope {
    void append(std::string cord);
    void insert(uint64_t position, std::string cord);
    void remove(uint64_t start, uint64_t end);
    void substring(uint64_t start, uint64_t end);
    void substr(uint64_t start, uint64_t length);
    char at(uint64_t pos);
    uint64_t length();
    void rebuild();
    void rebalance();
};

}

#endif // ROTIDE_ROPE_HPP
