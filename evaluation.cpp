//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"
#include "evaluation_constants.h"
#include "move.h"
#include "see.h"


void evaluate_king_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE file, bool is_white) {
    SQUARE_TYPE col = file - 1;
    if (is_white) {
        if (position.pawn_rank[0][file] == 3) {
            scores.mid += KING_PAWN_SHIELD_OWN_PENALTIES_MID[0][col];  // Pawn moved one square
            scores.end += KING_PAWN_SHIELD_OWN_PENALTIES_END[0][col];  // Pawn moved one square
        }
        else if (position.pawn_rank[0][file] == 4) {
            scores.mid += KING_PAWN_SHIELD_OWN_PENALTIES_MID[1][col];  // Pawn moved two squares
            scores.end += KING_PAWN_SHIELD_OWN_PENALTIES_END[1][col];  // Pawn moved two squares
        }
        else if (position.pawn_rank[0][file] != 2) {
            scores.mid += KING_PAWN_SHIELD_OWN_PENALTIES_MID[2][col];  // Pawn moved > 2 squares, or it doesn't exist
            scores.end += KING_PAWN_SHIELD_OWN_PENALTIES_END[2][col];  // Pawn moved > 2 squares, or it doesn't exist
        }

        if (position.pawn_rank[1][file] == 0) {
            scores.mid += KING_PAWN_SHIELD_OPP_PENALTIES_MID[0][col];
            scores.end += KING_PAWN_SHIELD_OPP_PENALTIES_END[0][col];
        }
        else if (position.pawn_rank[1][file] == 4) {
            scores.mid += KING_PAWN_SHIELD_OPP_PENALTIES_MID[1][col];  // Enemy pawn is on the 4th rank
            scores.end += KING_PAWN_SHIELD_OPP_PENALTIES_END[1][col];  // Enemy pawn is on the 4th rank
        }
        else if (position.pawn_rank[1][file] == 3) {
            scores.mid += KING_PAWN_SHIELD_OPP_PENALTIES_MID[2][col];  // Enemy pawn is on the 3rd rank
            scores.end += KING_PAWN_SHIELD_OPP_PENALTIES_END[2][col];  // Enemy pawn is on the 3rd rank
        }
    }

    else {
        if (position.pawn_rank[1][file] == 6) {
            scores.mid += KING_PAWN_SHIELD_OWN_PENALTIES_MID[0][col];  // Pawn moved one square
            scores.end += KING_PAWN_SHIELD_OWN_PENALTIES_END[0][col];  // Pawn moved one square
        }
        else if (position.pawn_rank[1][file] == 5) {
            scores.mid += KING_PAWN_SHIELD_OWN_PENALTIES_MID[1][col];  // Pawn moved two squares
            scores.end += KING_PAWN_SHIELD_OWN_PENALTIES_END[1][col];  // Pawn moved two squares
        }
        else if (position.pawn_rank[1][file] != 7) {
            scores.mid += KING_PAWN_SHIELD_OWN_PENALTIES_MID[2][col];  // Pawn moved > 2 squares, or it doesn't exist
            scores.end += KING_PAWN_SHIELD_OWN_PENALTIES_END[2][col];  // Pawn moved > 2 squares, or it doesn't exist
        }

        if (position.pawn_rank[0][file] == 9) {
            scores.mid += KING_PAWN_SHIELD_OPP_PENALTIES_MID[0][col];  // No enemy pawn on this file
            scores.end += KING_PAWN_SHIELD_OPP_PENALTIES_END[0][col];  // No enemy pawn on this file
        }
        else if (position.pawn_rank[0][file] == 5) {
            scores.mid += KING_PAWN_SHIELD_OPP_PENALTIES_MID[1][col];  // Enemy pawn is on the 5th rank
            scores.end += KING_PAWN_SHIELD_OPP_PENALTIES_END[1][col];  // Enemy pawn is on the 5th rank
        }
        else if (position.pawn_rank[0][file] == 6) {
            scores.mid += KING_PAWN_SHIELD_OPP_PENALTIES_MID[2][col];  // Enemy pawn is on the 6th rank
            scores.end += KING_PAWN_SHIELD_OPP_PENALTIES_END[2][col];  // Enemy pawn is on the 6th rank
        }
    }
}


void evaluate_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {

    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

    if (is_white) {

        scores.mid += PAWN_PST_MID[i];
        scores.end += PAWN_PST_END[i];

        // Pawn Protection and Threats
        if (position.board[pos - 9] < BLACK_PAWN) {
            scores.mid += PIECE_SUPPORT_MID[WHITE_PAWN][position.board[pos - 9]];
            scores.end += PIECE_SUPPORT_END[WHITE_PAWN][position.board[pos - 9]];
        } else if (position.board[pos - 9] < EMPTY) {
            scores.mid += PIECE_THREAT_MID[WHITE_PAWN][position.board[pos - 9] - BLACK_PAWN];
            scores.end += PIECE_THREAT_END[WHITE_PAWN][position.board[pos - 9] - BLACK_PAWN];
        }

        if (position.board[pos - 11] < BLACK_PAWN) {
            scores.mid += PIECE_SUPPORT_MID[WHITE_PAWN][position.board[pos - 11]];
            scores.end += PIECE_SUPPORT_END[WHITE_PAWN][position.board[pos - 11]];
        } else if (position.board[pos - 11] < EMPTY) {
            scores.mid += PIECE_THREAT_MID[WHITE_PAWN][position.board[pos - 11] - BLACK_PAWN];
            scores.end += PIECE_THREAT_END[WHITE_PAWN][position.board[pos - 11] - BLACK_PAWN];
        }

        // Doubled pawns. The pawn we are checking is higher in row compared to
        // the least advanced pawn in our column.
        if (row > position.pawn_rank[0][col]) {
            scores.mid += DOUBLED_PAWN_PENALTY_MID;
            scores.end += DOUBLED_PAWN_PENALTY_END;
        }

        // Isolated pawns. We do not have pawns on the columns next to our pawn.
        if (position.pawn_rank[0][col - 1] == 9 && position.pawn_rank[0][col + 1] == 9) {
            // If our opponent does not have a pawn in front of our pawn
            if (position.pawn_rank[1][col] == 0) {
                // The isolated pawn in the middle game is worse if the opponent
                // has the semi open file to attack it.
                scores.mid += ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID;
                scores.end += ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END;
            }
            else {
                scores.mid += ISOLATED_PAWN_PENALTY_MID;
                scores.end += ISOLATED_PAWN_PENALTY_END;
            }
        }

        // Backwards pawn
        else if (row < position.pawn_rank[0][col - 1] && row < position.pawn_rank[0][col + 1]) {
            // In the middle game it's worse to have a very backwards pawn
            // since then, the 'forwards' pawns won't be protected
            scores.mid += BACKWARDS_PAWN_PENALTY_MID;

            // In the end game the backwards pawn should be worse, but if it's very backwards it's not awful.
            scores.end += BACKWARDS_PAWN_PENALTY_END;

            // If there's no enemy pawn in front of our pawn then it's even worse, since
            // we allow outposts and pieces to attack us easily
            if (position.pawn_rank[1][col] == 0) {
                scores.mid += BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID;
                scores.end += BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END;
            }

            // Outposts
            auto outpost_pos = static_cast<SQUARE_TYPE>(pos - 10);
            if (position.board[outpost_pos - 11] == BLACK_PAWN || position.board[outpost_pos - 9] == BLACK_PAWN) {
                scores.mid += OUTPOST_PENALTY_MID;
                scores.end += OUTPOST_PENALTY_END;

                if (position.board[outpost_pos] == BLACK_KNIGHT) {
                    scores.mid += OUTPOST_KNIGHT_PENALTY_MID;
                    scores.end += OUTPOST_KNIGHT_PENALTY_END;
                } else if (position.board[outpost_pos] == BLACK_BISHOP) {
                    scores.mid += OUTPOST_BISHOP_PENALTY_MID;
                    scores.end += OUTPOST_BISHOP_PENALTY_END;
                }
            }
        }

        // Passed Pawn Bonus
        if (row >= position.pawn_rank[1][col - 1] &&
            row >= position.pawn_rank[1][col] &&
            row >= position.pawn_rank[1][col + 1]) {

            int protectors = 0;
            if (position.board[pos + 11] == WHITE_PAWN) protectors++;
            if (position.board[pos + 9] == WHITE_PAWN) protectors++;

            scores.mid += PASSED_PAWN_BONUSES_MID[protectors][row - 1];
            scores.end += PASSED_PAWN_BONUSES_END[protectors][row - 1];

            // Blocker right in front of pawn
            if (WHITE_KING < position.board[pos - 10] && position.board[pos - 10] < EMPTY) {
                scores.mid += BLOCKER_VALUES_MID[position.board[pos - 10] - 6][row - 1];
                scores.end += BLOCKER_VALUES_END[position.board[pos - 10] - 6][row - 1];
            }

            // Blocker two squares in front of pawn
            if (row < 7 && WHITE_KING < position.board[pos - 20] && position.board[pos - 20] < EMPTY) {
                scores.mid += BLOCKER_TWO_SQUARE_VALUES_MID[position.board[pos - 20] - 6][row - 1];
                scores.end += BLOCKER_TWO_SQUARE_VALUES_END[position.board[pos - 20] - 6][row - 1];
            }

            SQUARE_TYPE promotion_square = i % 8;
            int our_distance = get_chebyshev_distance(i, promotion_square);
            int king_distance = get_chebyshev_distance(MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]], promotion_square);

            if (std::min(our_distance, 5) < king_distance - (position.side == BLACK_COLOR)) {
                scores.mid += SQUARE_OF_THE_PAWN_MID;
                scores.end += SQUARE_OF_THE_PAWN_END;
            }
        }

        // Pawn Phalanx
        if (position.board[pos - 1] == WHITE_PAWN) {
            scores.mid += PHALANX_PAWN_BONUS_MID[row - 1];
            scores.end += PHALANX_PAWN_BONUS_END[row - 1];
        }
    }

    else {

        scores.mid += PAWN_PST_MID[i ^ 56];
        scores.end += PAWN_PST_END[i ^ 56];

        // Pawn Protection and Threats
        if (position.board[pos + 9] < BLACK_PAWN) {
            scores.mid += PIECE_THREAT_MID[WHITE_PAWN][position.board[pos + 9]];
            scores.end += PIECE_THREAT_END[WHITE_PAWN][position.board[pos + 9]];
        } else if (position.board[pos + 9] < EMPTY) {
            scores.mid += PIECE_SUPPORT_MID[WHITE_PAWN][position.board[pos + 9] - BLACK_PAWN];
            scores.end += PIECE_SUPPORT_END[WHITE_PAWN][position.board[pos + 9] - BLACK_PAWN];
        }

        if (position.board[pos + 11] < BLACK_PAWN) {
            scores.mid += PIECE_THREAT_MID[WHITE_PAWN][position.board[pos + 11]];
            scores.end += PIECE_THREAT_END[WHITE_PAWN][position.board[pos + 11]];
        } else if (position.board[pos + 11] < EMPTY) {
            scores.mid += PIECE_SUPPORT_MID[WHITE_PAWN][position.board[pos + 11] - BLACK_PAWN];
            scores.end += PIECE_SUPPORT_END[WHITE_PAWN][position.board[pos + 11] - BLACK_PAWN];
        }

        // Doubled pawns. The pawn we are checking is higher in row compared to
        // the least advanced pawn in our column.
        if (row < position.pawn_rank[1][col]) {
            scores.mid += DOUBLED_PAWN_PENALTY_MID;
            scores.end += DOUBLED_PAWN_PENALTY_END;
        }

        // Isolated pawns. We do not have pawns on the columns next to our pawn.
        if (position.pawn_rank[1][col - 1] == 0 && position.pawn_rank[1][col + 1] == 0) {
            // If our opponent does not have a pawn in front of our pawn
            if (position.pawn_rank[0][col] == 9) {
                // The isolated pawn in the middle game is worse if the opponent
                // has the semi open file to attack it.
                scores.mid += ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID;
                scores.end += ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END;
            }
            else {
                scores.mid += ISOLATED_PAWN_PENALTY_MID;
                scores.end += ISOLATED_PAWN_PENALTY_END;
            }
        }

        // Backwards pawn
        else if (row > position.pawn_rank[1][col - 1] && row > position.pawn_rank[1][col + 1]) {
            // In the middle game it's worse to have a very backwards pawn
            // since then, the 'forwards' pawns won't be protected
            scores.mid += BACKWARDS_PAWN_PENALTY_MID;

            // In the end game the backwards pawn should be worse, but if it's very backwards it's not awful.
            scores.end += BACKWARDS_PAWN_PENALTY_END;

            // If there's no enemy pawn in front of our pawn then it's even worse, since
            // we allow outposts and pieces to attack us easily
            if (position.pawn_rank[0][col] == 9) {
                scores.mid += BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID;
                scores.end += BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END;
            }

            // Outposts
            auto outpost_pos = static_cast<SQUARE_TYPE>(pos + 10);
            if (position.board[outpost_pos + 11] == WHITE_PAWN || position.board[outpost_pos + 9] == WHITE_PAWN) {
                scores.mid += OUTPOST_PENALTY_MID;
                scores.end += OUTPOST_PENALTY_END;

                if (position.board[outpost_pos] == WHITE_KNIGHT) {
                    scores.mid += OUTPOST_KNIGHT_PENALTY_MID;
                    scores.end += OUTPOST_KNIGHT_PENALTY_END;
                } else if (position.board[outpost_pos] == WHITE_BISHOP) {
                    scores.mid += OUTPOST_BISHOP_PENALTY_MID;
                    scores.end += OUTPOST_BISHOP_PENALTY_END;
                }
            }
        }

        // Passed Pawn Bonus
        if (row <= position.pawn_rank[0][col - 1] &&
            row <= position.pawn_rank[0][col] &&
            row <= position.pawn_rank[0][col + 1]) {

            int protectors = 0;
            if (position.board[pos - 11] == BLACK_PAWN) protectors++;
            if (position.board[pos - 9] == BLACK_PAWN) protectors++;

            scores.mid += PASSED_PAWN_BONUSES_MID[protectors][8 - row];
            scores.end += PASSED_PAWN_BONUSES_END[protectors][8 - row];

            // Blocker right in front of pawn
            if (position.board[pos + 10] < BLACK_PAWN) {
                scores.mid += BLOCKER_VALUES_MID[position.board[pos + 10]][8 - row];
                scores.end += BLOCKER_VALUES_END[position.board[pos + 10]][8 - row];
            }

            // Blocker two squares in front of pawn
            if (row > 2 && position.board[pos + 20] < BLACK_PAWN) {
                scores.mid += BLOCKER_TWO_SQUARE_VALUES_MID[position.board[pos + 20]][8 - row];
                scores.end += BLOCKER_TWO_SQUARE_VALUES_END[position.board[pos + 20]][8 - row];
            }

            SQUARE_TYPE promotion_square = (i % 8) ^ 56;
            int our_distance = get_chebyshev_distance(i, promotion_square);
            int king_distance = get_chebyshev_distance(MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]], promotion_square);

            if (std::min(our_distance, 5) < king_distance - (position.side == WHITE_COLOR)) {
                scores.mid += SQUARE_OF_THE_PAWN_MID;
                scores.end += SQUARE_OF_THE_PAWN_END;
            }
        }

        // Pawn Phalanx
        if (position.board[pos - 1] == BLACK_PAWN) {
            scores.mid += PHALANX_PAWN_BONUS_MID[8 - row];
            scores.end += PHALANX_PAWN_BONUS_END[8 - row];
        }
    }
}


void evaluate_knight(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SCORE_TYPE mobility = 0;
    int king_ring_attacks[2]{};

    if (is_white) {
        scores.mid += KNIGHT_PST_MID[i];
        scores.end += KNIGHT_PST_END[i];

        // Calculate Mobility
        for (short increment : WHITE_INCREMENTS[WHITE_KNIGHT]) {
            SQUARE_TYPE new_pos = pos + increment;
            PIECE_TYPE occupied = position.board[new_pos];

            if (occupied == PADDING) continue;

            king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                         king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);
            king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                         king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);

            // If there is an enemy pawn controlling this square then we deduct 2.
            if (position.board[new_pos - 11] == BLACK_PAWN || position.board[new_pos - 9] == BLACK_PAWN)
                mobility--;

            mobility++;

            // If we hit a piece of ours, we still add 1 to mobility because
            // that means we are protecting a piece of ours.
            if (occupied < BLACK_PAWN) {
                scores.mid += PIECE_SUPPORT_MID[WHITE_KNIGHT][occupied];
                scores.end += PIECE_SUPPORT_END[WHITE_KNIGHT][occupied];
                continue;
            }

            // Attacking pieces means more pressure which is good
            if (occupied < EMPTY) {
                scores.mid += PIECE_THREAT_MID[WHITE_KNIGHT][occupied - BLACK_PAWN];
                scores.end += PIECE_THREAT_END[WHITE_KNIGHT][occupied - BLACK_PAWN];
                continue;
            }
        }
    }
    else {
        scores.mid += KNIGHT_PST_MID[i ^ 56];
        scores.end += KNIGHT_PST_END[i ^ 56];

        // Calculate Mobility
        for (short increment : BLACK_INCREMENTS[WHITE_KNIGHT]) {
            SQUARE_TYPE new_pos = pos + increment;
            PIECE_TYPE occupied = position.board[new_pos];

            if (occupied == PADDING) continue;

            king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                         king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);
            king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                         king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);

            // If there is an enemy pawn controlling this square then we deduct 2.
            if (position.board[new_pos + 11] == WHITE_PAWN || position.board[new_pos + 9] == WHITE_PAWN)
                mobility--;

            mobility++;

            // If we hit a piece of ours, we still add 1 to mobility because
            // that means we are protecting a piece of ours.
            if (WHITE_KING < occupied && occupied < EMPTY) {
                scores.mid += PIECE_SUPPORT_MID[WHITE_KNIGHT][occupied - BLACK_PAWN];
                scores.end += PIECE_SUPPORT_END[WHITE_KNIGHT][occupied - BLACK_PAWN];
                continue;
            }

            // Attacking pieces means more pressure which is good
            if (occupied < BLACK_PAWN) {
                scores.mid += PIECE_THREAT_MID[WHITE_KNIGHT][occupied];
                scores.end += PIECE_THREAT_END[WHITE_KNIGHT][occupied];
                continue;
            }
        }
    }

    // Knights are good protectors for the king
    SCORE_TYPE distance_to_our_king = get_manhattan_distance(i, MAILBOX_TO_STANDARD[position.king_positions[(!is_white)]]);
    scores.mid += static_cast<SCORE_TYPE>(OWN_KING_DISTANCE_COEFFICIENTS_MID[WHITE_KNIGHT] * distance_to_our_king);
    scores.end += static_cast<SCORE_TYPE>(OWN_KING_DISTANCE_COEFFICIENTS_END[WHITE_KNIGHT] * distance_to_our_king);

    // Knights are also very good at attacking the opponents king
    SCORE_TYPE distance_to_opp_king = get_manhattan_distance(i, MAILBOX_TO_STANDARD[position.king_positions[(is_white)]]);
    scores.mid += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_MID[WHITE_KNIGHT] * distance_to_opp_king);
    scores.end += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_END[WHITE_KNIGHT] * distance_to_opp_king);

    scores.mid += KNIGHT_MOBILITY_MID[mobility];
    scores.end += KNIGHT_MOBILITY_END[mobility];

    scores.mid += king_ring_attacks[0] * KING_RING_ATTACKS_MID[0][WHITE_KNIGHT];
    scores.end += king_ring_attacks[0] * KING_RING_ATTACKS_END[0][WHITE_KNIGHT];

    scores.mid += king_ring_attacks[1] * KING_RING_ATTACKS_MID[1][WHITE_KNIGHT];
    scores.end += king_ring_attacks[1] * KING_RING_ATTACKS_END[1][WHITE_KNIGHT];

    // std::cout << "KNIGHT MOBILITY: " << mobility << std::endl;
}


void evaluate_bishop(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SCORE_TYPE mobility = 0;
    int king_ring_attacks[2]{};

    if (is_white) {
        scores.mid += BISHOP_PST_MID[i];
        scores.end += BISHOP_PST_END[i];

        // Calculate Mobility
        for (short increment : WHITE_INCREMENTS[WHITE_BISHOP]) {
            SQUARE_TYPE new_pos = pos;
            if (!increment) break;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                if (occupied == PADDING) break;

                king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);
                king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);

                // If there is an enemy pawn controlling this square then we deduct 2.
                if (position.board[new_pos - 11] == BLACK_PAWN || position.board[new_pos - 9] == BLACK_PAWN)
                    mobility--;

                mobility++;

                // If we hit a piece of ours, we still add 1 to mobility because
                // that means we are protecting a piece of ours.
                if (occupied < BLACK_PAWN) {
                    scores.mid += PIECE_SUPPORT_MID[WHITE_BISHOP][occupied];
                    scores.end += PIECE_SUPPORT_END[WHITE_BISHOP][occupied];
                    break;
                }

                // Attacking pieces means more pressure which is good
                if (occupied < EMPTY) {
                    scores.mid += PIECE_THREAT_MID[WHITE_BISHOP][occupied - BLACK_PAWN];
                    scores.end += PIECE_THREAT_END[WHITE_BISHOP][occupied - BLACK_PAWN];
                    break;
                }
            }
        }
    }
    else {
        scores.mid += BISHOP_PST_MID[i ^ 56];
        scores.end += BISHOP_PST_END[i ^ 56];

        // Calculate Mobility
        for (short increment : BLACK_INCREMENTS[WHITE_BISHOP]) {
            SQUARE_TYPE new_pos = pos;
            if (!increment) break;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                if (occupied == PADDING) break;

                king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);
                king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);

                // If there is an enemy pawn controlling this square then we deduct 2.
                if (position.board[new_pos + 11] == WHITE_PAWN || position.board[new_pos + 9] == WHITE_PAWN)
                    mobility--;

                mobility++;

                // If we hit a piece of ours, we still add 1 to mobility because
                // that means we are protecting a piece of ours.
                if (WHITE_KING < occupied && occupied < EMPTY) {
                    scores.mid += PIECE_SUPPORT_MID[WHITE_BISHOP][occupied - BLACK_PAWN];
                    scores.end += PIECE_SUPPORT_END[WHITE_BISHOP][occupied - BLACK_PAWN];
                    break;
                }

                // Attacking pieces means more pressure which is good
                if (occupied < BLACK_PAWN) {
                    scores.mid += PIECE_THREAT_MID[WHITE_BISHOP][occupied];
                    scores.end += PIECE_THREAT_END[WHITE_BISHOP][occupied];
                    break;
                }
            }
        }
    }

    SCORE_TYPE distance_to_opp_king = get_manhattan_distance(i, MAILBOX_TO_STANDARD[position.king_positions[(is_white)]]);
    scores.mid += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_MID[WHITE_BISHOP] * distance_to_opp_king);
    scores.end += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_END[WHITE_BISHOP] * distance_to_opp_king);

    scores.mid += BISHOP_MOBILITY_MID[mobility];
    scores.end += BISHOP_MOBILITY_END[mobility];

    scores.mid += king_ring_attacks[0] * KING_RING_ATTACKS_MID[0][WHITE_BISHOP];
    scores.end += king_ring_attacks[0] * KING_RING_ATTACKS_END[0][WHITE_BISHOP];

    scores.mid += king_ring_attacks[1] * KING_RING_ATTACKS_MID[1][WHITE_BISHOP];
    scores.end += king_ring_attacks[1] * KING_RING_ATTACKS_END[1][WHITE_BISHOP];

    // std::cout << "BISHOP MOBILITY: " << mobility << std::endl;
}


void evaluate_rook(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE col = i % 8 + 1;
    SCORE_TYPE mobility = 0;
    int king_ring_attacks[2]{};

    if (is_white) {
        scores.mid += ROOK_PST_MID[i];
        scores.end += ROOK_PST_END[i];

        if (position.pawn_rank[0][col] == 9) {
            if (position.pawn_rank[1][col] == 0) {
                scores.mid += ROOK_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += ROOK_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_SEMI_OPEN_FILE_BONUS_END;
            }
        }

        // Calculate Mobility
        for (short increment : WHITE_INCREMENTS[WHITE_ROOK]) {
            SQUARE_TYPE new_pos = pos;
            if (!increment) break;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                if (occupied == PADDING) break;

                king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);
                king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);

                // If there is an enemy pawn controlling this square then we deduct 2.
                if (position.board[new_pos - 11] == BLACK_PAWN || position.board[new_pos - 9] == BLACK_PAWN)
                    mobility--;

                mobility++;

                // If we hit a piece of ours, we still add 1 to mobility because
                // that means we are protecting a piece of ours.
                if (occupied < BLACK_PAWN) {
                    scores.mid += PIECE_SUPPORT_MID[WHITE_ROOK][occupied];
                    scores.end += PIECE_SUPPORT_END[WHITE_ROOK][occupied];
                    break;
                }

                // If we hit an enemy piece, get a score of 2.
                // An empty square may be even better, so you get a score 3.
                if (occupied < EMPTY) {
                    scores.mid += PIECE_THREAT_MID[WHITE_ROOK][occupied - BLACK_PAWN];
                    scores.end += PIECE_THREAT_END[WHITE_ROOK][occupied - BLACK_PAWN];
                    break;
                }
            }
        }
    }
    else {
        scores.mid += ROOK_PST_MID[i ^ 56];
        scores.end += ROOK_PST_END[i ^ 56];

        if (position.pawn_rank[1][col] == 0) {
            if (position.pawn_rank[0][col] == 9) {
                scores.mid += ROOK_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += ROOK_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_SEMI_OPEN_FILE_BONUS_END;
            }
        }

        // Calculate Mobility
        for (short increment : BLACK_INCREMENTS[WHITE_ROOK]) {
            SQUARE_TYPE new_pos = pos;
            if (!increment) break;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                if (occupied == PADDING) break;

                king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);
                king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);

                // If there is an enemy pawn controlling this square then we deduct 2.
                if (position.board[new_pos + 11] == WHITE_PAWN || position.board[new_pos + 9] == WHITE_PAWN)
                    mobility--;

                mobility++;

                // If we hit a piece of ours, we still add 1 to mobility because
                // that means we are protecting a piece of ours.
                if (WHITE_KING < occupied && occupied < EMPTY) {
                    scores.mid += PIECE_SUPPORT_MID[WHITE_ROOK][occupied - BLACK_PAWN];
                    scores.end += PIECE_SUPPORT_END[WHITE_ROOK][occupied - BLACK_PAWN];
                    break;
                }

                // If we hit an enemy piece, get a score of 2.
                // An empty square may be even better, so you get a score 3.
                if (occupied < BLACK_PAWN) {
                    scores.mid += PIECE_THREAT_MID[WHITE_ROOK][occupied];
                    scores.end += PIECE_THREAT_END[WHITE_ROOK][occupied];
                    break;
                }
            }
        }
    }

    SCORE_TYPE distance_to_opp_king = get_manhattan_distance(i, MAILBOX_TO_STANDARD[position.king_positions[(is_white)]]);
    scores.mid += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_MID[WHITE_ROOK] * distance_to_opp_king);
    scores.end += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_END[WHITE_ROOK] * distance_to_opp_king);

    scores.mid += ROOK_MOBILITY_MID[mobility];
    scores.end += ROOK_MOBILITY_END[mobility];

    scores.mid += king_ring_attacks[0] * KING_RING_ATTACKS_MID[0][WHITE_ROOK];
    scores.end += king_ring_attacks[0] * KING_RING_ATTACKS_END[0][WHITE_ROOK];

    scores.mid += king_ring_attacks[1] * KING_RING_ATTACKS_MID[1][WHITE_ROOK];
    scores.end += king_ring_attacks[1] * KING_RING_ATTACKS_END[1][WHITE_ROOK];

    // std::cout << "ROOK MOBILITY: " << mobility << std::endl;
}


void evaluate_queen(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE col = i % 8 + 1;
    SCORE_TYPE mobility = 0;
    int king_ring_attacks[2]{};

    if (is_white) {
        scores.mid += QUEEN_PST_MID[i];
        scores.end += QUEEN_PST_END[i];

        if (position.pawn_rank[0][col] == 9) {
            if (position.pawn_rank[1][col] == 0) {
                scores.mid += QUEEN_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += QUEEN_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_SEMI_OPEN_FILE_BONUS_END;
            }
        }

        // Calculate Mobility
        for (short increment : WHITE_INCREMENTS[WHITE_QUEEN]) {
            SQUARE_TYPE new_pos = pos;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                if (occupied == PADDING) break;

                king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);
                king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[BLACK_COLOR]]]);

                // If there is an enemy pawn controlling this square then we deduct 2.
                if (position.board[new_pos - 11] == BLACK_PAWN || position.board[new_pos - 9] == BLACK_PAWN)
                    mobility--;

                mobility++;

                // If we hit a piece of ours, we still add 1 to mobility because
                // that means we are protecting a piece of ours.
                if (occupied < BLACK_PAWN) {
                    scores.mid += PIECE_SUPPORT_MID[WHITE_QUEEN][occupied];
                    scores.end += PIECE_SUPPORT_END[WHITE_QUEEN][occupied];
                    break;
                }

                // If we hit an enemy piece, get a score of 2.
                // An empty square may be even better, so you get a score 3.
                if (occupied < EMPTY) {
                    scores.mid += PIECE_THREAT_MID[WHITE_QUEEN][occupied - BLACK_PAWN];
                    scores.end += PIECE_THREAT_END[WHITE_QUEEN][occupied - BLACK_PAWN];
                    break;
                }
            }
        }
    }
    else {
        scores.mid += QUEEN_PST_MID[i ^ 56];
        scores.end += QUEEN_PST_END[i ^ 56];

        if (position.pawn_rank[1][col] == 0) {
            if (position.pawn_rank[0][col] == 9) {
                scores.mid += QUEEN_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += QUEEN_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_SEMI_OPEN_FILE_BONUS_END;
            }
        }

        // Calculate Mobility
        for (short increment : BLACK_INCREMENTS[WHITE_QUEEN]) {
            SQUARE_TYPE new_pos = pos;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                if (occupied == PADDING) break;

                king_ring_attacks[0] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[0][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);
                king_ring_attacks[1] += bool((1ULL << MAILBOX_TO_STANDARD[new_pos]) &
                                             king_ring_zone.masks[1][MAILBOX_TO_STANDARD[position.king_positions[WHITE_COLOR]]]);

                // If there is an enemy pawn controlling this square then we deduct 2.
                if (position.board[new_pos + 11] == WHITE_PAWN || position.board[new_pos + 9] == WHITE_PAWN)
                    mobility--;

                mobility++;

                // If we hit a piece of ours, we still add 1 to mobility because
                // that means we are protecting a piece of ours.
                if (WHITE_KING < occupied && occupied < EMPTY) {
                    scores.mid += PIECE_SUPPORT_MID[WHITE_QUEEN][occupied - BLACK_PAWN];
                    scores.end += PIECE_SUPPORT_END[WHITE_QUEEN][occupied - BLACK_PAWN];
                    break;
                }

                // If we hit an enemy piece, get a score of 2.
                // An empty square may be even better, so you get a score 3.
                if (occupied < BLACK_PAWN) {
                    scores.mid += PIECE_THREAT_MID[WHITE_QUEEN][occupied];
                    scores.end += PIECE_THREAT_END[WHITE_QUEEN][occupied];
                    break;
                }
            }
        }
    }

    SCORE_TYPE distance_to_opp_king = get_manhattan_distance(i, MAILBOX_TO_STANDARD[position.king_positions[(is_white)]]);
    scores.mid += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_MID[WHITE_QUEEN] * distance_to_opp_king);
    scores.end += static_cast<SCORE_TYPE>(OPP_KING_DISTANCE_COEFFICIENTS_END[WHITE_QUEEN] * distance_to_opp_king);

    scores.mid += QUEEN_MOBILITY_MID[mobility];
    scores.end += QUEEN_MOBILITY_END[mobility];

    scores.mid += king_ring_attacks[0] * KING_RING_ATTACKS_MID[0][WHITE_QUEEN];
    scores.end += king_ring_attacks[0] * KING_RING_ATTACKS_END[0][WHITE_QUEEN];

    scores.mid += king_ring_attacks[1] * KING_RING_ATTACKS_MID[1][WHITE_QUEEN];
    scores.end += king_ring_attacks[1] * KING_RING_ATTACKS_END[1][WHITE_QUEEN];

    // std::cout << "QUEEN MOBILITY: " << mobility << std::endl;
}

void evaluate_king(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE col = i % 8 + 1;

    if (is_white) {
        scores.mid += KING_PST_MID[i];
        scores.end += KING_PST_END[i];

        if (col < 4) {  // Queen side
            evaluate_king_pawn(position, scores, 1, true);
            evaluate_king_pawn(position, scores, 2, true);
            evaluate_king_pawn(position, scores, 3, true);
        }
        else if (col > 5) {
            evaluate_king_pawn(position, scores, 8, true);
            evaluate_king_pawn(position, scores, 7, true);
            evaluate_king_pawn(position, scores, 6, true);
        }
        else {
            for (SQUARE_TYPE pawn_file = col - 1; pawn_file < col + 2; pawn_file++) {
                if (position.pawn_rank[0][pawn_file] == 9) {
                    scores.mid += KING_SEMI_OPEN_FILE_PENALTY_MID;
                    scores.end += KING_SEMI_OPEN_FILE_PENALTY_END;
                    if (position.pawn_rank[1][pawn_file] == 0) {
                        scores.mid += KING_OPEN_FILE_PENALTY_MID;
                        scores.end += KING_OPEN_FILE_PENALTY_END;
                    }
                }
            }
        }
    }
    else {
        scores.mid += KING_PST_MID[i ^ 56];
        scores.end += KING_PST_END[i ^ 56];

        if (col < 4) {  // Queen side
            evaluate_king_pawn(position, scores, 1, false); // A file pawn
            evaluate_king_pawn(position, scores, 2, false);
            evaluate_king_pawn(position, scores, 3, false); // C file pawn
        }
        else if (col > 5) {
            evaluate_king_pawn(position, scores, 8, false); // H file pawn
            evaluate_king_pawn(position, scores, 7, false);
            evaluate_king_pawn(position, scores, 6, false); // F file pawn
        }
        else {
            for (SQUARE_TYPE pawn_file = col - 1; pawn_file < col + 2; pawn_file++) {
                if (position.pawn_rank[1][pawn_file] == 0) {
                    scores.mid += KING_SEMI_OPEN_FILE_PENALTY_MID;
                    scores.end += KING_SEMI_OPEN_FILE_PENALTY_END;
                    if (position.pawn_rank[0][pawn_file] == 9) {
                        scores.mid += KING_OPEN_FILE_PENALTY_MID;
                        scores.end += KING_OPEN_FILE_PENALTY_END;
                    }
                }
            }
        }
    }
}


double evaluate_drawishness(const int white_piece_amounts[6], const int black_piece_amounts[6],
                            SCORE_TYPE white_material, SCORE_TYPE black_material, bool opp_colored_bishops) {

    // return a decimal from 0.0 - 1.0 that will multiply the eval by

    if (white_piece_amounts[WHITE_QUEEN] + black_piece_amounts[WHITE_QUEEN] > 0) return 1.0;
    if (white_piece_amounts[WHITE_ROOK] + black_piece_amounts[WHITE_ROOK] >= 3) return 1.0;
    if (white_piece_amounts[WHITE_PAWN] + black_piece_amounts[WHITE_PAWN] >= 1) {
        if (white_piece_amounts[WHITE_PAWN] + black_piece_amounts[WHITE_PAWN] == 1) {
            if (white_material <= PIECE_VALUES_MID[WHITE_PAWN] && black_material <= PIECE_VALUES_MID[WHITE_BISHOP])
                return 0.1;
            if (black_material <= PIECE_VALUES_MID[WHITE_PAWN] && white_material <= PIECE_VALUES_MID[WHITE_BISHOP])
                return 0.1;
        }

        if (white_piece_amounts[WHITE_KNIGHT] + white_piece_amounts[WHITE_ROOK] +
            black_piece_amounts[WHITE_KNIGHT] + black_piece_amounts[WHITE_ROOK] >= 1) return 1.0;

        if (white_piece_amounts[2] == 1 && black_piece_amounts[2] == 1 && opp_colored_bishops) {
            double pawn_difference = static_cast<double>(std::max(white_piece_amounts[0], black_piece_amounts[0])) /
                                     std::max(1, std::min(white_piece_amounts[0], black_piece_amounts[0]));

            return std::min(0.05 + pawn_difference *
                                   pawn_difference * 0.12, 1.0);
        }

        return 1.0;
    }
    if (white_material <= MAX_MINOR_PIECE_VALUE_MID && black_material <= MAX_MINOR_PIECE_VALUE_MID)
        return 0.0;
    if (white_material <= 2 * MAX_MINOR_PIECE_VALUE_MID && black_material <= 2 * MAX_MINOR_PIECE_VALUE_MID) {

        // With only 2 knights, it's impossible to checkmate
        if (white_piece_amounts[WHITE_KNIGHT] == 2 || black_piece_amounts[WHITE_KNIGHT] == 2)
            return 0.0;

        // If one of them has 0 pieces we know that due to the check above, at least one of has more than
        // a bishop's worth of material, or else it would have returned 0.0, and thus it would be a win.
        // Either the player that doesn't have 0 material has two bishops, a bishop and knight, or a rook.
        // All of these are wins.
        if (white_material == 0 || black_material == 0) {
            return 1.0;
        }

        // Here we know they both do not have 0 material, and they cannot have pawns or queens,
        // this means they either have a rook, and the other player has a minor piece,
        // or this means one player has two minor pieces, and the other players has one minor piece.

        return 0.14;
    }

    if (white_material <= PIECE_VALUES_MID[WHITE_ROOK] + MAX_MINOR_PIECE_VALUE_MID &&
        black_material == PIECE_VALUES_MID[WHITE_ROOK]) return 0.27;

    if (black_material <= PIECE_VALUES_MID[WHITE_ROOK] + MAX_MINOR_PIECE_VALUE_MID &&
        white_material == PIECE_VALUES_MID[WHITE_ROOK]) return 0.27;

    return 1.0;

}


SCORE_TYPE evaluate(Position& position) {

    Score_Struct white_material{};
    Score_Struct white_scores{};

    Score_Struct black_material{};
    Score_Struct black_scores{};

    int game_phase = 0;
    int white_piece_amounts[6] = {0};
    int black_piece_amounts[6] = {0};
    int bishop_colors[2] = {0};

    // We make a 10 size array for each side, and eight of them are used for storing
    // the least advanced pawn. Storing this allows us to check for passed pawns,
    // backwards pawns, isolated pawns and whatnot.
    // Having a ten element array gives padding on the side to prevent out of bounds exceptions.

    for (int i = 0; i < 10; i++) {
        position.pawn_rank[0][i] = 9;
        position.pawn_rank[1][i] = 0;
    }

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
        SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

        if (piece == WHITE_PAWN && row < position.pawn_rank[0][col]) position.pawn_rank[0][col] = row;
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
        SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

        if (piece == BLACK_PAWN && row > position.pawn_rank[1][col]) position.pawn_rank[1][col] = row;
    }

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE standard_pos = MAILBOX_TO_STANDARD[pos];

        game_phase += GAME_PHASE_SCORES[piece];
        white_piece_amounts[piece]++;

        white_material.mid += PIECE_VALUES_MID[piece];
        white_material.end += PIECE_VALUES_END[piece];
        // std::cout << piece << std::endl;

        // std::cout << white_scores.mid << " " << white_scores.end << std::endl;
        if (piece == WHITE_PAWN) evaluate_pawn(position, white_scores, pos, true);
        else if (piece == WHITE_KNIGHT) evaluate_knight(position, white_scores, pos, true);
        else if (piece == WHITE_BISHOP) {
            bishop_colors[0] = SQUARE_COLOR[standard_pos];
            evaluate_bishop(position, white_scores, pos, true);
        }
        else if (piece == WHITE_ROOK) evaluate_rook(position, white_scores, pos, true);
        else if (piece == WHITE_QUEEN) evaluate_queen(position, white_scores, pos, true);
        else if (piece == WHITE_KING) evaluate_king(position, white_scores, pos, true);

        // std::cout << white_scores.mid << " " << white_scores.end << std::endl;
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE standard_pos = MAILBOX_TO_STANDARD[pos];

        game_phase += GAME_PHASE_SCORES[piece-6];
        black_piece_amounts[piece-6]++;

        black_material.mid += PIECE_VALUES_MID[piece - BLACK_PAWN];
        black_material.end += PIECE_VALUES_END[piece - BLACK_PAWN];
        // std::cout << piece << std::endl;

        // std::cout << black_scores.mid << " " << black_scores.end << std::endl;
        if (piece == BLACK_PAWN) evaluate_pawn(position, black_scores, pos, false);
        else if (piece == BLACK_KNIGHT) evaluate_knight(position, black_scores, pos, false);
        else if (piece == BLACK_BISHOP) {
            bishop_colors[1] = SQUARE_COLOR[standard_pos];
            evaluate_bishop(position, black_scores, pos, false);
        }
        else if (piece == BLACK_ROOK) evaluate_rook(position, black_scores, pos, false);
        else if (piece == BLACK_QUEEN) evaluate_queen(position, black_scores, pos, false);
        else if (piece == BLACK_KING) evaluate_king(position, black_scores, pos, false);

        // std::cout << black_scores.mid << " " << black_scores.end << std::endl;
    }

    if (white_piece_amounts[WHITE_BISHOP] >= 2) {
        white_scores.mid += BISHOP_PAIR_BONUS_MID;
        white_scores.end += BISHOP_PAIR_BONUS_END;
    }

    if (black_piece_amounts[WHITE_BISHOP] >= 2) {
        black_scores.mid += BISHOP_PAIR_BONUS_MID;
        black_scores.end += BISHOP_PAIR_BONUS_END;
    }

    white_scores.mid += white_material.mid;
    white_scores.end += white_material.end;

    black_scores.mid += black_material.mid;
    black_scores.end += black_material.end;

    if (position.side == WHITE_COLOR) {
        white_scores.mid += TEMPO_BONUS_MID;
        white_scores.end += TEMPO_BONUS_END;
    } else {
        black_scores.mid += TEMPO_BONUS_MID;
        black_scores.end += TEMPO_BONUS_END;
    }

    if (game_phase > 24) game_phase = 24; // In case of early promotions
    SCORE_TYPE white_score = (white_scores.mid * game_phase +
                              (24 - game_phase) * white_scores.end) / 24;

    SCORE_TYPE black_score = (black_scores.mid * game_phase +
                              (24 - game_phase) * black_scores.end) / 24;

    double drawishness = evaluate_drawishness(white_piece_amounts, black_piece_amounts,
                                              white_material.mid, black_material.mid,
                                              bishop_colors[0] != bishop_colors[1]);

    white_score *= drawishness;
    black_score *= drawishness;

    // std::cout << white_score << " " << black_score << std::endl;

    return (position.side * -2 + 1) * (white_score - black_score);
}


SCORE_TYPE score_move(const Thread_State& thread_state, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move,
                      MOVE_TYPE last_move_one, MOVE_TYPE last_move_two) {

    if (move == tt_move) return 500000;

    SCORE_TYPE score = 0;

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    PIECE_TYPE selected_type = selected - 6 * position.side;

    short move_type = get_move_type(move);

    if (move_type == MOVE_TYPE_PROMOTION) {
        PIECE_TYPE promotion_piece = get_promotion_piece(move) - 6 * position.side;
        if (promotion_piece == WHITE_QUEEN) {
            score += thread_state.move_ordering_parameters.queen_promotion_margin;
        } else {
            score += score + thread_state.move_ordering_parameters.other_promotion_margin +
                     MVV_LVA_VALUES[promotion_piece];
        }
    }

    if (get_is_capture(move)) {
        PIECE_TYPE occupied_type = occupied - 6 * !position.side;

        score += thread_state.capture_history[selected][occupied][MAILBOX_TO_STANDARD[get_target_square(move)]];
        score += thread_state.move_ordering_parameters.capture_scale * MVV_LVA_VALUES[occupied_type]
                - MVV_LVA_VALUES[selected_type];

        // Only Use SEE under certain conditions since it is expensive
        if (score >= -3000) {
            if (score >= 3000 ||
                get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD))
                score += thread_state.move_ordering_parameters.winning_capture_margin;
        }

        score += thread_state.move_ordering_parameters.base_capture_margin;
    }

    else {
        // score 1st and 2nd killer move
        if (thread_state.killer_moves[0][thread_state.search_ply] == move) score +=
                thread_state.move_ordering_parameters.first_killer_margin;
        else if (thread_state.killer_moves[1][thread_state.search_ply] == move) score +=
                thread_state.move_ordering_parameters.second_killer_margin;

        score += thread_state.history_moves[selected][MAILBOX_TO_STANDARD[get_target_square(move)]];

        if (last_move_one != NO_MOVE) {
            score += thread_state.continuation_history[get_selected(last_move_one)]
                    [MAILBOX_TO_STANDARD[get_target_square(last_move_one)]]
                    [selected]
                    [MAILBOX_TO_STANDARD[get_target_square(move)]];
        }

        if (last_move_two != NO_MOVE) {
            score += thread_state.continuation_history[get_selected(last_move_two)]
                    [MAILBOX_TO_STANDARD[get_target_square(last_move_two)]]
                    [selected]
                    [MAILBOX_TO_STANDARD[get_target_square(move)]];
        }
        if (move_type == MOVE_TYPE_EP) score += thread_state.move_ordering_parameters.winning_capture_margin +
                thread_state.move_ordering_parameters.capture_scale * (MVV_LVA_VALUES[WHITE_PAWN] / 2);
        else if (move_type == MOVE_TYPE_CASTLE) score += thread_state.move_ordering_parameters.castle_margin;
    }

    return score;
}


SCORE_TYPE score_capture(const Thread_State& thread_state, Position& position,  MOVE_TYPE move, MOVE_TYPE tt_move) {

    if (move == tt_move) return 100000;

    SCORE_TYPE score = 0;

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    score += thread_state.capture_history[selected][occupied][MAILBOX_TO_STANDARD[get_target_square(move)]];

    if (score >= -3000) {
        if (score >= 3000 ||
            get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD))
            score += thread_state.move_ordering_parameters.winning_capture_margin;
    }

    if (selected < BLACK_PAWN) score += MVV_LVA_VALUES[occupied - BLACK_PAWN] - MVV_LVA_VALUES[selected];
    else score += MVV_LVA_VALUES[occupied] - MVV_LVA_VALUES[selected - BLACK_PAWN];

    return score;
}


void get_move_scores(const Thread_State& thread_state, Position& position, std::vector<Move_Struct>& moves,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move_one, MOVE_TYPE last_move_two) {

    for (Move_Struct& move_struct : moves) {
        move_struct.score = score_move(thread_state, position, move_struct.move, tt_move, last_move_one, last_move_two);
    }
}


void get_capture_scores(const Thread_State& thread_state, Position& position, std::vector<Move_Struct>& moves,
                        MOVE_TYPE tt_move) {

    for (Move_Struct& move_struct : moves) {
        move_struct.score = score_capture(thread_state, position, move_struct.move, tt_move);
    }
}


void sort_next_move(std::vector<Move_Struct>& moves, int current_count) {
    auto best_score = moves[current_count].score;
    auto best_idx = current_count;
    for (auto next_count = current_count + 1; next_count < static_cast<int>(moves.size()); next_count++) {
        if (best_score < moves[next_count].score) {
            best_score = moves[next_count].score;
            best_idx = next_count;
        }
    }
    std::swap(moves[current_count], moves[best_idx]);
}
