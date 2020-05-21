#include "utils.hpp"

#include <cstring>
#include <fstream>

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

}