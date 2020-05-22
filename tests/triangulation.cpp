#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <memory>

#include "mesh.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// TODO: Should be added test for more complicated geometry
TEST(DummyTriangulationStrategy, test_triangulate) {
    auto triangulation_strategy = std::make_unique<mesh::DummyTriangulationStrategy>();

    std::vector<glm::vec3> vertices {
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(1, 0, 0)
    };
    std::vector<glm::vec3> normals {
        glm::vec3(0, 0, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(1, 0, 0)
    };
    std::vector<glm::vec2> tex_coords {
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
    };

    auto polygon = mesh::Polygon(
        vertices,
        {normals},
        {tex_coords},
        {}
    );

    auto triangles = triangulation_strategy->triangulate(polygon);

    ASSERT_EQ(triangles.size(), 2);
    ASSERT_THAT(
        triangles[0].vertices,
        testing::ElementsAre(
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 1, 0)
        )
    );

    ASSERT_THAT(
        triangles[1].vertices,
        testing::ElementsAre(
            glm::vec3(0, 0, 0),
            glm::vec3(1, 1, 0),
            glm::vec3(1, 0, 0)
        )
    );
}
