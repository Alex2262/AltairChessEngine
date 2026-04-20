#pragma once

#include "../core/canonical_position.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace pipeline {

inline constexpr std::string_view SHARD_MAGIC = "ALTR";
inline constexpr uint16_t SHARD_VERSION = 2;
inline constexpr size_t PACKED_BOARD_BYTES = 32;

#pragma pack(push, 1)
struct ShardHeader {
    std::array<char, 4> magic {'A', 'L', 'T', 'R'};
    uint16_t version = SHARD_VERSION;
    uint32_t record_count = 0;
    uint16_t record_size = 0;
    std::array<uint8_t, 4> reserved {};
};

struct PackedBoardRecord {
    std::array<uint8_t, PACKED_BOARD_BYTES> packed_board {};
    uint8_t stm = 0;
    uint8_t wdl = 1;
    int16_t eval = 0;
};
#pragma pack(pop)

static_assert(sizeof(ShardHeader) == 16, "Shard header must be 16 bytes");
static_assert(sizeof(PackedBoardRecord) == 36, "Packed-board record must be 36 bytes");

inline PackedBoardRecord pack_record(const CanonicalPosition& position, const uint8_t stm, const uint8_t wdl, const int16_t eval) {
    PackedBoardRecord record;
    record.stm = stm;
    record.wdl = wdl;
    record.eval = eval;

    for (size_t byte_index = 0; byte_index < PACKED_BOARD_BYTES; ++byte_index) {
        const uint8_t low = static_cast<uint8_t>(position.board[byte_index * 2]);
        const uint8_t high = static_cast<uint8_t>(position.board[byte_index * 2 + 1]);
        record.packed_board[byte_index] = static_cast<uint8_t>(low | (high << 4));
    }

    return record;
}

inline CanonicalPosition unpack_record_board(const PackedBoardRecord& record) {
    CanonicalPosition position;
    for (size_t byte_index = 0; byte_index < PACKED_BOARD_BYTES; ++byte_index) {
        const uint8_t packed = record.packed_board[byte_index];
        position.board[byte_index * 2] = static_cast<Piece>(packed & 0x0F);
        position.board[byte_index * 2 + 1] = static_cast<Piece>((packed >> 4) & 0x0F);
    }
    position.side = record.stm == 0 ? WHITE : BLACK;
    return position;
}

inline uint8_t encode_wdl(const WDL wdl) {
    return static_cast<uint8_t>(wdl);
}

inline uint8_t encode_stm(const Color side) {
    return side == WHITE ? 0 : 1;
}

}  // namespace pipeline
