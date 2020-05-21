#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>

#include "obj.hpp"
#include "format.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(loadTest, test) {
    auto bytes = utils::load_file_to_bytes("../../tests/resources/box.obj");
    auto obj = obj_file::load_from_bytes(bytes);

    ASSERT_THAT(
        obj.v,
        testing::ElementsAre(
            glm::vec3(1.000000, 1.000000, -1.000000),
            glm::vec3(1.000000, -1.000000, -1.000000),
            glm::vec3(1.000000, 1.000000, 1.000000),
            glm::vec3(1.000000, -1.000000, 1.000000),
            glm::vec3(-1.000000, 1.000000, -1.000000),
            glm::vec3(-1.000000, -1.000000, -1.000000),
            glm::vec3(-1.000000, 1.000000, 1.000000),
            glm::vec3(-1.000000, -1.000000, 1.000000)
        )
    );

    ASSERT_THAT(
        obj.vt,
        testing::ElementsAre(
            glm::vec2(0.625000, 0.500000),
            glm::vec2(0.875000, 0.500000),
            glm::vec2(0.875000, 0.750000),
            glm::vec2(0.625000, 0.750000),
            glm::vec2(0.375000, 0.750000),
            glm::vec2(0.625000, 1.000000),
            glm::vec2(0.375000, 1.000000),
            glm::vec2(0.375000, 0.000000),
            glm::vec2(0.625000, 0.000000),
            glm::vec2(0.625000, 0.250000),
            glm::vec2(0.375000, 0.250000),
            glm::vec2(0.125000, 0.500000),
            glm::vec2(0.375000, 0.500000),
            glm::vec2(0.125000, 0.750000)
        )
    );

    ASSERT_THAT(
        obj.vn,
        testing::ElementsAre(
            glm::vec3(0.0000, 1.0000, 0.0000),
            glm::vec3(0.0000, 0.0000, 1.0000),
            glm::vec3(-1.0000, 0.0000, 0.0000),
            glm::vec3(0.0000, -1.0000, 0.0000),
            glm::vec3(1.0000, 0.0000, 0.0000),
            glm::vec3(0.0000, 0.0000, -1.0000)
        )
    );

    ASSERT_EQ(obj.f.size(), 6);

    ASSERT_THAT(
        obj.f[0].triplets,
        testing::ElementsAre(
            obj_file::Triplet(1, 1, 1),
            obj_file::Triplet(5, 2, 1),
            obj_file::Triplet(7, 3, 1),
            obj_file::Triplet(3, 4, 1)
        )
    );

    ASSERT_THAT(
        obj.f[1].triplets,
        testing::ElementsAre(
            obj_file::Triplet(4, 5, 2),
            obj_file::Triplet(3, 4, 2),
            obj_file::Triplet(7, 6, 2),
            obj_file::Triplet(8, 7, 2)
        )
    );

    ASSERT_THAT(
        obj.f[2].triplets,
        testing::ElementsAre(
            obj_file::Triplet(8, 8, 3),
            obj_file::Triplet(7, 9, 3),
            obj_file::Triplet(5, 10, 3),
            obj_file::Triplet(6, 11, 3)
        )
    );

    ASSERT_THAT(
        obj.f[3].triplets,
        testing::ElementsAre(
            obj_file::Triplet(6, 12, 4),
            obj_file::Triplet(2, 13, 4),
            obj_file::Triplet(4, 5, 4),
            obj_file::Triplet(8, 14, 4)
        )
    );

    ASSERT_THAT(
        obj.f[4].triplets,
        testing::ElementsAre(
            obj_file::Triplet(2, 13, 5),
            obj_file::Triplet(1, 1, 5),
            obj_file::Triplet(3, 4, 5),
            obj_file::Triplet(4, 5, 5)
        )
    );

    ASSERT_THAT(
        obj.f[5].triplets,
        testing::ElementsAre(
            obj_file::Triplet(6, 11, 6),
            obj_file::Triplet(5, 10, 6),
            obj_file::Triplet(1, 1, 6),
            obj_file::Triplet(2, 13, 6)
        )
    );
}
