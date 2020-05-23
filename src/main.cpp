#include <obj.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <glm/glm.hpp>

#include "vendor/cxxopts.hpp"
#include "stl.hpp"
#include "utils.hpp"
#include "calc.hpp"

namespace fs = std::filesystem;

static void save_to_stl(std::vector<char> const& out_bytes, std::string const& output);

static std::shared_ptr<mesh::MeshLayout> load_mesh_layout(std::string const& input) {
    try {
        auto lines = utils::load_text_file_lines(input);
        auto obj = obj_file::load_from_string_lines(lines);
        return obj_file::create_mesh_layout_from_obj(obj);
    }
    catch (std::ifstream::failure const& e) {
        std::cout << "Opening file '" << input << "' failed, it either doesn't exist or is not accessible." << std::endl;
        exit(1);
    }
    catch (obj_file::ParseException const& e) {
        std::cout << "Opening file '" << input << "' failed, parse error." << std::endl;
        exit(1);
    }
    catch (obj_file::StructIsException const& e) {
        std::cout << "Opening file '" << input << "' failed, struct model is empty." << std::endl;
        exit(1);
    }
}

static void convert_from_obj_to_stl(
    std::shared_ptr<mesh::MeshLayout> layout,
    std::string const& output,
    glm::vec3 const& transition,
    glm::vec3 const& rotations,
    glm::vec3 const& scale
) {
    try {
        auto transformed_layout = calc::apply_transforms_to_layout(
            layout,
            transition,
            rotations,
            scale
        );

        auto writer = std::make_unique<stl_file::StlMeshWriter>();
        auto out_bytes = writer->write(transformed_layout);

        save_to_stl(out_bytes, output);
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

        glm::vec3 transition(0);
        glm::vec3 rotation(0);
        glm::vec3 scale(1);
        glm::vec3 point(0);

        bool convert_to_stl = false;
        bool test_point = false;
        bool surface_area = false;
        bool volume = false;

        options
            .add_options()
            ("help", "Print help")

            ("c,convert", "Convert to stl", cxxopts::value<bool>(convert_to_stl))
            ("s,surface_area", "Calculate surface area", cxxopts::value<bool>(surface_area))
            ("v,volume", "Calculate volume (experimental)", cxxopts::value<bool>(volume))
            ("p,test_point", "Test whether point inside mesh or not (experimental)", cxxopts::value<bool>(test_point))

            ("px", "Point x (default: 0)", cxxopts::value<float>(point.x))
            ("py", "Point y (default: 0)", cxxopts::value<float>(point.y))
            ("pz", "Point z (default: 0)", cxxopts::value<float>(point.z))

            ("tx", "x transition (default: 0)", cxxopts::value<float>(transition.x))
            ("ty", "y transition (default: 0)", cxxopts::value<float>(transition.y))
            ("tz", "z transition (default: 0)", cxxopts::value<float>(transition.z))

            ("rx", "x rotation (default: 0)", cxxopts::value<float>(rotation.x))
            ("ry", "y rotation (default: 0)", cxxopts::value<float>(rotation.y))
            ("rz", "z rotation (default: 0)", cxxopts::value<float>(rotation.z))

            ("sx", "x scale (default: 1)", cxxopts::value<float>(scale.x))
            ("sy", "y scale (default: 1)", cxxopts::value<float>(scale.y))
            ("sz", "z scale (default: 1)", cxxopts::value<float>(scale.z))

            ("i,input", "Input .obj file", cxxopts::value<std::string>(input))
            ("o,output", "Output .stl file", cxxopts::value<std::string>(output));

        auto result = options.parse(argc, argv);

        if (result.count("help") > 0 || result.arguments().empty()) {
            std::cout << options.help({"", "Group"}) << std::endl;
            exit(0);
        }

        if (!convert_to_stl && !test_point && !surface_area && !volume) {
            std::cout << "At least one action should be selected" << std::endl;
            exit(1);
        }

        if (result.count("input") == 0) {
            std::cout << "Input is required" << std::endl;
            exit(1);
        }

        auto mesh_layout = load_mesh_layout(input);

        if (convert_to_stl) {
            if (result.count("output") == 0) {
                std::cout << "Output is required" << std::endl;
                exit(1);
            }

            convert_from_obj_to_stl(mesh_layout, output, transition, rotation, scale);
        }

        if (surface_area) {
            const auto area = calc::calculate_surface_area(mesh_layout);
            std::cout << "Surface area is: " << area << std::endl;
        }

        if (volume) {
            const auto volume = calc::calculate_volume(mesh_layout);
            std::cout << "Volume is: " << volume << std::endl;
        }

        if (test_point) {
            const auto inside = calc::is_point_inside_mesh(point, mesh_layout);
            std::cout << "Point (" << point.x << ", " << point.y << ", " << point.z << ") ";

            if (inside) {
                std::cout << "is inside" << std::endl;
            }
            else {
                std::cout << "is outside" << std::endl;
            }
        }
    }
    catch (cxxopts::OptionException const& e) {
        std::cout << "Error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
