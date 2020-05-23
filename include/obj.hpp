#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <exception>

#include <glm/glm.hpp>

#include "mesh.hpp"

namespace obj_file {

    struct ParseException : public std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "parse obj file error";
        }
    };

    struct StructIsException : public std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "model struct is empty";
        }
    };

    struct Triplet {
        size_t v;
        size_t vt;
        size_t vn;

        Triplet(int v, int vt, int vn) {
            this->v = v;
            this->vt = vt;
            this->vn = vn;
        }

        bool operator==(Triplet const& other) const {
            return this->v == other.v &&
                this->vt == other.vt &&
                this->vn == other.vn;
        }
    };

    struct Face {
        const std::vector<Triplet> triplets;

        explicit Face(std::vector<Triplet> triplets)
            : triplets(std::move(triplets)) {}
    };

    struct ObjStruct {
        const std::vector<glm::vec3> v;
        const std::vector<glm::vec2> vt;
        const std::vector<glm::vec3> vn;
        const std::vector<Face> f;

        ObjStruct(
            std::vector<glm::vec3> v,
            std::vector<glm::vec2> vt,
            std::vector<glm::vec3> vn,
            std::vector<Face> f
        ) :
            v(std::move(v)),
            vt(std::move(vt)),
            vn(std::move(vn)),
            f(std::move(f))
        {
            // Nothing
        }
    };

    ObjStruct load_from_string_lines(std::vector<std::string> const& lines);

    std::shared_ptr<mesh::MeshLayout> create_mesh_layout_from_obj(ObjStruct const& obj);
}
