//
// Created by Alex Tian on 8/24/2022.
//

#ifndef ANTARESCHESSENGINE_POSITION_H
#define ANTARESCHESSENGINE_POSITION_H

#include <vector>
#include <array>
#include <string>
#include "constants.h"


struct Undo_Move_Struct {
    MOVE_TYPE move;
    SQUARE_TYPE current_ep_square;
    uint16_t current_castle_ability_bits;
    uint64_t current_hash_key;
    PLY_TYPE current_fifty_move;
};


class Position {

public:

    Position() = default;

    void clear_movelist();
    void compute_hash_key();
    void set_fen(const std::string& fen_string);
    void print_board();
    bool is_attacked(SQUARE_TYPE pos);
    bool make_move(MOVE_TYPE move, PLY_TYPE search_ply, PLY_TYPE& fifty_move);
    void undo_move(MOVE_TYPE move, PLY_TYPE search_ply, PLY_TYPE& fifty_move);
    void make_null_move(PLY_TYPE search_ply, PLY_TYPE& fifty_move);
    void undo_null_move(PLY_TYPE search_ply, PLY_TYPE& fifty_move);

    void get_pseudo_legal_moves(PLY_TYPE ply);
    void get_pseudo_legal_captures(PLY_TYPE ply);

    PIECE_TYPE board[120]{};
    std::vector<PIECE_TYPE> white_pieces;
    std::vector<PIECE_TYPE> black_pieces;

    std::array<std::vector<MOVE_TYPE>, TOTAL_MAX_DEPTH> moves;
    std::array<std::vector<SCORE_TYPE>, TOTAL_MAX_DEPTH> move_scores;

    std::array<Undo_Move_Struct, TOTAL_MAX_DEPTH> undo_move_stack{};

    SQUARE_TYPE king_positions[2]{};

    SQUARE_TYPE pawn_rank[2][10]{};

    SQUARE_TYPE castle_ability_bits = 0;
    SQUARE_TYPE ep_square = 0;
    SQUARE_TYPE side = 0;
    HASH_TYPE hash_key = 0;


};





#endif //ANTARESCHESSENGINE_POSITION_H
