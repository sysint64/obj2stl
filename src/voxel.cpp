#include "voxel.hpp"

namespace voxel {

    void OctreeNode::divide() {
        std::array<std::unique_ptr<OctreeNode>, 8> nodes;
        const auto d = (this->max - this->min) / 2.0f;

        const auto box_min = this->min;
        const auto box_max = this->min + glm::vec3(d.x, d.y, d.z);

        nodes[0] = std::make_unique<OctreeNode>(
            box_min,
            box_max
        );

        nodes[1] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(d.x, 0, 0),
            box_max + glm::vec3(d.x, 0, 0)
        );

        nodes[2] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(0, 0, d.z),
            box_max + glm::vec3(0, 0, d.z)
        );

        nodes[3] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(d.x, 0, d.z),
            box_max + glm::vec3(d.x, 0, d.z)
        );

        nodes[4] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(0, d.y, 0),
            box_max + glm::vec3(0, d.y, 0)
        );

        nodes[5] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(d.x, d.y, 0),
            box_max + glm::vec3(d.x, d.y, 0)
        );

        nodes[6] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(0, d.y, d.z),
            box_max + glm::vec3(0, d.y, d.z)
        );

        nodes[7] = std::make_unique<OctreeNode>(
            box_min + glm::vec3(d.x, d.y, d.z),
            box_max + glm::vec3(d.x, d.y, d.z)
        );

        this->nodes = std::move(nodes);
    }

}
