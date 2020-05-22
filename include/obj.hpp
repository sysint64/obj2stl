#pragma once

#include <vector>
#include <memory>
#include <exception>

#include <glm/glm.hpp>

#include "mesh.hpp"

namespace obj_file {

    struct ParseException : public std::exception {
	const char* what() const throw() {
            return "parse obj file error";
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

        Face(std::vector<Triplet> const& triplets)
            : triplets(triplets) {}
    };

    struct ObjStruct {
        const std::vector<glm::vec3> v;
        const std::vector<glm::vec2> vt;
        const std::vector<glm::vec3> vn;
        const std::vector<Face> f;

        ObjStruct(
            std::vector<glm::vec3> const& v,
            std::vector<glm::vec2> const& vt,
            std::vector<glm::vec3> const& vn,
            std::vector<Face> const& f
        ) :
            v(v), vt(vt), vn(vn), f(f)
        {
            // Nothing
        }
    };

    ObjStruct load_from_string_lines(std::vector<std::string> const& lines);

    std::shared_ptr<mesh::MeshLayout> create_mesh_layout_from_obj(ObjStruct const& obj);
}
