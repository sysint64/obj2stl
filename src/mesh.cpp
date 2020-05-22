#include <algorithm>
#include <numeric>
#include <memory>
#include "mesh.hpp"

namespace mesh {
    std::shared_ptr<MeshLayout> MeshLayoutBuilder::build() {
        this->validate_indices();

        return std::make_shared<MeshLayout>(
            this->vertices,
            this->normals,
            this->tex_coords,
            this->colors,
            this->faces
        );
    }

    template<typename T>
    static void validate_indices(
        std::vector<size_t> const& indices,
        std::vector<T> const& data
    ) {
        for (const auto index : indices) {
            if (index == ::mesh::absent_index) {
                continue;
            }

            if (index >= data.size()) {
                throw ValidationException();
            }
        }
    }

    void MeshLayoutBuilder::validate_indices() {
        for (const auto face : faces) {
            ::mesh::validate_indices(face.vertices_indices, this->vertices);
            ::mesh::validate_indices(face.normals_indices, this->normals);
            ::mesh::validate_indices(face.tex_coord_indices, this->tex_coords);
            ::mesh::validate_indices(face.color_indices, this->colors);
        }
    }

    void MeshLayoutBuilder::push_vertex(glm::vec3 vertex) {
        this->vertices.push_back(vertex);
    }

    void MeshLayoutBuilder::push_normal(glm::vec3 normal) {
        this->normals.push_back(normal);
    }

    void MeshLayoutBuilder::push_tex_coord(glm::vec2 tex_coord) {
        this->tex_coords.push_back(tex_coord);
    }

    void MeshLayoutBuilder::push_color(glm::vec4 color) {
        this->colors.push_back(color);
    }

    void MeshLayoutBuilder::push_triplet(Triplet triplet) {
        this->triplets.push_back(triplet);
    }

    void MeshLayoutBuilder::push_triplet_face() {
        std::vector<size_t> vertices_indices;
        std::vector<size_t> normals_indices;
        std::vector<size_t> tex_coord_indices;
        std::vector<size_t> color_indices;

        for (auto triplet : this->triplets) {
            vertices_indices.push_back(triplet.vertex_index);
            normals_indices.push_back(triplet.normal_index);
            tex_coord_indices.push_back(triplet.tex_coord_index);
            color_indices.push_back(::mesh::absent_index);
        }

        this->triplets.clear();
        this->faces.push_back(
            FaceLayout(
                vertices_indices,
                normals_indices,
                tex_coord_indices,
                color_indices
            )
        );
    }

    void MeshLayoutBuilder::push_triplet_face(TripletFace face) {
        this->triplets.clear();

        for (auto triplet : face.triplets) {
            this->push_triplet(triplet);
        }

        push_triplet_face();
    }

    void MeshLayoutBuilder::push_polygon(Polygon polygon) {
        auto vertex_start = this->vertices.size();
        auto normal_start = this->normals.size();
        auto tex_coord_start = this->tex_coords.size();

        auto const size = polygon.vertices.size();

        std::vector<size_t> vertices_indices(size);
        std::vector<size_t> normals_indices(size);
        std::vector<size_t> tex_coord_indices(size);
        std::vector<size_t> colors_indices(size);

        std::iota(vertices_indices.begin(), vertices_indices.end(), vertex_start);
        std::iota(normals_indices.begin(), normals_indices.end(), normal_start);
        std::iota(tex_coord_indices.begin(), tex_coord_indices.end(), tex_coord_start);
        std::fill(colors_indices.begin(), colors_indices.end(), ::mesh::absent_index);

        std::copy(
            std::begin(polygon.vertices),
            std::end(polygon.vertices),
            std::back_inserter(this->vertices)
        );

        if (polygon.normals) {
            std::copy(
                std::begin(polygon.normals.value()),
                std::end(polygon.normals.value()),
                std::back_inserter(this->normals)
            );
        }

        if (polygon.tex_coords) {
            std::copy(
                std::begin(polygon.tex_coords.value()),
                std::end(polygon.tex_coords.value()),
                std::back_inserter(this->tex_coords)
            );
        }

        this->faces.push_back(
            FaceLayout(
                vertices_indices,
                normals_indices,
                tex_coord_indices,
                colors_indices
            )
        );
    }

    void MeshLayoutBuilder::push_triangle(Triangle triangle) {
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> tex_coords;

        std::copy(
            std::begin(triangle.vertices),
            std::end(triangle.vertices),
            std::back_inserter(vertices)
        );

        if (triangle.normals) {
            std::copy(
                std::begin(triangle.normals.value()),
                std::end(triangle.normals.value()),
                std::back_inserter(normals)
            );
        }

        if (triangle.tex_coords) {
            std::copy(
                std::begin(triangle.tex_coords.value()),
                std::end(triangle.tex_coords.value()),
                std::back_inserter(tex_coords)
            );
        }

        this->push_polygon(
            Polygon(
                vertices,
                !normals.empty() ? std::make_optional(normals) : std::nullopt,
                !tex_coords.empty() ? std::make_optional(tex_coords) : std::nullopt,
                std::nullopt
            )
        );
    }
}
