//
// Created by Alexander Tian on 6/26/23.
//

#include "evaluation.h"
#include "evaluation_constants.h"

Square relative_perspective_square(Square square, Color color) {
    return static_cast<Square>(square ^ (~color * 56));
}

SCORE_TYPE evaluate_piece(Position& position, PieceType piece_type, Color color, int& game_phase) {
    SCORE_TYPE score = 0;
    BITBOARD pieces = position.get_pieces(piece_type, color);

    while (pieces) {
        Square square = poplsb(pieces);
        score += PIECE_VALUES[piece_type];

        score += PIECE_SQUARE_TABLES[piece_type][relative_perspective_square(square, color)];

        game_phase += GAME_PHASE_SCORES[piece_type];
    }

    return score;
}

SCORE_TYPE evaluate_pieces(Position& position, int& game_phase) {
    SCORE_TYPE score = 0;
    for (int piece = 0; piece < 6; piece++) {
        score += evaluate_piece(position, static_cast<PieceType>(piece), WHITE, game_phase);
        score -= evaluate_piece(position, static_cast<PieceType>(piece), BLACK, game_phase);
    }

    return score;
}

SCORE_TYPE evaluate(Position& position) {

    SCORE_TYPE score = 0;
    int game_phase = 0;

    score += evaluate_pieces(position, game_phase);
    game_phase = std::min(game_phase, 24);

    SCORE_TYPE evaluation = (mg_score(score) * game_phase + eg_score(score) * (24 - game_phase)) / 24;

    return (position.side * -2 + 1) * evaluation;

}
