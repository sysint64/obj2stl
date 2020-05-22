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

TEST(StlFileFormatTest, test_write_to_bytes) {
}
