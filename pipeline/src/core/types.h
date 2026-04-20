#pragma once

#include <cstdint>
#include <array>
#include <string>

namespace pipeline {

// Color
enum Color : int {
    WHITE = 0,
    BLACK = 1,
};

constexpr Color operator~(Color c) {
    return Color(c ^ 1);
}

// Piece types (matches engine)
constexpr uint32_t N_PIECES = 13;

enum Piece : uint32_t {
    WHITE_PAWN = 0,
    WHITE_KNIGHT = 1,
    WHITE_BISHOP = 2,
    WHITE_ROOK = 3,
    WHITE_QUEEN = 4,
    WHITE_KING = 5,
    BLACK_PAWN = 6,
    BLACK_KNIGHT = 7,
    BLACK_BISHOP = 8,
    BLACK_ROOK = 9,
    BLACK_QUEEN = 10,
    BLACK_KING = 11,
    EMPTY = 12,
};

constexpr int COLOR_OFFSET = 6;
constexpr uint8_t WHITE_OO  = 1;
constexpr uint8_t WHITE_OOO = 2;
constexpr uint8_t BLACK_OO  = 4;
constexpr uint8_t BLACK_OOO = 8;

enum PieceType : uint32_t {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5,
    NONE = 6,
};

constexpr inline PieceType get_piece_type(Piece piece) {
    return static_cast<PieceType>(piece % COLOR_OFFSET);
}

constexpr inline Piece get_piece(PieceType piece_type, Color color) {
    return static_cast<Piece>(static_cast<int>(piece_type) + static_cast<int>(color * COLOR_OFFSET));
}

constexpr inline Color get_color(Piece piece) {
    return static_cast<Color>(piece / COLOR_OFFSET);
}

// Square
constexpr int N_SQUARES = 64;

enum Square : uint32_t {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    NO_SQUARE = 64
};

constexpr inline int square_file(Square sq) { return sq % 8; }
constexpr inline int square_rank(Square sq) { return sq / 8; }
constexpr inline Square make_square(int file, int rank) { return static_cast<Square>(rank * 8 + file); }

// File and Rank constants
constexpr int FILE_A = 0, FILE_B = 1, FILE_C = 2, FILE_D = 3;
constexpr int FILE_E = 4, FILE_F = 5, FILE_G = 6, FILE_H = 7;
constexpr int RANK_1 = 0, RANK_2 = 1, RANK_3 = 2, RANK_4 = 3;
constexpr int RANK_5 = 4, RANK_6 = 5, RANK_7 = 6, RANK_8 = 7;

// Piece character mapping
constexpr char PIECE_CHARS[12] = {
    'P', 'N', 'B', 'R', 'Q', 'K',  // White
    'p', 'n', 'b', 'r', 'q', 'k'   // Black
};

constexpr inline Piece piece_from_char(const char c) {
    switch (c) {
        case 'P': return WHITE_PAWN;
        case 'N': return WHITE_KNIGHT;
        case 'B': return WHITE_BISHOP;
        case 'R': return WHITE_ROOK;
        case 'Q': return WHITE_QUEEN;
        case 'K': return WHITE_KING;
        case 'p': return BLACK_PAWN;
        case 'n': return BLACK_KNIGHT;
        case 'b': return BLACK_BISHOP;
        case 'r': return BLACK_ROOK;
        case 'q': return BLACK_QUEEN;
        case 'k': return BLACK_KING;
        default: return EMPTY;
    }
}

// Hash type
using Hash = uint64_t;

// WDL values
enum class WDL : uint8_t {
    LOSS = 0,
    DRAW = 1,
    WIN = 2,
};

// Split types
enum class Split : uint8_t {
    TRAIN = 0,
    VAL = 1,
    TEST = 2,
};

inline std::string split_to_string(Split s) {
    switch (s) {
        case Split::TRAIN: return "train";
        case Split::VAL: return "val";
        case Split::TEST: return "test";
    }
    return "unknown";
}

} // namespace pipeline
