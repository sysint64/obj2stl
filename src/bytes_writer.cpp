#include "format.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cassert>

namespace mesh_format {
    std::vector<std::byte> const& BytesWriter::get_bytes() {
        return this->bytes;
    }

    bool BytesWriter::is_endian_mismatch() {
        if (this->byte_order == ByteOrder::Native) {
            return false;
        }

        bool mismatch_big_endian = !utils::is_big_endian() &&
            this->byte_order != ByteOrder::BigEndian;

        bool mismatch_little_endian = !utils::is_little_endian() &&
            this->byte_order != ByteOrder::LittleEndian;

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
        } union_value;

        union_value.val = value;

        std::copy(
            union_value.raw.begin(),
            union_value.raw.end(),
            std::back_inserter(bytes)
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
        } union_value;

        union_value.val = value;

        std::copy(
            union_value.raw.begin(),
            union_value.raw.end(),
            std::back_inserter(bytes)
        );
    }

    void BytesWriter::write_byte(std::byte byte) {
        assert(this->file_type == FileType::Binary);
        this->bytes.push_back(byte);
    }

    void BytesWriter::write_char(char ch) {
        this->bytes.push_back(std::byte(ch));
    }

    void BytesWriter::write_string(std::string const& str) {
        std::transform(
            str.begin(),
            str.end(),
            std::back_inserter(bytes),
            [] (const char c) { return std::byte(c); }
        );
    }

}
