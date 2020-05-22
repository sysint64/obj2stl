#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <fstream>

#include "obj.hpp"
#include "stl.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(StlMeshWriter, test_write_to_bytes) {
    auto lines = utils::load_text_file_lines("../../tests/resources/box.obj");
    auto obj = obj_file::load_from_string_lines(lines);
    auto layout = obj_file::create_mesh_layout_from_obj(obj);
    auto writer = std::make_unique<stl_file::StlMeshWriter>();
    auto stl_bytes = writer->write(layout);

    std::ofstream outfile(
        "../../tests/resources/generated.stl",
        std::ios::out | std::ios::binary
    );

    outfile.write(stl_bytes.data(), stl_bytes.size());
}
