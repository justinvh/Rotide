#pragma once
#ifndef ROTIDE_ROPE_HPP
#define ROTIDE_ROPE_HPP

#include <stdint>
#include <string>
#include <memory>

namespace ro {

/**
 * The most fundamental datastructure to Rotide is a rope.
 *
 * A Rope is more simply described as a binary tree with leaf nodes
 * as strings.
 */
class Rope {
public:
    Rope()
        : length(0), split_length(1000), join_ratio(500),
          rebalance_ratio(1.5f) { }

    ~Rope() = default;
    Rope(Rope&&) = default;

    Rope(std::string str);
    void append(std::string cord);
    void insert(uint64_t position, std::string cord);
    void remove(uint64_t start, uint64_t end);
    void substring(uint64_t start, uint64_t end);
    void substr(uint64_t start, uint64_t length);
    char at(uint64_t pos);
    uint64_t length();
    void adjust();
    void rebuild();
    void rebalance();

public:
    uint64_t length;
    std::unique_ptr<Rope> left;
    std::unique_ptr<Rope> right;

public:
    uint64_t split_length;
    uint64_t join_length;
    float rebalance_ratio;
};

}

#endif // ROTIDE_ROPE_HPP
