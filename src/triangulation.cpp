#include "mesh.hpp"
#include <numeric>

namespace mesh {
    std::vector<Triangle> DummyTriangulationStrategy::triangulate(Polygon &polygon) {
        std::vector<size_t> indices(polygon.vertices.size());
        std::vector<Triangle> triangles;
        std::iota(indices.begin(), indices.end(), 0);

        while (indices.size() >= 3) {
            triangles.push_back(
                Triangle {
                    .vertices = {
                        polygon.vertices[indices[0]],
                        polygon.vertices[indices[1]],
                        polygon.vertices[indices[2]]
                    },
                    .normals = {
                        polygon.normals[indices[0]],
                        polygon.normals[indices[1]],
                        polygon.normals[indices[2]]
                    },
                    .tex_coords = {
                        polygon.tex_coords[indices[0]],
                        polygon.tex_coords[indices[1]],
                        polygon.tex_coords[indices[2]]
                    },
                }
            );

            indices.erase(indices.begin() + 1);
        }

        return triangles;
    }
}
