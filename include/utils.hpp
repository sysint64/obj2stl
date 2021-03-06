#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <glm/glm.hpp>

#include "mesh.hpp"

namespace utils {

    constexpr double pi = 3.14159265358979323846;

    std::vector<std::string> load_text_file_lines(std::string const& filepath);

    std::vector<std::string> split(std::string const& src, char delimiter);

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

    glm::vec3 calculate_normal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    glm::vec3 calculate_normal(mesh::Triangle const& triangle);

}
