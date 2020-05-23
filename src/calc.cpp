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

}
