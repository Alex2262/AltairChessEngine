//
// Created by Alex Tian on 8/24/2022.
//

#ifndef ANTARESCHESSENGINE_POSITION_H
#define ANTARESCHESSENGINE_POSITION_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "constants.h"
#include "nnue.h"


struct Move_Struct {
    MOVE_TYPE move = NO_MOVE;
    SCORE_TYPE score = 0;
    bool legal = false;
};


struct State_Struct {
    int in_check = -1;
    uint64_t current_hash_key;
    MOVE_TYPE move = NO_MOVE;
    SCORE_TYPE evaluation = NO_EVALUATION;
    SQUARE_TYPE current_ep_square;
    uint16_t current_castle_ability_bits;
    PLY_TYPE current_fifty_move;
    MOVE_TYPE excluded_move = NO_MOVE;
    int double_extensions = 0;
};


class Position {

public:

    Position() = default;

    bool fischer_random_chess = false;
    NNUE_State nnue_state{};

    void clear_movelist();
    void clear_state_stack();
    void compute_hash_key();

    PLY_TYPE set_fen(const std::string& fen_string);
    void print_board();
    [[maybe_unused]] void print_piece_index_board();
    [[maybe_unused]] bool check_valid(PLY_TYPE ply);

    bool is_attacked(SQUARE_TYPE pos);

    void set_state(PLY_TYPE search_ply, PLY_TYPE fifty_move);

    bool make_move(MOVE_TYPE move, PLY_TYPE search_ply, PLY_TYPE& fifty_move);
    void undo_move(MOVE_TYPE move, PLY_TYPE search_ply, PLY_TYPE& fifty_move);
    void make_null_move(PLY_TYPE search_ply, PLY_TYPE& fifty_move);
    void undo_null_move(PLY_TYPE search_ply, PLY_TYPE& fifty_move);

    void get_pseudo_legal_moves(PLY_TYPE ply);
    void get_pseudo_legal_captures(PLY_TYPE ply);

    bool get_is_pseudo_legal(MOVE_TYPE move);

    PIECE_TYPE board[120]{};
    SQUARE_TYPE piece_list_index[120] = {NO_PIECE_INDEX};

    SQUARE_TYPE starting_rook_pos[2][2]{};

    std::vector<PIECE_TYPE> white_pieces;
    std::vector<PIECE_TYPE> black_pieces;

    std::array<std::vector<Move_Struct>, TOTAL_MAX_DEPTH> moves{};

    std::array<State_Struct, TOTAL_MAX_DEPTH> state_stack{};

    SQUARE_TYPE king_positions[2]{};

    SQUARE_TYPE pawn_rank[2][10]{};

    SQUARE_TYPE castle_ability_bits = 0;
    SQUARE_TYPE ep_square = 0;
    SQUARE_TYPE side = 0;
    HASH_TYPE hash_key = 0;

    int non_pawn_material_count = 0;

    inline void update_piece_list_index(SQUARE_TYPE left_range, SQUARE_TYPE right_range, SQUARE_TYPE side_to_use) {
        if (!side_to_use) {
            for (int i = left_range; i < right_range; i++) {
                piece_list_index[white_pieces[i]] = i;
            }
        } else {
            for (int i = left_range; i < right_range; i++) {
                piece_list_index[black_pieces[i]] = i;
            }
        }
    }

    Position& operator=(const Position& copy_position) {
        fischer_random_chess = copy_position.fischer_random_chess;

        for (SQUARE_TYPE square = 0; square < 120; square++) {
            board[square] = copy_position.board[square];
            piece_list_index[square] = copy_position.piece_list_index[square];
        }

        starting_rook_pos[0][0] = copy_position.starting_rook_pos[0][0];
        starting_rook_pos[0][1] = copy_position.starting_rook_pos[0][1];
        starting_rook_pos[1][0] = copy_position.starting_rook_pos[1][0];
        starting_rook_pos[1][1] = copy_position.starting_rook_pos[1][1];

        white_pieces = copy_position.white_pieces;
        black_pieces = copy_position.black_pieces;

        king_positions[0] = copy_position.king_positions[0];
        king_positions[1] = copy_position.king_positions[1];

        castle_ability_bits = copy_position.castle_ability_bits;
        ep_square = copy_position.ep_square;
        side = copy_position.side;
        hash_key = copy_position.hash_key;

        non_pawn_material_count = copy_position.non_pawn_material_count;

        clear_movelist();
        clear_state_stack();

        nnue_state.m_accumulator_stack.reserve(TOTAL_MAX_DEPTH);
        nnue_state.reset_nnue(*this);

        // std::cout << nnue_state.m_accumulator_stack.size() << std::endl;

        // print_board();
        // print_piece_index_board();

        return *this;
    }


};





#endif //ANTARESCHESSENGINE_POSITION_H
