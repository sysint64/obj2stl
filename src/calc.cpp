#include "calc.hpp"

#include <cmath>
#include "utils.hpp"

namespace calc {

    std::shared_ptr<mesh::MeshLayout> apply_transforms_to_layout(
        std::shared_ptr<mesh::MeshLayout> const& layout,
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

        return 0.5 * std::sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
    }

    double calculate_surface_area(std::shared_ptr<mesh::MeshLayout> const& layout) {
        auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
        auto layout_reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);
        double surface = 0;

        for (auto const& triangle : layout_reader->triangles()) {
            surface += triangle_area(triangle);
        }

        return surface;
    }

    // Calculate volume refs:
    //   https://stackoverflow.com/questions/1406029/how-to-calculate-the-volume-of-a-3d-mesh-object-the-surface-of-which-is-made-up-t
    //   http://chenlab.ece.cornell.edu/Publication/Cha/icip01_Cha.pdf
    static double signed_volume_of_triangle(mesh::Triangle const& triangle) {
        const auto v321 = triangle.vertices[2].x * triangle.vertices[1].y * triangle.vertices[0].z;
        const auto v231 = triangle.vertices[1].x * triangle.vertices[2].y * triangle.vertices[0].z;
        const auto v312 = triangle.vertices[2].x * triangle.vertices[0].y * triangle.vertices[1].z;
        const auto v132 = triangle.vertices[0].x * triangle.vertices[2].y * triangle.vertices[1].z;
        const auto v213 = triangle.vertices[1].x * triangle.vertices[0].y * triangle.vertices[2].z;
        const auto v123 = triangle.vertices[0].x * triangle.vertices[1].y * triangle.vertices[2].z;

        return (1.0f/6.0f) * (-v321 + v231 + v312 - v132 - v213 + v123);
    }

    double calculate_volume(std::shared_ptr<mesh::MeshLayout> const& layout) {
        auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
        auto layout_reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);
        double volume = 0;

        for (auto const& triangle : layout_reader->triangles()) {
            volume += signed_volume_of_triangle(triangle);
        }

        return volume;
    }

    static double signed_volume(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
        return (1.0f/6.0f) * glm::dot(glm::cross(b-a, c-a), d-a);
    }

    static double signed_volume(glm::vec3 point, mesh::Triangle const& triangle) {
        return signed_volume(point, triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
    }

    static bool eq_sign(double v1, double v2) {
        if (v1 >= 0 && v2 >= 0) return true;
        else return v1 < 0 && v2 < 0;
    }

    // Ref: https://stackoverflow.com/questions/42740765/intersection-between-line-and-triangle-in-3d
    static bool test_intersect_triangle(
        glm::vec3 ray_dir,
        glm::vec3 ray_pos,
        mesh::Triangle const& triangle
    ) {
        const glm::vec3 ray_dir_normalized = glm::normalize(ray_dir);

        const auto q1 = ray_pos;
        const auto q2 = ray_dir_normalized * std::numeric_limits<glm::vec3>::infinity();

        const auto v1 = signed_volume(q1, triangle);
        const auto v2 = signed_volume(q2, triangle);
        const auto v3 = signed_volume(q1, q2, triangle.vertices[0], triangle.vertices[1]);
        const auto v4 = signed_volume(q1, q2, triangle.vertices[1], triangle.vertices[2]);
        const auto v5 = signed_volume(q1, q2, triangle.vertices[2], triangle.vertices[0]);

        return !eq_sign(v1, v2) && eq_sign(v3, v4) && eq_sign(v3, v5);
    }

    bool is_point_inside_mesh(glm::vec3 point, std::shared_ptr<mesh::MeshLayout> const& layout) {
        auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
        auto layout_reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);

        for (auto const& triangle : layout_reader->triangles()) {
            const auto n = utils::calculate_normal(triangle);
            const auto dist = glm::dot(n, point - triangle.vertices[0]);

            if (dist > 0) {
                return false;
            }
        }

        return true;
    }

    BoundingBox find_bounding_box(std::shared_ptr<mesh::MeshLayout> const& layout) {
        glm::vec3 min;
        glm::vec3 max;

        for (auto const& vertex : layout->vertices) {
            min.x = std::min(min.x, vertex.x);
            min.y = std::min(min.y, vertex.y);
            min.z = std::min(min.z, vertex.z);

            max.x = std::max(max.x, vertex.x);
            max.y = std::max(max.y, vertex.y);
            max.z = std::max(max.z, vertex.z);
        }

        return BoundingBox(
            std::move(min),
            std::move(max)
        );
    }

}
