#include "calc.hpp"

namespace calc {

    std::shared_ptr<mesh::MeshLayout> apply_transforms_to_layout(
        std::shared_ptr<mesh::MeshLayout> layout,
        glm::vec3 pos,
        glm::vec3 rotation,
        glm::vec3 scale
    ) {
        const auto translate_matrix = glm::translate(glm::mat4(1), pos);

        const auto rotate_x_matrix = glm::rotate(
            glm::mat4(1),
            rotation[0],
            glm::vec3(1.0f, 0.0f, 0.0f)
        );

        const auto rotate_y_matrix = glm::rotate(
            glm::mat4(1),
            rotation[0],
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        const auto rotate_z_matrix = glm::rotate(
            glm::mat4(1),
            rotation[0],
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

        const auto scale_matrix = glm::scale(glm::mat4(1), scale);

        const auto rotate_matrix = rotate_x_matrix * rotate_y_matrix * rotate_z_matrix;
        const auto model_matrix = translate_matrix * rotate_matrix * scale_matrix;

        auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

        builder->push_normals(layout->normals);
        builder->push_tex_coords(layout->tex_coords);
        builder->push_colors(layout->colors);
        builder->push_face_layouts(layout->faces);

        for (auto const& vertex : layout->vertices) {
            auto new_vertex = model_matrix * glm::vec4(vertex, 1.0f);
            builder->push_vertex(glm::vec3(new_vertex));
        }

        return builder->build();
    }

    static double triangle_area(mesh::Triangle const& triangle) {
        const glm::vec3 a = triangle.vertices[1] - triangle.vertices[0];
        const glm::vec3 b = triangle.vertices[2] - triangle.vertices[0];
        const glm::vec3 c = glm::cross(a, b);

        return 0.5 * sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
    }

    double calculate_surface_area(std::shared_ptr<mesh::MeshLayout> layout) {
        auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
        auto layout_reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);
        double surface = 0;

        for (auto const& triangle : layout_reader->triangles()) {
            surface += triangle_area(triangle);
        }

        return surface;
    }

    double signed_volume_of_triangle(mesh::Triangle const& triangle) {
        const auto v321 = triangle.vertices[2].x * triangle.vertices[1].y * triangle.vertices[0].z;
        const auto v231 = triangle.vertices[1].x * triangle.vertices[2].y * triangle.vertices[0].z;
        const auto v312 = triangle.vertices[2].x * triangle.vertices[0].y * triangle.vertices[1].z;
        const auto v132 = triangle.vertices[0].x * triangle.vertices[2].y * triangle.vertices[1].z;
        const auto v213 = triangle.vertices[1].x * triangle.vertices[0].y * triangle.vertices[2].z;
        const auto v123 = triangle.vertices[0].x * triangle.vertices[1].y * triangle.vertices[2].z;

        return (1.0f/6.0f) * (-v321 + v231 + v312 - v132 - v213 + v123);
    }

    double calculate_volume(std::shared_ptr<mesh::MeshLayout> layout) {
        auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
        auto layout_reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);
        double volume = 0;

        for (auto const& triangle : layout_reader->triangles()) {
            volume += signed_volume_of_triangle(triangle);
        }

        return volume;
    }

}
