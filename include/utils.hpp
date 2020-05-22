#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

namespace utils {

    std::vector<std::byte> load_file_to_bytes(std::string const& filepath);

    // Original version: https://mklimenko.github.io/english/2018/08/22/robust-endian-swap/
    template<typename T>
    void swap_endian(T &val) {
        union U {
            T val;
            std::array<std::byte, sizeof(T)> raw;
        } src, dst;

        src.val = val;
        std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
        val = dst.val;
    }

    bool is_big_endian();

    bool is_little_endian();

}
