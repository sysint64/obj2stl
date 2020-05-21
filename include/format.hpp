#pragma one

#include <glm/glm.hpp>
#include "mesh.hpp"

namespace mesh_format {

    enum class FileType {
        Binary,
        Text,
    };

    class Writer {
    public:
        std::vector<std::byte> write(mesh::MeshLayout data);

        void write_little_endian_byte(std::byte b);

        void write_big_endian_byte(std::byte b);

        void write_little_endian_bytes(std::vector<std::byte> const& b);

        void write_big_endian_bytes(std::vector<std::byte> const& b);

        void write_char(char ch);

        void write_string(std::string str);

    private:
        std::vector<std::byte> bytes;
        mesh::MeshLayout data;
        FileType file_type;
    };

    class TrianglesWriter {
    public:
        std::vector<std::byte> write(mesh::MeshLayout data);

    protected:
        virtual FileType get_file_type() = 0;

        virtual void write_header() = 0;

        virtual void write_triangles(std::vector<mesh::Triangle> const& triangles);

        virtual void write_triangle(mesh::Triangle const& triangle) = 0;

        virtual void write_end() = 0;
    };

    class IndexedMeshWriter {
    public:
        std::vector<std::byte> write(mesh::MeshLayout data);

    protected:
        virtual FileType get_file_type() = 0;

        virtual void write_header() = 0;

        virtual void write_vertices(std::vector<glm::vec3> const& vertices);

        virtual void write_normals(std::vector<glm::vec3> const& normals);

        virtual void write_tex_coords(std::vector<glm::vec2> const& tex_coords);

        virtual void write_triplets(std::vector<mesh::Triplet> const& triplet) = 0;

        virtual void write_vertex(glm::vec3 const& vertex) = 0;

        virtual void write_normal(glm::vec3 const& normal) = 0;

        virtual void write_tex_coord(glm::vec2 const& tex_coord) = 0;

        virtual void write_triplet(mesh::Triplet const& index) = 0;

        virtual void write_end() = 0;
    };
}
