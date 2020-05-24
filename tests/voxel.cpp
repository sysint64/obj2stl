#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <memory>

#include "mesh.hpp"
#include "voxel.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(OctreeNode, test_divide) {
    auto root = std::make_unique<voxel::OctreeNode>(
        glm::vec3(0, 0, 0),
        glm::vec3(1, 1, 1)
    );

    root->divide();

    ASSERT_TRUE(root->nodes);

    // Bottom
    ASSERT_NEAR(root->nodes.value()[0]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->max.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->max.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->max.z, 0.5, 0.01);

    ASSERT_NEAR(root->nodes.value()[1]->min.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->max.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->max.z, 0.5, 0.01);

    ASSERT_NEAR(root->nodes.value()[2]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->min.z, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->max.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->max.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->max.z, 1.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[3]->min.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->min.z, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->max.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->max.z, 1.0, 0.01);

    // Top
    ASSERT_NEAR(root->nodes.value()[4]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->min.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->max.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->max.z, 0.5, 0.01);

    ASSERT_NEAR(root->nodes.value()[5]->min.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->min.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->max.z, 0.5, 0.01);

    ASSERT_NEAR(root->nodes.value()[6]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->min.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->min.z, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->max.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->max.z, 1.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[7]->min.x, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->min.y, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->min.z, 0.5, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->max.z, 1.0, 0.01);
}

TEST(OctreeNode, test_divide_2) {
    auto root = std::make_unique<voxel::OctreeNode>(
        glm::vec3(-1, -1, -1),
        glm::vec3(1, 1, 1)
    );

    root->divide();

    ASSERT_TRUE(root->nodes);

    // Bottom
    ASSERT_NEAR(root->nodes.value()[0]->min.x, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->min.y, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->min.z, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->max.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->max.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[0]->max.z, 0.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[1]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->min.y, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->min.z, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->max.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[1]->max.z, 0.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[2]->min.x, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->min.y, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->max.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->max.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[2]->max.z, 1.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[3]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->min.y, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->max.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[3]->max.z, 1.0, 0.01);

    // Top
    ASSERT_NEAR(root->nodes.value()[4]->min.x, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->min.z, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->max.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[4]->max.z, 0.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[5]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->min.z, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[5]->max.z, 0.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[6]->min.x, -1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->max.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[6]->max.z, 1.0, 0.01);

    ASSERT_NEAR(root->nodes.value()[7]->min.x, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->min.y, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->min.z, 0.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->max.x, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->max.y, 1.0, 0.01);
    ASSERT_NEAR(root->nodes.value()[7]->max.z, 1.0, 0.01);
}
