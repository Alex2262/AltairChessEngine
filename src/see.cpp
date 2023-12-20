

#include <vector>
#include <utility>
#include <iostream>
#include "see.h"

BITBOARD get_all_attackers(Position& position, Square square) {

    // Treat square like a pawn
    BITBOARD pawn_attackers = (WHITE_PAWN_ATTACKS[square] & position.get_pieces(PAWN, BLACK)) |
            (BLACK_PAWN_ATTACKS[square] & position.get_pieces(PAWN, WHITE));

    // Treat square like a knight
    BITBOARD knight_attackers = KNIGHT_ATTACKS[square] &
            (position.get_pieces(WHITE_KNIGHT) | position.get_pieces(BLACK_KNIGHT));

    // Treat square like a bishop
    BITBOARD bishop_attacks = get_bishop_attacks(square, position.all_pieces);
    BITBOARD bishop_attackers = bishop_attacks &
            (position.get_pieces(WHITE_BISHOP) | position.get_pieces(BLACK_BISHOP));

    // Treat square like a rook
    BITBOARD rook_attacks = get_rook_attacks(square, position.all_pieces);
    BITBOARD rook_attackers = rook_attacks &
            (position.get_pieces(WHITE_ROOK) | position.get_pieces(BLACK_ROOK));

    BITBOARD queen_attackers = (bishop_attacks | rook_attacks) &
            (position.get_pieces(WHITE_QUEEN) | position.get_pieces(BLACK_QUEEN));

    BITBOARD king_attackers = KING_ATTACKS[square] &
            (position.get_pieces(WHITE_KING) | position.get_pieces(BLACK_KING));

    return pawn_attackers | knight_attackers | bishop_attackers | rook_attackers | queen_attackers | king_attackers;
}


SCORE_TYPE get_static_exchange_evaluation(Position& position, Move move, SCORE_TYPE threshold) {
    assert(move != NO_MOVE);

    MoveType move_type = move.type();
    if (move_type == MOVE_TYPE_CASTLE) return true;
    if (move_type == MOVE_TYPE_PROMOTION) return true;
    if (move_type == MOVE_TYPE_EP) return true;

    Square origin_square = move.origin();
    Square target_square = move.target();

    Piece selected = position.board[origin_square];
    Piece occupied = position.board[target_square];

    SCORE_TYPE exchange_value = SEE_values[occupied] - threshold;
    if (exchange_value < 0) return false; // If taking the opponent's piece without any risk is still negative

    exchange_value -= SEE_values[selected];
    if (exchange_value >= 0) return true; // If we risk our piece being fully lost and the exchange value is still >= 0

    BITBOARD occupancy = position.all_pieces ^ from_square(origin_square);
    BITBOARD attackers = get_all_attackers(position, target_square);

    BITBOARD diagonal_attackers = position.get_pieces(WHITE_BISHOP) | position.get_pieces(BLACK_BISHOP) |
                                  position.get_pieces(WHITE_QUEEN) | position.get_pieces(BLACK_QUEEN);

    BITBOARD horizontal_attackers = position.get_pieces(WHITE_ROOK) | position.get_pieces(BLACK_ROOK) |
                                    position.get_pieces(WHITE_QUEEN) | position.get_pieces(BLACK_QUEEN);

    Color original_side = position.side;
    position.side = ~position.side;

    while (true) {

        // Removed used pieces from attackers
        attackers &= occupancy;

        BITBOARD our_attackers = attackers & position.get_our_pieces();
        if (!our_attackers) break; // No attacking piece was found

        PieceType cheapest_attacker = KING;
        for (int piece = PAWN; piece < static_cast<int>(KING); piece++) {
            if (our_attackers & position.get_pieces(static_cast<PieceType>(piece), position.side)) {
                cheapest_attacker = static_cast<PieceType>(piece);
                break;
            }
        }

        position.side = ~position.side;

        exchange_value = -exchange_value - 1 - SEE_values[cheapest_attacker];
        if (exchange_value >= 0) {
            if (cheapest_attacker == KING && (attackers & position.get_our_pieces())) position.side = ~position.side;
            break;
        }

        occupancy ^= from_square(lsb(our_attackers & position.get_pieces(cheapest_attacker, ~position.side)));

        if (cheapest_attacker == PAWN || cheapest_attacker == BISHOP || cheapest_attacker == QUEEN) {
            attackers |= get_bishop_attacks(target_square, occupancy) & diagonal_attackers;
        }
        if (cheapest_attacker == ROOK || cheapest_attacker == QUEEN) {
            attackers |= get_rook_attacks(target_square, occupancy) & horizontal_attackers;
        }
    }


    bool exchange_flag = position.side != original_side;

    position.side = original_side;

    return exchange_flag;


}

