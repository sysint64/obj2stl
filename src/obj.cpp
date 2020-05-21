#include "obj.hpp"

namespace obj_file {
    ObjStruct load_from_bytes(std::vector<std::byte> const& bytes) {
        return ObjStruct {
            .v = {
                glm::vec3(1.000000, 1.000000, -1.000000),
                glm::vec3(1.000000, -1.000000, -1.000000),
                glm::vec3(1.000000, 1.000000, 1.000000),
                glm::vec3(1.000000, -1.000000, 1.000000),
                glm::vec3(-1.000000, 1.000000, -1.000000),
                glm::vec3(-1.000000, -1.000000, -1.000000),
                glm::vec3(-1.000000, 1.000000, 1.000000),
                glm::vec3(-1.000000, -1.000000, 1.000000),
            },
            .vt = {
                glm::vec2(0.625000, 0.500000),
                glm::vec2(0.875000, 0.500000),
                glm::vec2(0.875000, 0.750000),
                glm::vec2(0.625000, 0.750000),
                glm::vec2(0.375000, 0.750000),
                glm::vec2(0.625000, 1.000000),
                glm::vec2(0.375000, 1.000000),
                glm::vec2(0.375000, 0.000000),
                glm::vec2(0.625000, 0.000000),
                glm::vec2(0.625000, 0.250000),
                glm::vec2(0.375000, 0.250000),
                glm::vec2(0.125000, 0.500000),
                glm::vec2(0.375000, 0.500000),
                glm::vec2(0.125000, 0.750000)
            },
            .vn = {
                glm::vec3(0.0000, 1.0000, 0.0000),
                glm::vec3(0.0000, 0.0000, 1.0000),
                glm::vec3(-1.0000, 0.0000, 0.0000),
                glm::vec3(0.0000, -1.0000, 0.0000),
                glm::vec3(1.0000, 0.0000, 0.0000),
                glm::vec3(0.0000, 0.0000, -1.0000)
            },
            .f = {
                Face {
                    .triplets = {
                        obj_file::Triplet(1, 1, 1),
                        obj_file::Triplet(5, 2, 1),
                        obj_file::Triplet(7, 3, 1),
                        obj_file::Triplet(3, 4, 1)
                    }
                },
                Face {
                    .triplets = {
                        obj_file::Triplet(4, 5, 2),
                        obj_file::Triplet(3, 4, 2),
                        obj_file::Triplet(7, 6, 2),
                        obj_file::Triplet(8, 7, 2)
                    }
                },
                Face {
                    .triplets = {
                        obj_file::Triplet(8, 8, 3),
                        obj_file::Triplet(7, 9, 3),
                        obj_file::Triplet(5, 10, 3),
                        obj_file::Triplet(6, 11, 3)
                    }
                },
                Face {
                    .triplets = {
                        obj_file::Triplet(6, 12, 4),
                        obj_file::Triplet(2, 13, 4),
                        obj_file::Triplet(4, 5, 4),
                        obj_file::Triplet(8, 14, 4)
                    }
                },
                Face {
                    .triplets = {
                        obj_file::Triplet(2, 13, 5),
                        obj_file::Triplet(1, 1, 5),
                        obj_file::Triplet(3, 4, 5),
                        obj_file::Triplet(4, 5, 5)
                    }
                },
                Face {
                    .triplets = {
                        obj_file::Triplet(6, 11, 6),
                        obj_file::Triplet(5, 10, 6),
                        obj_file::Triplet(1, 1, 6),
                        obj_file::Triplet(2, 13, 6)
                    }
                },
            }
        };
    }
}
