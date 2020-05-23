#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <fstream>

#include "obj.hpp"
#include "calc.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Transforms, test_apply_transforms_to_layout_pos) {
    auto lines = utils::load_text_file_lines("../../tests/resources/box.obj");
    auto obj = obj_file::load_from_string_lines(lines);
    auto layout = obj_file::create_mesh_layout_from_obj(obj);

    auto transformed_layout = calc::apply_transforms_to_layout(
        layout,
        glm::vec3(10, 0, 0),
        glm::vec3(0, 0, 0),
        glm::vec3(1, 1, 1)
    );

    ASSERT_THAT(
        transformed_layout->vertices,
        testing::ElementsAre(
            glm::vec3(11.000000, 1.000000, -1.000000),
            glm::vec3(11.000000, -1.000000, -1.000000),
            glm::vec3(11.000000, 1.000000, 1.000000),
            glm::vec3(11.000000, -1.000000, 1.000000),
            glm::vec3(9.000000, 1.000000, -1.000000),
            glm::vec3(9.000000, -1.000000, -1.000000),
            glm::vec3(9.000000, 1.000000, 1.000000),
            glm::vec3(9.000000, -1.000000, 1.000000)
        )
    );
}

TEST(Transforms, test_apply_transforms_to_layout_scale) {
    auto lines = utils::load_text_file_lines("../../tests/resources/box.obj");
    auto obj = obj_file::load_from_string_lines(lines);
    auto layout = obj_file::create_mesh_layout_from_obj(obj);

    auto transformed_layout = calc::apply_transforms_to_layout(
        layout,
        glm::vec3(0, 0, 0),
        glm::vec3(0, 0, 0),
        glm::vec3(2, 1, 1)
    );

    ASSERT_THAT(
        transformed_layout->vertices,
        testing::ElementsAre(
            glm::vec3(2.000000, 1.000000, -1.000000),
            glm::vec3(2.000000, -1.000000, -1.000000),
            glm::vec3(2.000000, 1.000000, 1.000000),
            glm::vec3(2.000000, -1.000000, 1.000000),
            glm::vec3(-2.000000, 1.000000, -1.000000),
            glm::vec3(-2.000000, -1.000000, -1.000000),
            glm::vec3(-2.000000, 1.000000, 1.000000),
            glm::vec3(-2.000000, -1.000000, 1.000000)
        )
    );
}

TEST(Transforms, test_apply_transforms_to_layout_pos_and_scale) {
    auto lines = utils::load_text_file_lines("../../tests/resources/box.obj");
    auto obj = obj_file::load_from_string_lines(lines);
    auto layout = obj_file::create_mesh_layout_from_obj(obj);

    auto transformed_layout = calc::apply_transforms_to_layout(
        layout,
        glm::vec3(10, 5, 0),
        glm::vec3(0, 0, 0),
        glm::vec3(2, 1, 1)
    );

    ASSERT_THAT(
        transformed_layout->vertices,
        testing::ElementsAre(
            glm::vec3(12.000000, 6.000000, -1.000000),
            glm::vec3(12.000000, 4.000000, -1.000000),
            glm::vec3(12.000000, 6.000000, 1.000000),
            glm::vec3(12.000000, 4.000000, 1.000000),
            glm::vec3(8.000000, 6.000000, -1.000000),
            glm::vec3(8.000000, 4.000000, -1.000000),
            glm::vec3(8.000000, 6.000000, 1.000000),
            glm::vec3(8.000000, 4.000000, 1.000000)
        )
    );
}
