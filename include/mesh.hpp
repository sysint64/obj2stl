#pragma once

#include <limits>
#include <memory>
#include <utility>
#include <vector>
#include <cassert>
#include <glm/glm.hpp>
#include <sstream>
#include <exception>
#include <optional>

namespace mesh {
    const size_t absent_index = std::numeric_limits<size_t>::max();

    struct ValidationException : public std::exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "validation error";
        }
    };

    struct Triplet {
        size_t vertex_index;
        size_t normal_index;
        size_t tex_coord_index;

        Triplet(
            size_t vertex_index,
            size_t normal_index,
            size_t tex_coord_index
        ) {
            this->vertex_index = vertex_index;
            this->normal_index = normal_index;
            this->tex_coord_index = tex_coord_index;
        }

        bool operator==(Triplet const& other) const {
            return this->vertex_index == other.vertex_index &&
                this->normal_index == other.normal_index &&
                this->tex_coord_index == other.tex_coord_index;
        }
    };

    struct TripletFace {
        std::vector<Triplet> triplets;

        explicit TripletFace(std::vector<Triplet> triplets)
            : triplets(std::move(triplets)) {}

        bool operator==(TripletFace const& other) const {
            return this->triplets == other.triplets;
        }
    };

    struct Polygon {
        const std::vector<glm::vec3> vertices;
        const std::optional<std::vector<glm::vec3>> normals;
        const std::optional<std::vector<glm::vec2>> tex_coords;
        const std::optional<std::vector<glm::vec3>> normal;

        Polygon(
            std::vector<glm::vec3> const& vertices,
            std::optional<std::vector<glm::vec3>> const& normals,
            std::optional<std::vector<glm::vec2>> const& tex_coords,
            std::optional<std::vector<glm::vec3>> normal
        ) :
            normals(normals),
            vertices(vertices),
            tex_coords(tex_coords),
            normal(std::move(normal))
        {
            // IVARIANT: all vectors should have the same size
            if (normals) {
                assert(vertices.size() == normals.value().size());
            }

            if (tex_coords) {
                assert(vertices.size() == tex_coords.value().size());
            }
        }

        Polygon(
            std::vector<glm::vec3> const& vertices,
            std::vector<glm::vec3> const& normals,
            std::vector<glm::vec2> const& tex_coords
        ) :
            normals(normals),
            vertices({vertices}),
            tex_coords({tex_coords}),
            normal({})
        {
            // IVARIANT: all vectors should have the same size
            assert(vertices.size() == normals.size());
            assert(vertices.size() == tex_coords.size());
        }

        bool operator==(Polygon const& other) const {
            return this->vertices == other.vertices &&
                this->normals == other.normals &&
                this->tex_coords == other.tex_coords;
        }
    };

    struct Triangle {
        const std::array<glm::vec3, 3> vertices;
        const std::optional<std::array<glm::vec3, 3>> normals;
        const std::optional<std::array<glm::vec2, 3>> tex_coords;
        const std::optional<glm::vec3> normal;

        Triangle(
            std::array<glm::vec3, 3> const& vertices,
            std::optional<std::array<glm::vec3, 3>> const& normals,
            std::optional<std::array<glm::vec2, 3>> const& tex_coords,
            std::optional<glm::vec3> normal
        ) :
            normals(normals),
            vertices(vertices),
            tex_coords(tex_coords),
            normal(normal)
        {
        }

        Triangle(
            std::array<glm::vec3, 3> const& vertices,
            std::array<glm::vec3, 3> const& normals,
            std::array<glm::vec2, 3> const& tex_coords
        ) :
            normals({normals}),
            vertices(vertices),
            tex_coords({tex_coords}),
            normal({})
        {
        }

        bool operator==(Triangle const& other) const {
            return this->vertices == other.vertices &&
                this->normals == other.normals &&
                this->tex_coords == other.tex_coords &&
                this->normal == other.normal;
        }
    };

    struct FaceLayout {
        const std::vector<size_t> vertices_indices;
        const std::vector<size_t> normals_indices;
        const std::vector<size_t> tex_coord_indices;
        const std::vector<size_t> color_indices;

        FaceLayout(
            std::vector<size_t> const& vertices_indices,
            std::vector<size_t> const& normals_indices,
            std::vector<size_t> const& tex_coord_indices,
            std::vector<size_t> const& color_indices
        ) :
            vertices_indices(vertices_indices),
            normals_indices(normals_indices),
            tex_coord_indices(tex_coord_indices),
            color_indices(color_indices)
        {
            // IVARIANT: all vectors should have the same size
            assert(vertices_indices.size() == normals_indices.size());
            assert(vertices_indices.size() == tex_coord_indices.size());
            assert(vertices_indices.size() == color_indices.size());
        }
    };

    struct MeshLayout {
        const std::vector<glm::vec3> vertices;
        const std::vector<glm::vec3> normals;
        const std::vector<glm::vec2> tex_coords;
        const std::vector<glm::vec4> colors;
        const std::vector<FaceLayout> faces;

        MeshLayout(
            std::vector<glm::vec3> vertices,
            std::vector<glm::vec3> normals,
            std::vector<glm::vec2> tex_coords,
            std::vector<glm::vec4> colors,
            std::vector<FaceLayout> faces
        ) :
            vertices(std::move(vertices)),
            normals(std::move(normals)),
            tex_coords(std::move(tex_coords)),
            colors(std::move(colors)),
            faces(std::move(faces))
        {
            // Nothing
        }
    };

    class MeshLayoutBuilder {
    private:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> tex_coords;
        std::vector<glm::vec4> colors;
        std::vector<FaceLayout> faces;
        std::vector<Triplet> triplets;

        void validate_indices();

    public:
        std::shared_ptr<MeshLayout> build();

        void push_vertex(glm::vec3 vertex);

        void push_normal(glm::vec3 normal);

        void push_tex_coord(glm::vec2 tex_coord);

        void push_color(glm::vec4 color);

        void push_triplet(Triplet triplet);

        void push_triplet_face();

        void push_triplet_face(TripletFace const& face);

        void push_polygon(Polygon const& polygon);

        void push_triangle(Triangle triangle);
    };

    class TriangulationStrategy {
    public:
        virtual std::vector<Triangle> triangulate(Polygon &polygon) = 0;
    };

    class DummyTriangulationStrategy : public TriangulationStrategy {
    public:
        std::vector<Triangle> triangulate(Polygon &polygon) override;
    };

    class MeshLayoutReader {
        std::shared_ptr<MeshLayout> layout;
        std::shared_ptr<TriangulationStrategy> triangulation_strategy;

        std::vector<Triangle> triangles_data;
        std::vector<Polygon> polygons_data;
        std::vector<Triplet> triplets_data;
        std::vector<TripletFace> triplet_faces_data;

    public:
        MeshLayoutReader(
            std::shared_ptr<MeshLayout> layout,
            std::shared_ptr<TriangulationStrategy> triangulation_strategy
        ) :
            layout(std::move(layout)),
            triangulation_strategy(std::move(triangulation_strategy))
        {
            // Nothing
        }

        std::vector<Triangle> const& triangles();

        std::vector<Polygon> const& polygons();

        std::vector<glm::vec3> const& vertices();

        std::vector<glm::vec3> const& normals();

        std::vector<glm::vec2> const& tex_coords();

        std::vector<Triplet> const& triplets();

        std::vector<TripletFace> const& triplet_faces();
    };
}
