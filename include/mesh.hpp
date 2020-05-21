#pragma once

#include <memory>
#include <vector>
#include <cassert>
#include <glm/glm.hpp>
#include <sstream>
#include <exception>

namespace mesh {
    struct ValidationException : public std::exception {
	const char* what() const throw() {
            return "Validation Exception";
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
    };

    struct Polygon {
        const std::vector<glm::vec3> normals;
        const std::vector<glm::vec3> vertices;
        const std::vector<glm::vec2> tex_coords;

        Polygon(
            std::vector<glm::vec3> const& normals,
            std::vector<glm::vec3> const& vertices,
            std::vector<glm::vec2> const& tex_coords
        ) :
            normals(normals),
            vertices(vertices),
            tex_coords(tex_coords)
        {
            // IVARIANT: all vectors should have the same size
            assert(vertices.size() == normals.size());
            assert(vertices.size() == tex_coords.size());
        }
    };

    struct Triangle {
        const glm::vec3 normals[3];
        const glm::vec3 vertices[3];
        const glm::vec2 tex_coords[3];
    };

    struct ColoredTriangle {
        glm::vec3 normal;
        glm::vec3 vertices[3];
        glm::vec2 tex_coord;
        glm::vec4 color;
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
            std::vector<glm::vec3> const& vertices,
            std::vector<glm::vec3> const& normals,
            std::vector<glm::vec2> const& tex_coords,
            std::vector<glm::vec4> const& colors,
            std::vector<FaceLayout> const& faces
        ) :
            vertices(vertices),
            normals(normals),
            tex_coords(tex_coords),
            colors(colors),
            faces(faces)
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
        MeshLayoutBuilder();

        MeshLayout build();

        void push_vertex(glm::vec3 vertex);

        void push_normal(glm::vec3 normal);

        void push_tex_coord(glm::vec2 tex_coord);

        void push_color(glm::vec4 color);

        void push_triplet(Triplet triplet);

        void push_triplet_face();

        void push_polygon(Polygon polygon);

        void push_triangle(Triangle triangle);
    };

    class TriangulationStrategy {
        virtual std::vector<Triangle> triangulate(Polygon polygon) = 0;
    };

    class MeshLayoutReader {
        std::shared_ptr<MeshLayout> mesh;
        std::shared_ptr<TriangulationStrategy> triangulation_strategy;

    public:
        MeshLayoutReader(
            std::shared_ptr<MeshLayout> mesh,
            std::shared_ptr<TriangulationStrategy> triangulation_strategy
        ) {
            this->mesh = mesh;
            this->triangulation_strategy = triangulation_strategy;
        }

        std::vector<Triangle>::iterator triangles();

        std::vector<ColoredTriangle>::iterator colored_triangle();

        std::vector<Polygon>::iterator polygons();

        std::vector<glm::vec3>::iterator vertices();

        std::vector<glm::vec3>::iterator normals();

        std::vector<glm::vec2>::iterator tex_coords();

        std::vector<Triplet>::iterator triplets();
    };
}
