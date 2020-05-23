#include <obj.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "vendor/cxxopts.hpp"
#include "stl.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

static void save_to_stl(std::vector<char> const& out_bytes, std::string const& output);

static void convert_from_obj_to_stl(std::string const& input, std::string const& output) {
    try {
        auto lines = utils::load_text_file_lines(input);
        auto obj = obj_file::load_from_string_lines(lines);
        auto layout = obj_file::create_mesh_layout_from_obj(obj);
        auto writer = std::make_unique<stl_file::StlMeshWriter>();
        auto out_bytes = writer->write(layout);

        save_to_stl(out_bytes, output);
    }
    catch (obj_file::ParseException const& e) {
        std::cout << "Opening file '" << input << "' failed, parse error." << std::endl;
    }
    catch (obj_file::StructIsException const& e) {
        std::cout << "Opening file '" << input << "' failed, struct model is empty." << std::endl;
    }
    catch (std::ifstream::failure const& e) {
        std::cout << "Opening file '" << input << "' failed, it either doesn't exist or is not accessible." << std::endl;
    }
    catch (std::exception const& e) {
        std::cout << "Failed to convert file." << std::endl;
    }
}

static void save_to_stl(std::vector<char> const& out_bytes, std::string const& output) {
    try {
        std::ofstream outfile;

        if (fs::exists(output)) {
            std::cout << "File '" << output << "' already exists" << std::endl;
        }
        else {
            outfile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            outfile.open(output, std::ios::out | std::ios::binary);
            outfile.write(out_bytes.data(), out_bytes.size());

            std::cout << "Successfully converted" << std::endl;
        }
    }
    catch (std::ofstream::failure const& e) {
        std::cout << "Converted but save to file '" << output << "' failed." << std::endl;
    }
}

int main(int argc, char **argv) {
    try {
        cxxopts::Options options(argv[0], "Converter from .obj to .stl");

        std::string input;
        std::string output;

        options
            .add_options()
            ("help", "Print help")
            ("i,input", "Input .obj file", cxxopts::value<std::string>(input))
            ("o,output", "Output .stl file", cxxopts::value<std::string>(output));

        auto result = options.parse(argc, argv);

        if (result.count("help") > 0 || result.arguments().empty()) {
            std::cout << options.help({"", "Group"}) << std::endl;
            exit(0);
        }

        if (result.count("input") == 0) {
            std::cout << "error parsing options: input is required" << std::endl;
            exit(1);
        }

        if (result.count("output") == 0) {
            std::cout << "error parsing options: output is required" << std::endl;
            exit(1);
        }

        convert_from_obj_to_stl(input, output);
    }
    catch (cxxopts::OptionException const& e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
