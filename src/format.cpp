#include "format.hpp"

namespace mesh_format {

    void MeshWriter::write_vertices(std::vector<glm::vec3> const& vertices) {
        for (auto vertex : vertices) {
            this->write_vertex(vertex);
        }
    }

    void MeshWriter::write_normals(std::vector<glm::vec3> const& normals) {
        for (auto normal : normals) {
            this->write_normal(normal);
        }
    }

    void MeshWriter::write_tex_coords(std::vector<glm::vec2> const& tex_coords) {
        for (auto tex_coord : tex_coords) {
            this->write_tex_coord(tex_coord);
        }
    }

    void MeshWriter::write_triplets(std::vector<mesh::Triplet> const& triplets) {
        for (auto triplet : triplets) {
            this->write_triplet(triplet);
        }
    }

    void MeshWriter::write_triangles(std::vector<mesh::Triangle> const& triangles) {
        for (auto triangle : triangles) {
            this->write_triangle(triangle);
        }
    }

    void MeshWriter::write_polygons(std::vector<mesh::Polygon> const& polygons) {
        for (auto polygon : polygons) {
            this->write_polygon(polygon);
        }
    }

}
