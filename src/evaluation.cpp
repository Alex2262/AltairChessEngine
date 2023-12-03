
#include <algorithm>
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

    for (int color = 0; color < 2; color++) {
        for (int piece_type = 0; piece_type < 6; piece_type++) {
            evaluation_information.piece_counts[color][piece_type] = static_cast<int>(popcount(
                    position.get_pieces(static_cast<PieceType>(piece_type), static_cast<Color>(color))
                    ));

            evaluation_information.piece_relative_occupancies[color][piece_type] = position.all_pieces;
        }
    }

    BITBOARD white_diagonal_sliders = position.get_pieces(BISHOP, WHITE) | position.get_pieces(QUEEN, WHITE);
    BITBOARD black_diagonal_sliders = position.get_pieces(BISHOP, BLACK) | position.get_pieces(QUEEN, BLACK);

    BITBOARD white_orthogonal_sliders = position.get_pieces(ROOK, WHITE) | position.get_pieces(QUEEN, WHITE);
    BITBOARD black_orthogonal_sliders = position.get_pieces(ROOK, BLACK) | position.get_pieces(QUEEN, BLACK);

    evaluation_information.piece_relative_occupancies[WHITE][BISHOP] ^= white_diagonal_sliders;
    evaluation_information.piece_relative_occupancies[BLACK][BISHOP] ^= black_diagonal_sliders;

    evaluation_information.piece_relative_occupancies[WHITE][ROOK] ^= white_orthogonal_sliders;
    evaluation_information.piece_relative_occupancies[BLACK][ROOK] ^= black_orthogonal_sliders;

    evaluation_information.piece_relative_occupancies[WHITE][QUEEN] ^=
            white_diagonal_sliders | white_orthogonal_sliders;
    evaluation_information.piece_relative_occupancies[BLACK][QUEEN] ^=
            black_diagonal_sliders | black_orthogonal_sliders;
}

Square get_white_relative_square(Square square, Color color) {
    return static_cast<Square>(square ^ (color * 56));
}

Square get_black_relative_square(Square square, Color color) {
    return static_cast<Square>(square ^ (~color * 56));
}

SCORE_TYPE evaluate_king_pawn(File file, Color color, EvaluationInformation& evaluation_information) {
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

    Direction up = color == WHITE ? NORTH : SOUTH;

    SCORE_TYPE score = 0;
    BITBOARD our_pawns = evaluation_information.pawns[color];
    BITBOARD opp_pawns = evaluation_information.pawns[~color];
    BITBOARD phalanx_pawns = our_pawns & shift<WEST>(our_pawns);
    BITBOARD pawn_threats = evaluation_information.pawn_attacks[color] & evaluation_information.pieces[~color];

    // Doubled Pawns
    BITBOARD doubled_pawns = our_pawns & shift<NORTH>(our_pawns);
    score += static_cast<SCORE_TYPE>(popcount(doubled_pawns)) * DOUBLED_PAWN_PENALTY;

    // KING RING ATTACKS
    BITBOARD king_ring_attacks_1 = evaluation_information.pawn_attacks[color] &
                                   king_ring_zone.masks[0][evaluation_information.king_squares[~color]];
    BITBOARD king_ring_attacks_2 = evaluation_information.pawn_attacks[color] &
                                   king_ring_zone.masks[1][evaluation_information.king_squares[~color]];

    score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_1)) * KING_RING_ATTACKS[0][PAWN];
    score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_2)) * KING_RING_ATTACKS[1][PAWN];

    evaluation_information.total_king_ring_attacks[color] +=
            static_cast<int>(2 * popcount(king_ring_attacks_1) + popcount(king_ring_attacks_2));

    // MAIN PAWN EVAL
    while (our_pawns) {
        Square square = poplsb(our_pawns);
        BITBOARD bb_square = from_square(square);

        Square black_relative_square = get_black_relative_square(square, color);
        Rank relative_rank = rank_of(get_white_relative_square(square, color));

        score += PIECE_VALUES[PAWN];

        score += PIECE_SQUARE_TABLES[PAWN][black_relative_square];

        // PASSED PAWN
        if (!(passed_pawn_masks[color][square] & opp_pawns)) {
			auto protectors = popcount(evaluation_information.pawns[color] & get_piece_attacks(get_piece(PAWN, ~color), square, 0));

            score += PASSED_PAWN_BONUSES[protectors][relative_rank];
            evaluation_information.passed_pawn_count[color]++;

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

            // Square of the Pawn
            auto promotion_square = get_black_relative_square(static_cast<Square>(square % 8), color);
            int promotion_distance = get_chebyshev_distance(square, promotion_square);
            int promotion_king_distance = get_chebyshev_distance(evaluation_information.king_squares[~color], promotion_square);

            if (std::min(promotion_distance, 5) < promotion_king_distance - (position.side != color)) {
                score += SQUARE_OF_THE_PAWN;
            }

            // Passed King Distances
            int our_king_distance = get_chebyshev_distance(square, evaluation_information.king_squares[ color]);
            int opp_king_distance = get_chebyshev_distance(square, evaluation_information.king_squares[~color]);

            score += our_king_distance * PASSED_OUR_DISTANCE[relative_rank];
            score += opp_king_distance * PASSED_OPP_DISTANCE[relative_rank];
        }

        BITBOARD isolated_pawn_mask = fill<SOUTH>(fill<NORTH>(shift<WEST>(bb_square) | shift<EAST>(bb_square)));

        // We can use the passed pawn mask for the opposite color including the two squares next to it
        BITBOARD backwards_pawn_mask = passed_pawn_masks[~color][square]
                                       | (shift<WEST>(bb_square)) | (shift<EAST>(bb_square));

        // ISOLATED PAWN
        if (!(isolated_pawn_mask & evaluation_information.pawns[color])) {
            score += ISOLATED_PAWN_PENALTY;
        }

            // BACKWARDS PAWN
            // We don't count this as an isolated pawn, and we ensure that the backwards pawn is prevented from
            // advancing by an opposing pawn
        else if (!(backwards_pawn_mask & evaluation_information.pawns[color]) &&
                 (from_square(square + up) & evaluation_information.pawn_attacks[~color])) {

            bool open = !(fill(up, bb_square) & evaluation_information.pawns[~color]);
            score += BACKWARDS_PAWN_PENALTY[open];
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

        BITBOARD piece_attacks = get_regular_piece_type_attacks<piece_type>(square,
                                    evaluation_information.piece_relative_occupancies[color][piece_type]);

        if constexpr (piece_type != KING) {
            // MOBILITY
            BITBOARD mobility = piece_attacks &
                                (~evaluation_information.pieces[color]) &
                                (~evaluation_information.pawn_attacks[~color]);

            score += MOBILITY_VALUES[piece_type - 1][popcount(mobility)];

            // KING RING ATTACKS
            BITBOARD king_ring_attacks_1 = piece_attacks & king_ring_zone.masks[0][evaluation_information.king_squares[~color]];
            BITBOARD king_ring_attacks_2 = piece_attacks & king_ring_zone.masks[1][evaluation_information.king_squares[~color]];

            score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_1)) * KING_RING_ATTACKS[0][piece_type];
            score += static_cast<SCORE_TYPE>(popcount(king_ring_attacks_2)) * KING_RING_ATTACKS[1][piece_type];

            evaluation_information.total_king_ring_attacks[color] +=
                    static_cast<int>(2 * popcount(king_ring_attacks_1) + popcount(king_ring_attacks_2));

            // OPPONENT KING TROPISM
            int distance_to_opp_king = get_manhattan_distance(square, evaluation_information.king_squares[~color]);
            score += OPP_KING_TROPISM[piece_type] * distance_to_opp_king;


            // OUR KING TROPISM
            int distance_to_our_king = get_manhattan_distance(square, evaluation_information.king_squares[color]);
            score += OUR_KING_TROPISM[piece_type] * distance_to_our_king;
        }

        // Only King
        else {
            File file = file_of(square);
            if (file <= 2) {  // Queen side: Files A, B, C  (0, 1, 2)
                score += evaluate_king_pawn(0, color, evaluation_information);
                score += evaluate_king_pawn(1, color, evaluation_information);
                score += evaluate_king_pawn(2, color, evaluation_information);
            }

            else if (file >= 5) {  // King side: Files F, G, H  (5, 6, 7)
                score += evaluate_king_pawn(5, color, evaluation_information);
                score += evaluate_king_pawn(6, color, evaluation_information);
                score += evaluate_king_pawn(7, color, evaluation_information);
            }
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


double evaluate_drawishness(Position& position, EvaluationInformation& evaluation_information) {

    // This function returns a decimal from 0.0 - 1.0 that will be used to scale the total evaluation

    // Get material counts
    const SCORE_TYPE white_material = evaluation_information.piece_counts[WHITE][PAWN] * CANONICAL_PIECE_VALUES[PAWN] +
                                      evaluation_information.piece_counts[WHITE][KNIGHT] * CANONICAL_PIECE_VALUES[KNIGHT] +
                                      evaluation_information.piece_counts[WHITE][BISHOP] * CANONICAL_PIECE_VALUES[BISHOP] +
                                      evaluation_information.piece_counts[WHITE][ROOK] * CANONICAL_PIECE_VALUES[ROOK] +
                                      evaluation_information.piece_counts[WHITE][QUEEN] * CANONICAL_PIECE_VALUES[QUEEN];

    const SCORE_TYPE black_material = evaluation_information.piece_counts[BLACK][PAWN] * CANONICAL_PIECE_VALUES[PAWN] +
                                      evaluation_information.piece_counts[BLACK][KNIGHT] * CANONICAL_PIECE_VALUES[KNIGHT] +
                                      evaluation_information.piece_counts[BLACK][BISHOP] * CANONICAL_PIECE_VALUES[BISHOP] +
                                      evaluation_information.piece_counts[BLACK][ROOK] * CANONICAL_PIECE_VALUES[ROOK] +
                                      evaluation_information.piece_counts[BLACK][QUEEN] * CANONICAL_PIECE_VALUES[QUEEN];

    // const SCORE_TYPE white_material_non_pawns = white_material - evaluation_information.piece_counts[WHITE][PAWN] * CANONICAL_PIECE_VALUES[PAWN];
    // const SCORE_TYPE black_material_non_pawns = black_material - evaluation_information.piece_counts[BLACK][PAWN] * CANONICAL_PIECE_VALUES[PAWN];

    Color more_material_side = white_material >= black_material ? WHITE : BLACK;
    Color less_material_side = ~more_material_side;

    SCORE_TYPE more_material = std::max(white_material, black_material);
    SCORE_TYPE less_material = std::min(white_material, black_material);

    // SCORE_TYPE more_material_non_pawns = more_material_side == WHITE ? white_material_non_pawns : black_material_non_pawns;
    // SCORE_TYPE less_material_non_pawns = less_material_side == WHITE ? white_material_non_pawns : black_material_non_pawns;

    BITBOARD strong_side_pawns = position.get_pieces(PAWN, more_material_side);
    BITBOARD weak_side_pawns   = position.get_pieces(PAWN, less_material_side);

    double base = 1.0;

    // Low material difference scaling
    if (!strong_side_pawns && more_material - less_material <= MAX_MINOR_PIECE_VALUE)
        base = std::clamp((more_material - less_material) / 780.0 + popcount(weak_side_pawns) * 0.12, 0.1, 1.0);

    // If there are too many rooks, don't evaluate for a special draw case
    if (evaluation_information.piece_counts[WHITE][ROOK] + evaluation_information.piece_counts[BLACK][ROOK] >= 3) return base;

    // There is a queen on the board
    if (evaluation_information.piece_counts[WHITE][QUEEN] + evaluation_information.piece_counts[BLACK][QUEEN] >= 1) {
        // Guard clause
        if (more_material > CANONICAL_PIECE_VALUES[QUEEN]) return base;

        // Queen vs rook + knight, queen vs rook + bishop, etc.
        if (less_material >= CANONICAL_PIECE_VALUES[ROOK] + MIN_MINOR_PIECE_VALUE) return 0.03;

        // Queen vs two bishops, queen vs two knights, queen vs bishop + knight, etc.
        if (less_material >= 2 * MIN_MINOR_PIECE_VALUE) return 0.25;

        // Queen vs rook + pawn, possible fortress
        if (less_material >= CANONICAL_PIECE_VALUES[ROOK] + CANONICAL_PIECE_VALUES[PAWN]) return 0.6;

        return base;
    }

    // There are pawns on the board
    if (evaluation_information.piece_counts[WHITE][PAWN] + evaluation_information.piece_counts[BLACK][PAWN] >= 1) {

        // Single pawn imbalance drawish endgames
        if (evaluation_information.piece_counts[WHITE][PAWN] + evaluation_information.piece_counts[BLACK][PAWN] == 1) {

            // Pawn vs 2 knights
            if (more_material == 2 * CANONICAL_PIECE_VALUES[KNIGHT]) return 0.01;

            // Pawn + 2 knights vs minor piece / rook
            if (more_material == CANONICAL_PIECE_VALUES[PAWN] + 2 * CANONICAL_PIECE_VALUES[KNIGHT] &&
                less_material >= MIN_MINOR_PIECE_VALUE) {
                return 0.27;
            }

            // Pawn vs minor piece
            if (less_material == CANONICAL_PIECE_VALUES[PAWN] && more_material <= MAX_MINOR_PIECE_VALUE) return 0.02;

            // Pawn + minor vs minor
            if (less_material >= MIN_MINOR_PIECE_VALUE && more_material <= CANONICAL_PIECE_VALUES[PAWN] + MAX_MINOR_PIECE_VALUE) return 0.19;

            // Pawn + minor vs rook or Pawn + minor vs 2 minor pieces
            if (less_material >= CANONICAL_PIECE_VALUES[PAWN] + MIN_MINOR_PIECE_VALUE && more_material <= 2 * MAX_MINOR_PIECE_VALUE &&
                evaluation_information.piece_counts[less_material_side][PAWN] == 1) return 0.1;

            // Pawn + rook vs rook + minor
            if (less_material >= CANONICAL_PIECE_VALUES[PAWN] + CANONICAL_PIECE_VALUES[ROOK] &&
                more_material <= CANONICAL_PIECE_VALUES[ROOK] + MAX_MINOR_PIECE_VALUE) return 0.1;

            // Wrong Colored Bishop
            if (less_material == 0 && more_material == CANONICAL_PIECE_VALUES[BISHOP] + CANONICAL_PIECE_VALUES[PAWN]) {
                BITBOARD pawn_bitboard = evaluation_information.pawns[more_material_side];

                // Pawn is a rook pawn
                if (pawn_bitboard & (MASK_FILE[FILE_A] | MASK_FILE[FILE_H])) {

                    Square promotion_square = get_black_relative_square(static_cast<Square>(lsb(pawn_bitboard) % 8),
                                                                        more_material_side);

                    bool king_in_reach = position.get_pieces(KING, less_material_side) &
                                         (king_ring_zone.masks[0][promotion_square] | from_square(promotion_square));

                    bool wrong_colored_bishop = !same_color(promotion_square,
                                                            static_cast<Square>(lsb(position.get_pieces(BISHOP,
                                                                                                        more_material_side))));

                    if (king_in_reach && wrong_colored_bishop) return 0.0;
                }
            }
        }

        // Double pawn imbalance drawish endgames
        if (evaluation_information.piece_counts[WHITE][PAWN] + evaluation_information.piece_counts[BLACK][PAWN] == 2) {

            // Two Pawns vs Minor Piece (Search should cover the case where two pawns will promote)
            if (less_material == 2 * CANONICAL_PIECE_VALUES[PAWN] && more_material <= MAX_MINOR_PIECE_VALUE) return 0.3;

            // Two Pawns vs Two Knights (Search should cover the case where two pawns will promote)
            if (less_material == 2 * CANONICAL_PIECE_VALUES[PAWN] && more_material == 2 * CANONICAL_PIECE_VALUES[KNIGHT]) return 0.3;

        }

        // if (evaluation_information.piece_counts[WHITE][KNIGHT] + evaluation_information.piece_counts[WHITE][ROOK] +
        //     evaluation_information.piece_counts[BLACK][KNIGHT] + evaluation_information.piece_counts[BLACK][ROOK] >= 1) return 1.0;

        return base;
    }

    // At this point, we know there are no queens on the board, no pawns on the board,
    // and less than or equal to 2 rooks.

    // Always a draw when the side with more material has less than or equal to a minor piece
    if (more_material <= MAX_MINOR_PIECE_VALUE) return 0.0;

    // When the side with more material has less than or equal to two minor pieces
    if (more_material <= 2 * MAX_MINOR_PIECE_VALUE) {

        // With only 2 knights, it's impossible to checkmate
        if (evaluation_information.piece_counts[WHITE][KNIGHT] == 2 || evaluation_information.piece_counts[BLACK][KNIGHT] == 2)
            return 0.0;

        // If one of them has 0 pieces we know that due to the check above, at least one of has more than
        // a bishop's worth of material, or else it would have returned 0.0, and thus it would be a win.
        // Either the player that doesn't have 0 material has two bishops, a bishop and knight, or a rook.
        // All of these are wins.
        if (less_material == 0) {
            return 1.0;
        }

        // Here we know they both do not have 0 material, and they cannot have pawns or queens,
        // this means they either have a rook, and the other player has a minor piece,
        // or this means one player has two minor pieces, and the other players has one minor piece.
        return 0.1 + (more_material - less_material) / 1800.0;
    }

    // Rook + Minor piece imbalances
    if (more_material <= CANONICAL_PIECE_VALUES[ROOK] + MAX_MINOR_PIECE_VALUE) {
        if (less_material >= 2 * MIN_MINOR_PIECE_VALUE) return 0.09;
        if (less_material == CANONICAL_PIECE_VALUES[ROOK]) return 0.14;
    }

    return base;

}


double evaluate_opposite_colored_bishop_endgames(Position& position, EvaluationInformation& evaluation_information) {

    bool opposite_colored_bishops = evaluation_information.piece_counts[WHITE][BISHOP] == 1 &&
                                    evaluation_information.piece_counts[BLACK][BISHOP] == 1 &&
                                    !same_color(static_cast<Square>(lsb(position.get_pieces(BISHOP, WHITE))),
                                                static_cast<Square>(lsb(position.get_pieces(BISHOP, BLACK))));

    if (opposite_colored_bishops &&
        evaluation_information.piece_counts[WHITE][QUEEN] + evaluation_information.piece_counts[BLACK][QUEEN] +
        evaluation_information.piece_counts[WHITE][KNIGHT] + evaluation_information.piece_counts[BLACK][KNIGHT] +
        evaluation_information.piece_counts[WHITE][ROOK] + evaluation_information.piece_counts[BLACK][ROOK] == 0 &&
        evaluation_information.piece_counts[WHITE][PAWN] + evaluation_information.piece_counts[BLACK][PAWN] >= 1) {

        Color more_pawns_side = (evaluation_information.piece_counts[WHITE][PAWN] >
                                 evaluation_information.piece_counts[BLACK][PAWN]) ? WHITE : BLACK;

        int pawn_difference = evaluation_information.piece_counts[more_pawns_side][PAWN] -
                              evaluation_information.piece_counts[~more_pawns_side][PAWN];

        if (pawn_difference <= 1) return std::min(0.13 +
                                                  evaluation_information.passed_pawn_count[more_pawns_side] *
                                                  evaluation_information.passed_pawn_count[more_pawns_side] * 0.14, 1.0);

        if (pawn_difference >= 3) return std::min(evaluation_information.passed_pawn_count[more_pawns_side] * 0.38
                                                  + pawn_difference * 0.04, 1.0);

        // Pawn Difference must equal two here
        if (evaluation_information.passed_pawn_count[more_pawns_side] >= 3) return 1.0;

        if (evaluation_information.piece_counts[more_pawns_side][PAWN] > 2)
            return std::min(0.2 + evaluation_information.passed_pawn_count[more_pawns_side] *
                                  evaluation_information.passed_pawn_count[more_pawns_side] * 0.14, 1.0);

        BITBOARD more_pawns_bitboard = position.get_pieces(PAWN, more_pawns_side);

        // There are only two pawns here, and they must be passed
        auto pawn_1 = static_cast<Square>(lsb(more_pawns_bitboard));
        auto pawn_2 = static_cast<Square>(msb(more_pawns_bitboard));

        int file_difference = abs(static_cast<int>(file_of(pawn_1)) - static_cast<int>(file_of(pawn_2))) - 1;
        if (file_difference > 2) return 0.85;

        if (file_difference == 1) return 0.1;
        if (file_difference == 2) {
            if (more_pawns_bitboard & (MASK_FILE[FILE_A] | MASK_FILE[FILE_H])) return 0.05;
            if (more_pawns_bitboard & (MASK_FILE[FILE_B] | MASK_FILE[FILE_G])) return 0.15;
            return 0.7;
        }

        // Pawns must be connected here
        if (more_pawns_bitboard & (MASK_FILE[FILE_A] | MASK_FILE[FILE_H])) return 0.05;
        if (more_pawns_bitboard & (more_pawns_side == WHITE ? MASK_RANK[RANK_6] : MASK_RANK[RANK_3])) return 0.95;

        return 0.15;
    }

    return 1.0;
}


SCORE_TYPE evaluate_classic(Position& position) {

    EvaluationInformation evaluation_information{};
    initialize_evaluation_information(position, evaluation_information);

    double drawishness = evaluate_drawishness(position, evaluation_information);
    if (drawishness == 0.0) return 0;

    SCORE_TYPE score = 0;

    score += evaluate_pieces(position, evaluation_information);

    evaluation_information.total_king_ring_attacks[WHITE] = std::min<int>(evaluation_information.total_king_ring_attacks[WHITE], 39);
    evaluation_information.total_king_ring_attacks[BLACK] = std::min<int>(evaluation_information.total_king_ring_attacks[BLACK], 39);

    score += TOTAL_KING_RING_ATTACKS[evaluation_information.total_king_ring_attacks[WHITE]];
    score -= TOTAL_KING_RING_ATTACKS[evaluation_information.total_king_ring_attacks[BLACK]];

    score += (position.side * -2 + 1) * TEMPO_BONUS;

    evaluation_information.game_phase = std::min(evaluation_information.game_phase, 24);

    SCORE_TYPE evaluation = (mg_score(score) * evaluation_information.game_phase +
            eg_score(score) * (24 - evaluation_information.game_phase)) / 24;

    double opposite_colored_bishop_scale_factor = evaluate_opposite_colored_bishop_endgames(position, evaluation_information);

    evaluation = static_cast<SCORE_TYPE>(evaluation * drawishness * opposite_colored_bishop_scale_factor);

    return (position.side * -2 + 1) * evaluation;

}
