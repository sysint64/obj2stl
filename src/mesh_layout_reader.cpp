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

        for (auto face : this->layout->faces) {
            for (int i = 0; i < face.vertices_indices.size(); i++) {
                this->triplets_data.push_back(
                    Triplet(
                        face.vertices_indices[i],
                        face.normals_indices[i],
                        face.tex_coord_indices[i]
                    )
                );
            }
        }

        return this->triplets_data;
    }

    std::vector<TripletFace> const& MeshLayoutReader::triplet_faces() {
        this->triplet_faces_data.clear();

        for (auto face : this->layout->faces) {
            std::vector<Triplet> triplets;

            for (int i = 0; i < face.vertices_indices.size(); i++) {
                triplets.push_back(
                    Triplet(
                        face.vertices_indices[i],
                        face.normals_indices[i],
                        face.tex_coord_indices[i]
                    )
                );
            }

            this->triplet_faces_data.push_back(TripletFace(triplets));
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

        for (auto face : this->layout->faces) {
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> tex_coords;

            for (int i = 0; i < face.vertices_indices.size(); i++) {
                vertices.push_back(this->layout->vertices[face.vertices_indices[i]]);
                normals.push_back(this->layout->normals[face.normals_indices[i]]);
                tex_coords.push_back(this->layout->tex_coords[face.tex_coord_indices[i]]);
            }

            this->polygons_data.push_back(Polygon(vertices, normals, tex_coords));
        }

        return this->polygons_data;
    }
}
