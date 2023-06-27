//
// Created by Alexander Tian on 5/4/23.
//

#include <vector>
#include <utility>
#include <iostream>
#include "see.h"

// TODO: get all attackers instead of the cheapest attacker, and then incrementally find the next cheapest one
Square get_cheapest_attacker(Position& position, Square square) {

    BITBOARD occupancy = position.all_pieces & (~from_square(square));

    // Treat square like a pawn
    BITBOARD pawn_attackers = position.side == WHITE ? WHITE_PAWN_ATTACKS[square] : BLACK_PAWN_ATTACKS[square] &
            position.get_pieces(PAWN, ~position.side);

    if (pawn_attackers) return poplsb(pawn_attackers);

    // Treat square like a knight
    BITBOARD knight_attackers = KNIGHT_ATTACKS[square] & position.get_pieces(KNIGHT, ~position.side);
    if (knight_attackers) return poplsb(knight_attackers);

    // Treat square like a bishop
    BITBOARD bishop_attacks = get_bishop_attacks(square, occupancy);
    BITBOARD bishop_attackers = bishop_attacks & position.get_pieces(BISHOP, ~position.side);
    if (bishop_attackers) return poplsb(bishop_attackers);

    // Treat square like a rook
    BITBOARD rook_attacks = get_rook_attacks(square, occupancy);
    BITBOARD rook_attackers = rook_attacks & position.get_pieces(ROOK, ~position.side);
    if (rook_attackers) return poplsb(rook_attackers);

    BITBOARD queen_attackers = (bishop_attacks | rook_attacks) & position.get_pieces(QUEEN, ~position.side);
    if (queen_attackers) return poplsb(queen_attackers);

    return NO_SQUARE;
}


SCORE_TYPE get_static_exchange_evaluation(Position& position, Move move, SCORE_TYPE threshold) {
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

    std::vector<std::pair<Piece, Square>> removed_pieces;

    position.remove_piece(occupied, target_square);
    removed_pieces.emplace_back(occupied, target_square);

    Color original_side = position.side;

    while (true) {
        Square cheapest_attacker_square = get_cheapest_attacker(position, target_square);
        if (cheapest_attacker_square == NO_SQUARE) break; // No attacking piece was found

        position.side = ~position.side;

        Piece cheapest_attacker = position.board[cheapest_attacker_square];

        exchange_value = -exchange_value - 1 - SEE_values[cheapest_attacker];
        if (exchange_value >= 0) {
            break;
        }

        position.remove_piece(cheapest_attacker, cheapest_attacker_square);
        removed_pieces.emplace_back(cheapest_attacker, cheapest_attacker_square);
    }

    for (auto removed : removed_pieces) {
        position.place_piece(removed.first, removed.second);
    }

    bool exchange_flag = position.side == original_side;

    position.side = original_side;

    return exchange_flag;


}

