#pragma once

#include "format.hpp"

namespace stl_file {

    class StlMeshWriter : public mesh_format::MeshWriter {
        StlMeshWriter() : MeshWriter(
            mesh_format::FileType::Binary,
            mesh_format::ByteOrder::LittleEndian
        ) {}

        void write_header() override;

        void write_triangle(mesh::Triangle const& triangle) override;
    };

}
