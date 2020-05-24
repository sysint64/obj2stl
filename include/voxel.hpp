#pragma once

#include <memory>
#include "mesh.hpp"

namespace voxel {
    enum class LeafFillness {
        Fill,
        Empty,
    };

    class OctreeNode {
    public:
        LeafFillness fillness;
        const glm::vec3 min;
        const glm::vec3 max;
        std::optional<std::array<std::unique_ptr<OctreeNode>, 8>> nodes;

        void divide();

        OctreeNode(glm::vec3 min, glm::vec3 max)
            : min(min), max(max) {}
    };

    std::unique_ptr<OctreeNode> build_octree_from_mesh_layout(
        std::shared_ptr<mesh::MeshLayout> const& layout
    );
}
