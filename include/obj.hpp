#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace obj_file {

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
            return this->v == other.v;
        }
    };

    struct Face {
        std::vector<Triplet> triplets;
    };

    struct ObjStruct {
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;
        std::vector<Face> f;
    };

    ObjStruct load_from_bytes(std::vector<std::byte> const& bytes);
}
