#include "utils.hpp"

#include <iterator>
#include <fstream>
#include <sstream>

namespace utils {

    std::vector<std::string> load_text_file_lines(std::string const& filepath) {
        std::vector<std::string> lines;

        std::ifstream ifs;
        ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        ifs.open(filepath);

        std::string line;

        while (ifs.peek() != EOF && std::getline(ifs, line)) {
            lines.push_back(line);
        }

        return std::move(lines);
    }

    // https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program
    bool is_big_endian() {
        union {
            uint32_t i;
            char c[4];
        } bint = {0x01020304};

        return bint.c[0] == 1;
    }

    bool is_little_endian() {
        return !is_big_endian();
    }

    glm::vec3 calculate_normal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
        auto dir = glm::cross(v2 - v1, v3 - v1);
        return glm::normalize(dir);
    }

    glm::vec3 calculate_normal(mesh::Triangle const& triangle) {
        return calculate_normal(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
    }

    std::vector<std::string> split(std::string const& src, char delimiter) {
        std::stringstream test(src);
        std::string segment;
        std::vector<std::string> seg_list;

        while (std::getline(test, segment, delimiter)) {
            seg_list.push_back(segment);
        }

        return seg_list;
    }
}
