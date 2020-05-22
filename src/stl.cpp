#include "stl.hpp"
#include "utils.hpp"

namespace stl_file {

    void StlMeshWriter::write_layout() {
        this->write_header();
        MeshWriter::write_triangles();
    }

    void StlMeshWriter::write_header() {
        std::vector<std::byte> bytes(80);
        this->writer->write_bytes(bytes);
    }

    void StlMeshWriter::write_triangles(std::vector<mesh::Triangle> const& triangles) {
        this->writer->write_int32_t(static_cast<int32_t>(triangles.size()));
        MeshWriter::write_triangles(triangles);
    }

    void StlMeshWriter::write_triangle(mesh::Triangle const& triangle) {
        // REAL32[3] – Normal vector
        auto normal = triangle.normal.value_or(
            utils::calculate_normal(
                triangle.vertices[0],
                triangle.vertices[1],
                triangle.vertices[2]
            )
        );

        this->writer->write_float(normal.x);
        this->writer->write_float(normal.y);
        this->writer->write_float(normal.z);

        // Vertices
        for (auto vertex : triangle.vertices) {
            this->writer->write_float(vertex.x);
            this->writer->write_float(vertex.y);
            this->writer->write_float(vertex.z);
        }

        // UINT16 – Attribute byte count
        this->writer->write_bytes({std::byte(0x00), std::byte(0x00)});
    }
}
