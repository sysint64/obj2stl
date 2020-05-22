#pragma once

#include "format.hpp"

namespace stl_file {

    class StlMeshWriter : public mesh_format::MeshWriter {
    public:
        StlMeshWriter() : MeshWriter(
            mesh_format::FileType::Binary,
            mesh_format::ByteOrder::LittleEndian
        ) {}

    private:
        void write_header() override;

        void write_layout() override;

        void write_triangles(std::vector<mesh::Triangle> const& triangles) override;

        void write_triangle(mesh::Triangle const& triangle) override;
    };

}
