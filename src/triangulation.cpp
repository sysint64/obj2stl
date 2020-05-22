#include "mesh.hpp"
#include <numeric>

namespace mesh {
    std::vector<Triangle> DummyTriangulationStrategy::triangulate(Polygon &polygon) {
        std::vector<size_t> indices(polygon.vertices.size());
        std::vector<Triangle> triangles;
        std::iota(indices.begin(), indices.end(), 0);

        while (indices.size() >= 3) {
            std::optional<std::array<glm::vec3, 3>> normals;
            std::optional<std::array<glm::vec2, 3>> tex_coords;

            if (polygon.normals) {
                normals = {
                    {
                        polygon.normals.value()[indices[0]],
                        polygon.normals.value()[indices[1]],
                        polygon.normals.value()[indices[2]]
                    }
                };
            }

            if (polygon.tex_coords) {
                tex_coords = {
                    {
                        polygon.tex_coords.value()[indices[0]],
                        polygon.tex_coords.value()[indices[1]],
                        polygon.tex_coords.value()[indices[2]]
                    }
                };
            }

            triangles.push_back(
                {
                    Triangle(
                        {
                            polygon.vertices[indices[0]],
                            polygon.vertices[indices[1]],
                            polygon.vertices[indices[2]]
                        },
                        normals,
                        tex_coords,
                        std::nullopt
                    )
                }
            );

            indices.erase(indices.begin() + 1);
        }

        return triangles;
    }
}
