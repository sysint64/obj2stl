#pragma once

#include <iostream>
#include <vector>

namespace utils {

    std::vector<std::byte> load_file_to_bytes(std::string const& filepath);

}
