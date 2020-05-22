#include "format.hpp"

namespace mesh_format {

    std::vector<char> MeshWriter::write(std::shared_ptr<mesh::MeshLayout> const& layout) {
        auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
        this->layout_reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);

        this->writer->clear();
        this->write_layout();
        return this->writer->get_data();
    }

    void MeshWriter::write_vertices() {
        this->write_vertices(this->layout_reader->vertices());
    }

    void MeshWriter::write_normals() {
        this->write_normals(this->layout_reader->normals());
    }

    void MeshWriter::write_tex_coords() {
        this->write_tex_coords(this->layout_reader->tex_coords());
    }

    void MeshWriter::write_triplets() {
        this->write_triplets(this->layout_reader->triplets());
    }

    void MeshWriter::write_triangles() {
        this->write_triangles(this->layout_reader->triangles());
    }

    void MeshWriter::write_polygons() {
        this->write_polygons(this->layout_reader->polygons());
    }

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
        for (auto const& polygon : polygons) {
            this->write_polygon(polygon);
        }
    }

}
