//
// Created by Alexander Tian on 6/26/23.
//

#include <iostream>
#include "evaluation.h"
#include "evaluation_constants.h"

void initialize_evaluation_information(Position& position, EvaluationInformation& evaluation_information) {
    evaluation_information.game_phase = 0;

    evaluation_information.pawns[WHITE] = position.get_pieces(PAWN, WHITE);
    evaluation_information.pawns[BLACK] = position.get_pieces(PAWN, BLACK);

    evaluation_information.pieces[WHITE] = position.get_pieces(WHITE);
    evaluation_information.pieces[BLACK] = position.get_pieces(BLACK);

    evaluation_information.pawn_attacks[WHITE] = get_pawn_bitboard_attacks(evaluation_information.pawns[WHITE], WHITE);
    evaluation_information.pawn_attacks[BLACK] = get_pawn_bitboard_attacks(evaluation_information.pawns[BLACK], BLACK);
}

Square get_white_relative_square(Square square, Color color) {
    return static_cast<Square>(square ^ (color * 56));
}

Square get_black_relative_square(Square square, Color color) {
    return static_cast<Square>(square ^ (~color * 56));
}

SCORE_TYPE evaluate_pawns(Position& position, Color color, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;
    BITBOARD our_pawns = position.get_pieces(PAWN, color);
    BITBOARD opp_pawns = position.get_pieces(PAWN, ~color);
    BITBOARD phalanx_pawns = our_pawns & shift<WEST>(our_pawns);

    while (our_pawns) {
        Square square = poplsb(our_pawns);
        BITBOARD bb_square = from_square(square);

        Square black_relative_square = get_black_relative_square(square, color);
        Rank relative_rank = rank_of(get_white_relative_square(square, color));

        score += PIECE_VALUES[PAWN];

        score += PIECE_SQUARE_TABLES[PAWN][black_relative_square];

        evaluation_information.game_phase += GAME_PHASE_SCORES[PAWN];

        Direction up = color == WHITE ? NORTH : SOUTH;
        Direction down = color == WHITE ? SOUTH : NORTH;

        // PASSED PAWN
        if (!(passed_pawn_masks[color][square] & opp_pawns)) {
            int protectors = 0;
            if (!(bb_square & MASK_FILE[FILE_A]) &&
                position.board[square + down + WEST] == get_piece(PAWN, color)) protectors++;
            if (!(bb_square & MASK_FILE[FILE_H]) &&
                position.board[square + down + EAST] == get_piece(PAWN, color)) protectors++;

            score += PASSED_PAWN_BONUSES[protectors][relative_rank];

            // BLOCKERS
            auto blocker_square = square + up;
            if (from_square(blocker_square) & evaluation_information.pieces[~color]) {
                score += PASSED_PAWN_BLOCKERS[get_piece_type(position.board[blocker_square], ~color)][rank_of(
                        get_white_relative_square(blocker_square, color))];
            }

            auto blocker_square_2 = blocker_square + up;
            if (relative_rank <= 5 && from_square(blocker_square_2) & evaluation_information.pieces[~color]) {
                score += PASSED_PAWN_BLOCKERS_2[get_piece_type(position.board[blocker_square_2], ~color)][rank_of(
                        get_white_relative_square(blocker_square_2, color))];
            }
        }

        // ISOLATED PAWN
        BITBOARD isolated_pawn_mask = fill<SOUTH>(fill<NORTH>(shift<WEST>(bb_square) | shift<EAST>(bb_square)));
        if (!(isolated_pawn_mask & our_pawns)) {
            score += ISOLATED_PAWN_PENALTY;
        }
    }

    // Phalanx Pawns
    while (phalanx_pawns) {
        Square square = poplsb(phalanx_pawns);
        Rank relative_rank = rank_of(get_white_relative_square(square, color));

        score += PHALANX_PAWN_BONUSES[relative_rank];
    }

    return score;
}

SCORE_TYPE evaluate_piece(Position& position, PieceType piece_type, Color color, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;
    BITBOARD pieces = position.get_pieces(piece_type, color);

    if (piece_type == BISHOP && popcount(pieces) >= 2) {
        score += BISHOP_PAIR_BONUS;
    }

    while (pieces) {
        Square square = poplsb(pieces);
        score += PIECE_VALUES[piece_type];

        score += PIECE_SQUARE_TABLES[piece_type][get_black_relative_square(square, color)];

        evaluation_information.game_phase += GAME_PHASE_SCORES[piece_type];

        BITBOARD piece_attacks = get_piece_attacks(get_piece(piece_type, color), square, position.all_pieces);

        if (piece_type != KING) {
            BITBOARD mobility = piece_attacks &
                                (~evaluation_information.pieces[color]) &
                                (~evaluation_information.pawn_attacks[~color]);

            score += static_cast<SCORE_TYPE>(popcount(mobility)) * MOBILITY_VALUES[piece_type];
        }

        if (piece_type == KING || piece_type == QUEEN || piece_type == ROOK) {
            if (!(MASK_FILE[file_of(square)] & evaluation_information.pawns[color])) {
                if (!(MASK_FILE[file_of(square)] & evaluation_information.pawns[~color])) {
                    score += OPEN_FILE_VALUES[piece_type];
                }
                else {
                    score += SEMI_OPEN_FILE_VALUES[piece_type];
                }
            }
        }

        for (int our_piece = 0; our_piece < 6; our_piece++) {
            score += static_cast<SCORE_TYPE>(popcount(
                    piece_attacks & position.get_pieces(static_cast<PieceType>(our_piece), color))) *
                     PIECE_SUPPORT[piece_type][our_piece];
        }
    }

    return score;
}

SCORE_TYPE evaluate_pieces(Position& position, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;

    score += evaluate_pawns(position, WHITE, evaluation_information);
    score -= evaluate_pawns(position, BLACK, evaluation_information);

    for (int piece = 1; piece < 6; piece++) {
        score += evaluate_piece(position, static_cast<PieceType>(piece), WHITE, evaluation_information);
        score -= evaluate_piece(position, static_cast<PieceType>(piece), BLACK, evaluation_information);
    }

    return score;
}

SCORE_TYPE evaluate(Position& position) {

    EvaluationInformation evaluation_information{};
    initialize_evaluation_information(position, evaluation_information);

    SCORE_TYPE score = 0;

    score += evaluate_pieces(position, evaluation_information);

    score += (position.side * -2 + 1) * TEMPO_BONUS;

    evaluation_information.game_phase = std::min(evaluation_information.game_phase, 24);

    SCORE_TYPE evaluation = (mg_score(score) * evaluation_information.game_phase +
            eg_score(score) * (24 - evaluation_information.game_phase)) / 24;

    return (position.side * -2 + 1) * evaluation;

}
