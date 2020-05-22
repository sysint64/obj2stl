#include "mesh.hpp"

namespace mesh {
    std::vector<glm::vec3> const& MeshLayoutReader::vertices() {
        return this->layout->vertices;
    }

    std::vector<glm::vec3> const& MeshLayoutReader::normals() {
        return this->layout->normals;
    }

    std::vector<glm::vec2> const& MeshLayoutReader::tex_coords() {
        return this->layout->tex_coords;
    }

    std::vector<Triplet> const& MeshLayoutReader::triplets() {
        this->triplets_data.clear();

        for (auto const& face : this->layout->faces) {
            for (int i = 0; i < face.vertices_indices.size(); i++) {
                this->triplets_data.emplace_back(
                    face.vertices_indices[i],
                    face.normals_indices[i],
                    face.tex_coord_indices[i]
                );
            }
        }

        return this->triplets_data;
    }

    std::vector<TripletFace> const& MeshLayoutReader::triplet_faces() {
        this->triplet_faces_data.clear();

        for (auto const& face : this->layout->faces) {
            std::vector<Triplet> triplets;
            triplets.reserve(face.vertices_indices.size());

            for (int i = 0; i < face.vertices_indices.size(); i++) {
                triplets.emplace_back(
                    face.vertices_indices[i],
                    face.normals_indices[i],
                    face.tex_coord_indices[i]
                );
            }

            this->triplet_faces_data.emplace_back(triplets);
        }

        return this->triplet_faces_data;
    }

    std::vector<Triangle> const& MeshLayoutReader::triangles() {
        this->triangles_data.clear();

        for (auto polygon : this->polygons()) {
            auto triangles = this->triangulation_strategy->triangulate(polygon);

            std::copy(
                triangles.begin(),
                triangles.end(),
                std::back_inserter(this->triangles_data)
            );
        }

        return this->triangles_data;
    }

    std::vector<Polygon> const& MeshLayoutReader::polygons() {
        this->polygons_data.clear();

        for (auto const& face : this->layout->faces) {
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> tex_coords;

            for (int i = 0; i < face.vertices_indices.size(); i++) {
                assert(face.vertices_indices[i] != ::mesh::absent_index);

                vertices.push_back(this->layout->vertices[face.vertices_indices[i]]);

                if (face.normals_indices[i] != ::mesh::absent_index) {
                    normals.push_back(this->layout->normals[face.normals_indices[i]]);
                }

                if (face.tex_coord_indices[i] != ::mesh::absent_index) {
                    tex_coords.push_back(this->layout->tex_coords[face.tex_coord_indices[i]]);
                }
            }

            this->polygons_data.push_back(
                Polygon(
                    vertices,
                    vertices.size() == normals.size() ? std::make_optional(std::move(normals)) : std::nullopt,
                    vertices.size() == tex_coords.size() ? std::make_optional(std::move(tex_coords)) : std::nullopt,
                    {}
                )
            );
        }

        return this->polygons_data;
    }
}
