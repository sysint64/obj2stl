#include "format.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cassert>

namespace mesh_format {
    std::vector<std::byte> const& BytesWriter::get_bytes() {
        return this->bytes;
    }

    std::vector<char> const& BytesWriter::get_data() {
        this->chars.clear();

        std::transform(
            this->bytes.begin(),
            this->bytes.end(),
            std::back_inserter(this->chars),
            [](std::byte byte) { return char(byte); }
        );

        return this->chars;
    }

    void BytesWriter::clear() {
        this->bytes.clear();
    }

    bool BytesWriter::is_endian_mismatch() {
        bool mismatch_big_endian = utils::is_big_endian() &&
            this->byte_order == ByteOrder::LittleEndian;

        bool mismatch_little_endian = utils::is_little_endian() &&
            this->byte_order == ByteOrder::BigEndian;

        return mismatch_big_endian || mismatch_little_endian;
    }

    void BytesWriter::write_int32_t(int32_t value) {
        assert(this->file_type == FileType::Binary);

        if (this->is_endian_mismatch()) {
            utils::swap_endian(value);
        }

        union {
            int32_t val;
            std::array<std::byte, sizeof(int32_t)> raw;
        } union_value {};

        union_value.val = value;

        std::copy(
            union_value.raw.begin(),
            union_value.raw.end(),
            std::back_inserter(this->bytes)
        );
    }

    void BytesWriter::write_float(float value) {
        assert(this->file_type == FileType::Binary);

        if (this->is_endian_mismatch()) {
            utils::swap_endian(value);
        }

        union {
            float val;
            std::array<std::byte, sizeof(int32_t)> raw;
        } union_value {};

        union_value.val = value;

        std::copy(
            union_value.raw.begin(),
            union_value.raw.end(),
            std::back_inserter(this->bytes)
        );
    }

    void BytesWriter::write_byte(std::byte byte) {
        assert(this->file_type == FileType::Binary);
        this->bytes.push_back(byte);
    }

    void BytesWriter::write_bytes(std::vector<std::byte> const& in_bytes) {
        std::copy(
            in_bytes.begin(),
            in_bytes.end(),
            std::back_inserter(this->bytes)
        );
    }

    void BytesWriter::write_char(char ch) {
        this->bytes.push_back(std::byte(ch));
    }

    void BytesWriter::write_string(std::string const& str) {
        std::transform(
            str.begin(),
            str.end(),
            std::back_inserter(this->bytes),
            [] (const char c) { return std::byte(c); }
        );
    }

}
