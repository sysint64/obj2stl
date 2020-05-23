#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "mesh.hpp"

namespace calc {

    // Create new transformed mesh layout
    std::shared_ptr<mesh::MeshLayout> apply_transforms_to_layout(
        std::shared_ptr<mesh::MeshLayout> layout,
        glm::vec3 pos,
        glm::vec3 rotation,
        glm::vec3 scale
    );

    double calculate_surface_area(std::shared_ptr<mesh::MeshLayout> layout);

    double calculate_volume(std::shared_ptr<mesh::MeshLayout> layout);

    bool is_point_inside_mesh(glm::vec3 point, std::shared_ptr<mesh::MeshLayout> layout);

}
