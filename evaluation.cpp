//
// Created by Alexander Tian on 6/26/23.
//

#include <iostream>
#include "evaluation.h"
#include "evaluation_constants.h"

void initialize_evaluation_information(Position& position, EvaluationInformation& evaluation_information) {
    evaluation_information.game_phase = 0;

    evaluation_information.total_king_ring_attacks[WHITE] = 0;
    evaluation_information.total_king_ring_attacks[BLACK] = 0;

    evaluation_information.king_squares[WHITE] = position.get_king_pos(WHITE);
    evaluation_information.king_squares[BLACK] = position.get_king_pos(BLACK);

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

SCORE_TYPE evaluate_king_pawn(const Position& position, File file, Color color, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;

    // PAWN SHIELD
    BITBOARD file_pawns = evaluation_information.pawns[color] & MASK_FILE[file];
    Square square = file_pawns == 0 ? NO_SQUARE :
                    color == WHITE ? lsb(file_pawns) : msb(file_pawns);

    Rank relative_rank = rank_of(get_white_relative_square(square, color));

    int index = square == NO_SQUARE ? 4 : std::min(static_cast<int>(relative_rank) - 1, 3);

    score += KING_PAWN_SHIELD[index][file];

    // PAWN STORM
    BITBOARD opp_file_pawns = evaluation_information.pawns[~color] & MASK_FILE[file];
    square = opp_file_pawns == 0 ? NO_SQUARE :
             color == WHITE ? lsb(opp_file_pawns) : msb(opp_file_pawns);

    relative_rank = rank_of(get_white_relative_square(square, color));

    // Uses the relative ranks 3-7 (ranks 6 & 7 are combined into one index)
    index = square == NO_SQUARE ? 5 : std::min(static_cast<int>(relative_rank) - 1, 4);

    score += KING_PAWN_STORM[index][file];

    return score;
}

SCORE_TYPE evaluate_pawns(Position& position, Color color, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;
    BITBOARD our_pawns = evaluation_information.pawns[color];
    BITBOARD opp_pawns = evaluation_information.pawns[~color];
    BITBOARD phalanx_pawns = our_pawns & shift<WEST>(our_pawns);
    BITBOARD pawn_threats = evaluation_information.pawn_attacks[color] & evaluation_information.pieces[~color];

    // KING RING ATTACKS
    BITBOARD king_ring_attacks_1 = evaluation_information.pawn_attacks[color] &
                                   king_ring_zone.masks[0][evaluation_information.king_squares[~color]];
    BITBOARD king_ring_attacks_2 = evaluation_information.pawn_attacks[color] &
                                   king_ring_zone.masks[1][evaluation_information.king_squares[~color]];

    score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_1)) * KING_RING_ATTACKS[0][PAWN];
    score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_2)) * KING_RING_ATTACKS[1][PAWN];

    evaluation_information.total_king_ring_attacks[color] += static_cast<int>(popcount(king_ring_attacks_1 | king_ring_attacks_2));

    // MAIN PAWN EVAL
    while (our_pawns) {
        Square square = poplsb(our_pawns);
        BITBOARD bb_square = from_square(square);

        Square black_relative_square = get_black_relative_square(square, color);
        Rank relative_rank = rank_of(get_white_relative_square(square, color));

        score += PIECE_VALUES[PAWN];

        score += PIECE_SQUARE_TABLES[PAWN][black_relative_square];

        // evaluation_information.game_phase += GAME_PHASE_SCORES[PAWN];

        Direction up = color == WHITE ? NORTH : SOUTH;
        // PASSED PAWN
        if (!(passed_pawn_masks[color][square] & opp_pawns)) {
			auto protectors = popcount(evaluation_information.pawns[color] & get_piece_attacks(get_piece(PAWN, ~color), square, 0));

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
        Rank relative_rank = rank_of(get_white_relative_square(poplsb(phalanx_pawns), color));
        score += PHALANX_PAWN_BONUSES[relative_rank];
    }

    while (pawn_threats) {
        score += PIECE_THREATS[PAWN][get_piece_type(position.board[poplsb(pawn_threats)], ~color)];
    }

    return score;
}

template<PieceType piece_type>
SCORE_TYPE evaluate_piece(Position& position, Color color, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;
    BITBOARD pieces = position.get_pieces(piece_type, color);

    if constexpr (piece_type == BISHOP) {
		if (popcount(pieces) >= 2)
			score += BISHOP_PAIR_BONUS;
	}

    while (pieces) {
        Square square = poplsb(pieces);
        score += PIECE_VALUES[piece_type];

        score += PIECE_SQUARE_TABLES[piece_type][get_black_relative_square(square, color)];

        evaluation_information.game_phase += GAME_PHASE_SCORES[piece_type];

        BITBOARD piece_attacks = get_piece_attacks(get_piece(piece_type, color), square, position.all_pieces);

        if constexpr (piece_type != KING) {
            // MOBILITY
            BITBOARD mobility = piece_attacks &
                                (~evaluation_information.pieces[color]) &
                                (~evaluation_information.pawn_attacks[~color]);

            score += static_cast<SCORE_TYPE>(popcount(mobility)) * MOBILITY_VALUES[piece_type];

            // KING RING ATTACKS
            BITBOARD king_ring_attacks_1 = piece_attacks & king_ring_zone.masks[0][evaluation_information.king_squares[~color]];
            BITBOARD king_ring_attacks_2 = piece_attacks & king_ring_zone.masks[1][evaluation_information.king_squares[~color]];

            score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_1)) * KING_RING_ATTACKS[0][piece_type];
            score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_2)) * KING_RING_ATTACKS[1][piece_type];

            evaluation_information.total_king_ring_attacks[color] += static_cast<int>(popcount(king_ring_attacks_1 | king_ring_attacks_2));
        }

        if constexpr (piece_type == KING || piece_type == QUEEN || piece_type == ROOK) {
            if (!(MASK_FILE[file_of(square)] & evaluation_information.pawns[color])) {
                if (!(MASK_FILE[file_of(square)] & evaluation_information.pawns[~color])) {
                    score += OPEN_FILE_VALUES[piece_type];
                }
                else {
                    score += SEMI_OPEN_FILE_VALUES[piece_type];
                }
            }
        }

        if constexpr (piece_type == KING) {
            File file = file_of(square);
            if (file <= 2) {  // Queen side: Files A, B, C  (0, 1, 2)
                score += evaluate_king_pawn(position, 0, color, evaluation_information);
                score += evaluate_king_pawn(position, 1, color, evaluation_information);
                score += evaluate_king_pawn(position, 2, color, evaluation_information);
            }

            else if (file >= 5) {  // King side: Files F, G, H  (5, 6, 7)
                score += evaluate_king_pawn(position, 5, color, evaluation_information);
                score += evaluate_king_pawn(position, 6, color, evaluation_information);
                score += evaluate_king_pawn(position, 7, color, evaluation_information);
            }
        }

        for (int opp_piece = 0; opp_piece < 6; opp_piece++) {
            score += static_cast<SCORE_TYPE>(popcount(
                    piece_attacks & position.get_pieces(static_cast<PieceType>(opp_piece), ~color))) *
                     PIECE_THREATS[piece_type][opp_piece];
        }
    }

    return score;
}

SCORE_TYPE evaluate_pieces(Position& position, EvaluationInformation& evaluation_information) {
    SCORE_TYPE score = 0;

    score += evaluate_pawns(position, WHITE, evaluation_information);
    score -= evaluate_pawns(position, BLACK, evaluation_information);

	score += evaluate_piece<KNIGHT>(position, WHITE, evaluation_information);
	score -= evaluate_piece<KNIGHT>(position, BLACK, evaluation_information);

	score += evaluate_piece<BISHOP>(position, WHITE, evaluation_information);
	score -= evaluate_piece<BISHOP>(position, BLACK, evaluation_information);

	score += evaluate_piece<ROOK>(position, WHITE, evaluation_information);
	score -= evaluate_piece<ROOK>(position, BLACK, evaluation_information);

	score += evaluate_piece<QUEEN>(position, WHITE, evaluation_information);
	score -= evaluate_piece<QUEEN>(position, BLACK, evaluation_information);

	score += evaluate_piece<KING>(position, WHITE, evaluation_information);
	score -= evaluate_piece<KING>(position, BLACK, evaluation_information);

    return score;
}

SCORE_TYPE evaluate(Position& position) {

    EvaluationInformation evaluation_information{};
    initialize_evaluation_information(position, evaluation_information);

    SCORE_TYPE score = 0;

    score += evaluate_pieces(position, evaluation_information);

    evaluation_information.total_king_ring_attacks[WHITE] = std::min<int>(evaluation_information.total_king_ring_attacks[WHITE], 29);
    evaluation_information.total_king_ring_attacks[BLACK] = std::min<int>(evaluation_information.total_king_ring_attacks[BLACK], 29);

    score += TOTAL_KING_RING_ATTACKS[evaluation_information.total_king_ring_attacks[WHITE]];
    score -= TOTAL_KING_RING_ATTACKS[evaluation_information.total_king_ring_attacks[BLACK]];

    score += (position.side * -2 + 1) * TEMPO_BONUS;

    evaluation_information.game_phase = std::min(evaluation_information.game_phase, 24);

    SCORE_TYPE evaluation = (mg_score(score) * evaluation_information.game_phase +
            eg_score(score) * (24 - evaluation_information.game_phase)) / 24;

    return (position.side * -2 + 1) * evaluation;

}
