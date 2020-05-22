#include <algorithm>
#include <string>

#include "obj.hpp"
#include "utils.hpp"

namespace obj_file {

    static glm::vec3 parse_vec3(std::string const& line);

    static glm::vec2 parse_vec2(std::string const& line);

    static Face parse_face(std::string const& line);

    static Triplet parse_triplet(std::string const& line);

    static size_t parse_optional_index(std::string const& str);

    ObjStruct load_from_string_lines(std::vector<std::string> const& lines) {
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;
        std::vector<Face> f;

        for (auto const& line : lines) {
            if (line.rfind("v ", 0) == 0) {
                auto vec = parse_vec3(line.substr(2));
                v.push_back(vec);
            }
            else if (line.rfind("vt ", 0) == 0) {
                auto vec = parse_vec2(line.substr(3));
                vt.push_back(vec);
            }
            else if (line.rfind("vn ", 0) == 0) {
                auto vec = parse_vec3(line.substr(3));
                vn.push_back(vec);
            }
            else if (line.rfind("f ", 0) == 0) {
                auto face = parse_face(line.substr(2));
                f.push_back(face);
            }
        }

        return ObjStruct(v, vt, vn, f);
    }

    static glm::vec3 parse_vec3(std::string const& line) {
        auto components = utils::split(line, ' ');

        if (components.size() != 3) {
            throw ParseException();
        }

        return glm::vec3(
            std::stof(components[0]),
            std::stof(components[1]),
            std::stof(components[2])
        );
    }

    static glm::vec2 parse_vec2(std::string const& line) {
        auto components = utils::split(line, ' ');

        if (components.size() != 2) {
            throw ParseException();
        }

        return glm::vec2(
            std::stof(components[0]),
            std::stof(components[1])
        );
    }

    static Face parse_face(std::string const& line) {
        auto triplets_str = utils::split(line, ' ');
        std::vector<Triplet> triplets;
        triplets.reserve(triplets_str.size());

        for (auto const& triplet : triplets_str) {
            triplets.push_back(parse_triplet(triplet));
        }

        return Face(triplets);
    }

    static Triplet parse_triplet(std::string const& line) {
        auto components = utils::split(line, '/');

        if (components.size() != 3) {
            throw ParseException();
        }

        return Triplet(
            std::stoi(components[0]),
            parse_optional_index(components[1]),
            parse_optional_index(components[2])
        );
    }

    static size_t parse_optional_index(std::string const& str) {
        if (str.empty()) {
            return 0;
        }
        else {
            return std::stoi(str);
        }
    }

    std::shared_ptr<mesh::MeshLayout> create_mesh_layout_from_obj(ObjStruct const& obj) {
        auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

        for (auto v : obj.v) {
            builder->push_vertex(v);
        }

        for (auto vn : obj.vn) {
            builder->push_normal(vn);
        }

        for (auto vt : obj.vt) {
            builder->push_tex_coord(vt);
        }

        std::vector<mesh::TripletFace> faces;
        faces.reserve(obj.f.size());

        for (auto const& f : obj.f) {
            std::vector<mesh::Triplet> triplets;
            triplets.reserve(obj.f.size());

            for (auto triplet : f.triplets) {
                triplets.emplace_back(
                    triplet.v == 0 ? mesh::absent_index : triplet.v - 1,
                    triplet.vn == 0 ? mesh::absent_index : triplet.vn - 1,
                    triplet.vt == 0 ? mesh::absent_index : triplet.vt - 1
                );
            }

            faces.emplace_back(triplets);
        }

        for (auto const& face : faces) {
            builder->push_triplet_face(face);
        }

        return builder->build();
    }
}
