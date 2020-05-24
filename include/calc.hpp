#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "mesh.hpp"

namespace calc {

    // Create new transformed mesh layout
    std::shared_ptr<mesh::MeshLayout> apply_transforms_to_layout(
        std::shared_ptr<mesh::MeshLayout> const& layout,
        glm::vec3 pos,
        glm::vec3 rotation,
        glm::vec3 scale
    );

    double calculate_surface_area(std::shared_ptr<mesh::MeshLayout> const& layout);

    double calculate_volume(std::shared_ptr<mesh::MeshLayout> const& layout);

    bool is_point_inside_mesh(glm::vec3 point, std::shared_ptr<mesh::MeshLayout> const& layout);

    struct BoundingBox {
        const glm::vec3 min;
        const glm::vec3 max;

        BoundingBox(glm::vec3 min, glm::vec3 max)
            : min(min), max(max) {}
    };

    BoundingBox find_bounding_box(std::shared_ptr<mesh::MeshLayout> const& layout);

    // Makes all sides equal
    BoundingBox eq_bounding_box(BoundingBox box);
}
