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
        for (auto const& face : faces) {
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

    void MeshLayoutBuilder::push_triplet(Triplet const& triplet) {
        this->triplets.push_back(triplet);
    }

    void MeshLayoutBuilder::push_face_layout(FaceLayout const& face) {
        this->faces.push_back(face);
    }

    void MeshLayoutBuilder::push_triplet_face() {
        std::vector<size_t> vertices_indices;
        std::vector<size_t> normals_indices;
        std::vector<size_t> tex_coord_indices;
        std::vector<size_t> color_indices;

        for (auto const& triplet : this->triplets) {
            vertices_indices.push_back(triplet.vertex_index);
            normals_indices.push_back(triplet.normal_index);
            tex_coord_indices.push_back(triplet.tex_coord_index);
            color_indices.push_back(::mesh::absent_index);
        }

        this->triplets.clear();
        this->faces.emplace_back(
            vertices_indices,
            normals_indices,
            tex_coord_indices,
            color_indices
        );
    }

    void MeshLayoutBuilder::push_triplet_face(TripletFace const& face) {
        this->triplets.clear();

        for (auto const& triplet : face.triplets) {
            this->push_triplet(triplet);
        }

        push_triplet_face();
    }

    void MeshLayoutBuilder::push_polygon(Polygon const& polygon) {
        auto vertex_start = this->vertices.size();
        auto normal_start = this->normals.size();
        auto tex_coord_start = this->tex_coords.size();

        auto const size = polygon.vertices.size();

        std::vector<size_t> vertices_indices(size);
        std::vector<size_t> normals_indices(size);
        std::vector<size_t> tex_coord_indices(size);
        std::vector<size_t> colors_indices(size);

        std::iota(vertices_indices.begin(), vertices_indices.end(), vertex_start);
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
            std::iota(normals_indices.begin(), normals_indices.end(), normal_start);
        }
        else {
            std::fill(normals_indices.begin(), normals_indices.end(), ::mesh::absent_index);
        }

        if (polygon.tex_coords) {
            std::copy(
                std::begin(polygon.tex_coords.value()),
                std::end(polygon.tex_coords.value()),
                std::back_inserter(this->tex_coords)
            );
            std::iota(tex_coord_indices.begin(), tex_coord_indices.end(), tex_coord_start);
        }
        else {
            std::fill(tex_coord_indices.begin(), tex_coord_indices.end(), ::mesh::absent_index);
        }

        this->faces.emplace_back(
            vertices_indices,
            normals_indices,
            tex_coord_indices,
            colors_indices
        );
    }

    void MeshLayoutBuilder::push_triangle(Triangle const& triangle) {
        std::vector<glm::vec3> polygon_normals;
        std::vector<glm::vec3> polygon_vertices;
        std::vector<glm::vec2> polygon_tex_coords;

        std::copy(
            std::begin(triangle.vertices),
            std::end(triangle.vertices),
            std::back_inserter(polygon_vertices)
        );

        if (triangle.normals) {
            std::copy(
                std::begin(triangle.normals.value()),
                std::end(triangle.normals.value()),
                std::back_inserter(polygon_normals)
            );
        }

        if (triangle.tex_coords) {
            std::copy(
                std::begin(triangle.tex_coords.value()),
                std::end(triangle.tex_coords.value()),
                std::back_inserter(polygon_tex_coords)
            );
        }

        this->push_polygon(
            Polygon(
                polygon_vertices,
                !polygon_normals.empty() ? std::make_optional(std::move(polygon_normals)) : std::nullopt,
                !polygon_tex_coords.empty() ? std::make_optional(std::move(polygon_tex_coords)) : std::nullopt,
                std::nullopt
            )
        );
    }

    void MeshLayoutBuilder::push_vertices(std::vector<glm::vec3> const& items) {
        for (auto const& item : items) {
            this->push_vertex(item);
        }
    }

    void MeshLayoutBuilder::push_normals(std::vector<glm::vec3> const& items) {
        for (auto const& item : items) {
            this->push_normal(item);
        }
    }

    void MeshLayoutBuilder::push_tex_coords(std::vector<glm::vec2> const& items) {
        for (auto const& item : items) {
            this->push_tex_coord(item);
        }
    }

    void MeshLayoutBuilder::push_colors(std::vector<glm::vec4> const& items) {
        for (auto const& item : items) {
            this->push_color(item);
        }
    }

    void MeshLayoutBuilder::push_triplets(std::vector<Triplet> const& items) {
        for (auto const& item : items) {
            this->push_triplet(item);
        }
    }

    void MeshLayoutBuilder::push_triplet_faces(std::vector<TripletFace> const& items) {
        for (auto const& item : items) {
            this->push_triplet_face(item);
        }
    }

    void MeshLayoutBuilder::push_polygons(std::vector<Polygon> const& items) {
        for (auto const& item : items) {
            this->push_polygon(item);
        }
    }

    void MeshLayoutBuilder::push_triangles(std::vector<Triangle> const& items) {
        for (auto const& item : items) {
            this->push_triangle(item);
        }
    }

    void MeshLayoutBuilder::push_face_layouts(std::vector<FaceLayout> const& items) {
        for (auto const& item : items) {
            this->push_face_layout(item);
        }
    }
}
