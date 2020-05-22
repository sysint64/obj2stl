#include "utils.hpp"

#include <cstring>
#include <fstream>
#include <sstream>

namespace utils {

    std::vector<std::byte> load_file_to_bytes(std::string const& filepath) {
        std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);

        if (!ifs) {
            throw std::runtime_error(filepath + ": " + std::strerror(errno));
        }

        const auto end = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        const auto size = std::size_t(end - ifs.tellg());

        if (size == 0) {
            return {};
        }

        std::vector<std::byte> buffer(size);
        auto data = reinterpret_cast<char*>(buffer.data());

        if (!ifs.read(data, buffer.size())) {
            throw std::runtime_error(filepath + ": " + std::strerror(errno));
        }

        return buffer;
    }

    std::vector<std::string> load_text_file_lines(std::string const& filepath) {
        std::vector<std::string> lines;
        std::ifstream ifs(filepath);

        for (std::string line; std::getline(ifs, line); ) {
            lines.push_back(line);
        }

        return lines;
    }

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

    std::vector<std::string> split(std::string const& src, char delimeter) {
        std::stringstream test(src);
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(test, segment, delimeter)) {
            seglist.push_back(segment);
        }

        return seglist;
    }
}
