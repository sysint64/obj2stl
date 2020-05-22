#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <memory>

#include "format.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(BytesWriter, test_write_char) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::LittleEndian
    );

    writer->write_char('a');
    writer->write_char('b');
    writer->write_char('c');

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte('a'),
            std::byte('b'),
            std::byte('c')
        )
    );
}

TEST(BytesWriter, test_write_byte) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::LittleEndian
    );

    writer->write_byte(std::byte(0xff));
    writer->write_byte(std::byte(0x0b));
    writer->write_byte(std::byte(0xca));

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte(0xff),
            std::byte(0x0b),
            std::byte(0xca)
        )
    );
}

TEST(BytesWriter, test_write_bytes) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::LittleEndian
    );

    writer->write_bytes({std::byte(0xff), std::byte(0x0b), std::byte(0xca)});
    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte(0xff),
            std::byte(0x0b),
            std::byte(0xca)
        )
    );
}

TEST(BytesWriter, test_write_string) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::LittleEndian
    );

    writer->write_string("Hello");

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte('H'),
            std::byte('e'),
            std::byte('l'),
            std::byte('l'),
            std::byte('o')
        )
    );
}

TEST(BytesWriter, test_write_int32_t_little_endian) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::LittleEndian
    );

    writer->write_int32_t(0x00000001);

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte(1),
            std::byte(0),
            std::byte(0),
            std::byte(0)
        )
    );
}

TEST(BytesWriter, test_write_int32_t_big_endian) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::BigEndian
    );

    writer->write_int32_t(0x00000001);

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte(0),
            std::byte(0),
            std::byte(0),
            std::byte(1)
        )
    );
}

TEST(BytesWriter, test_write_float_little_endian) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::LittleEndian
    );

    // 0x3f800000
    writer->write_float(1.f);

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte(0),
            std::byte(0),
            std::byte(0x80),
            std::byte(0x3f)
        )
    );
}

TEST(BytesWriter, test_write_float_big_endian) {
    auto writer = std::make_unique<mesh_format::BytesWriter>(
        mesh_format::FileType::Binary,
        mesh_format::ByteOrder::BigEndian
    );

    // 0x3f800000
    writer->write_float(1.f);

    auto bytes = writer->get_bytes();

    ASSERT_THAT(
        bytes,
        testing::ElementsAre(
            std::byte(0x3f),
            std::byte(0x80),
            std::byte(0x0),
            std::byte(0x0)
        )
    );
}
