//
// Created by Alexander Tian on 6/26/23.
//

#ifndef ALTAIRCHESSENGINE_EVALUATION_H
#define ALTAIRCHESSENGINE_EVALUATION_H

#include "position.h"
#include "constants.h"
#include "types.h"

struct EvaluationInformation {
    int game_phase = 0;

    BITBOARD pawns[2]{};
    BITBOARD pieces[2]{};
    BITBOARD pawn_attacks[2]{};
};

void initialize_evaluation_information(Position& position, EvaluationInformation& evaluation_information);

Square get_white_relative_square(Square square, Color color);
Square get_black_relative_square(Square square, Color color);

SCORE_TYPE evaluate_piece(Position& position, PieceType piece_type, Color color, int& game_phase);
SCORE_TYPE evaluate_pieces(Position& position, int& game_phase);
SCORE_TYPE evaluate(Position& position);

constexpr SCORE_TYPE S(int mg, int eg) {
    return static_cast<SCORE_TYPE>(static_cast<unsigned int>(eg) << 16) + mg;
}

inline int eg_score(SCORE_TYPE s) {
    const auto eg = static_cast<uint16_t>(static_cast<uint32_t>(s + 0x8000) >> 16);

    int16_t v;
    std::memcpy(&v, &eg, sizeof(eg));

    return static_cast<int>(v);
}

inline int mg_score(SCORE_TYPE s) {
    const auto mg = static_cast<uint16_t>(s);

    int16_t v;
    std::memcpy(&v, &mg, sizeof(mg));

    return static_cast<int>(v);
}

#endif //ALTAIRCHESSENGINE_EVALUATION_H
