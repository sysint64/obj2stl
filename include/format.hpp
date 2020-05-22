#pragma one

#include <glm/glm.hpp>
#include "mesh.hpp"

namespace mesh_format {

    enum class FileType {
        Binary,
        Text,
    };

    enum class ByteOrder {
        LittleEndian,
        BigEndian,
        Native,
    };

    class BytesWriter {
    public:
        BytesWriter(FileType file_type, ByteOrder byte_order) {
            this->file_type = file_type;
            this->byte_order = byte_order;
        }

        BytesWriter(FileType file_type) {
            this->file_type = file_type;
            this->byte_order = ByteOrder::Native;
        }

        std::vector<std::byte> const& get_bytes();

        std::vector<char> const& get_data();

        void clear();

        void write_int32_t(int32_t value);

        void write_float(float value);

        void write_byte(std::byte byte);

        void write_bytes(std::vector<std::byte> const& bytes);

        void write_char(char ch);

        void write_string(std::string const& str);

    private:
        std::vector<std::byte> bytes;
        std::vector<char> chars;

        FileType file_type;
        ByteOrder byte_order;

        bool is_endian_mismatch();
    };

    class MeshWriter {
    public:
        std::vector<char> write(std::shared_ptr<mesh::MeshLayout> layout);

        MeshWriter(FileType file_type, ByteOrder byte_order) {
            this->writer = std::make_unique<BytesWriter>(file_type, byte_order);
        }

    protected:
        std::unique_ptr<BytesWriter> writer;
        std::unique_ptr<mesh::MeshLayoutReader> layout_reader;

        virtual void write_header() {}

        virtual void write_layout() = 0;

        virtual void write_vertices();

        virtual void write_normals();

        virtual void write_tex_coords();

        virtual void write_triplets();

        virtual void write_triangles();

        virtual void write_polygons();

        virtual void write_vertices(std::vector<glm::vec3> const& vertices);

        virtual void write_normals(std::vector<glm::vec3> const& normals);

        virtual void write_tex_coords(std::vector<glm::vec2> const& tex_coords);

        virtual void write_triplets(std::vector<mesh::Triplet> const& triplets);

        virtual void write_triangles(std::vector<mesh::Triangle> const& triangles);

        virtual void write_polygons(std::vector<mesh::Polygon> const& polygons);

        virtual void write_triangle(mesh::Triangle const& triangle) {}

        virtual void write_polygon(mesh::Polygon const& polygon) {}

        virtual void write_vertex(glm::vec3 const& vertex) {}

        virtual void write_normal(glm::vec3 const& normal) {}

        virtual void write_tex_coord(glm::vec2 const& tex_coord) {}

        virtual void write_triplet(mesh::Triplet const& index) {}

        virtual void write_end() {}
    };

}
