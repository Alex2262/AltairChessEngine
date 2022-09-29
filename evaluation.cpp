//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"

SCORE_TYPE evaluate(const Position& position) {

    SCORE_TYPE white_mid_material = 0;
    SCORE_TYPE white_end_material = 0;

    SCORE_TYPE white_mid_scores = 0;
    SCORE_TYPE white_end_scores = 0;

    SCORE_TYPE black_mid_material = 0;
    SCORE_TYPE black_end_material = 0;

    SCORE_TYPE black_mid_scores = 0;
    SCORE_TYPE black_end_scores = 0;

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];

        white_mid_material += PIECE_VALUES[piece];
        white_end_material += PIECE_VALUES[piece];

        white_mid_scores += MIDGAME_PST[piece][MAILBOX_TO_STANDARD[pos]];
        white_end_scores += ENDGAME_PST[piece][MAILBOX_TO_STANDARD[pos]];
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];

        black_mid_material += PIECE_VALUES[piece - BLACK_PAWN];
        black_end_material += PIECE_VALUES[piece - BLACK_PAWN];

        black_mid_scores += MIDGAME_PST[piece - BLACK_PAWN][MAILBOX_TO_STANDARD[pos] ^ 56];
        black_end_scores += ENDGAME_PST[piece - BLACK_PAWN][MAILBOX_TO_STANDARD[pos] ^ 56];
    }

    if (white_mid_material + black_mid_material >= 2600) {
        return (position.side * -2 + 1) *
               ((white_mid_material + white_mid_scores) - (black_mid_material + black_mid_scores));
    } else {
        return (position.side * -2 + 1) *
               ((white_end_material + white_end_scores) - (black_end_material + black_end_scores));
    }
}