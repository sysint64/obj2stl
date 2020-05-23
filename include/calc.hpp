#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "mesh.hpp"

namespace calc {
    // Will create new transformed mesh layout
    std::shared_ptr<mesh::MeshLayout> apply_transforms_to_layout(
        std::shared_ptr<mesh::MeshLayout> layout,
        glm::vec3 pos,
        glm::vec3 rotation,
        glm::vec3 scale
    );
}
