//
// Created by Alex Tian on 8/24/2022.
//

#ifndef ANTARESCHESSENGINE_POSITION_H
#define ANTARESCHESSENGINE_POSITION_H

#include <vector>
#include <string>
#include "constants.h"

class Position {

public:

    Position() = default;
    void set_fen(const std::string& fen_string);
    void print_board();
    bool is_attacked(SQUARE_TYPE pos);
    bool make_move(MOVE_TYPE move);
    void undo_move(MOVE_TYPE move, SQUARE_TYPE current_ep,
                   uint16_t current_castle_ability_bits, uint64_t current_hash_key);

    PIECE_TYPE board[120] = {0};
    std::vector<PIECE_TYPE> white_pieces;
    std::vector<PIECE_TYPE> black_pieces;

    SQUARE_TYPE king_positions[2] = {0};

    SQUARE_TYPE castle_ability_bits = 0;
    SQUARE_TYPE ep_square = 0;
    SQUARE_TYPE side = 0;
    HASH_TYPE hash_key = 0;


};

#endif //ANTARESCHESSENGINE_POSITION_H
