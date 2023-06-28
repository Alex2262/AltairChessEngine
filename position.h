//
// Created by Alex Tian on 8/24/2022.
//

#ifndef ANTARESCHESSENGINE_POSITION_H
#define ANTARESCHESSENGINE_POSITION_H

#include <string>
#include "constants.h"
#include "types.h"
#include "fixed_vector.h"
#include "bitboard.h"
#include "tables.h"
#include "move.h"


struct ScoredMove {
    Move move = NO_MOVE;
    SCORE_TYPE score = 0;
};

struct State_Struct {
    uint64_t current_hash_key = 0ULL;
    Square current_ep_square = NO_SQUARE;
    uint8_t current_castle_ability_bits = 0;
    PLY_TYPE current_fifty_move = 0;

    InformativeMove move = NO_INFORMATIVE_MOVE;
    Move excluded_move = NO_MOVE;

    SCORE_TYPE evaluation = NO_EVALUATION;

    int double_extensions = 0;
    int in_check = -1;
};


class Position {

public:

    Position() = default;

    bool fischer_random_chess = false;

    BITBOARD all_pieces{};
    BITBOARD our_pieces{};
    BITBOARD opp_pieces{};
    BITBOARD empty_squares{};

    BITBOARD pieces[12]{};

    Piece board[64]{};

    Color side = WHITE;

    uint8_t castle_ability_bits = 0;
    Square ep_square = NO_SQUARE;
    HASH_TYPE hash_key = 0;

    std::array<State_Struct, TOTAL_MAX_DEPTH> state_stack{};

    std::array<FixedVector<ScoredMove, MAX_MOVES>, TOTAL_MAX_DEPTH> scored_moves{};

    void clear_state_stack();
    void set_state(State_Struct& state_struct, PLY_TYPE fifty_move) const;

    [[nodiscard]] BITBOARD get_pieces(Piece piece) const;
    [[nodiscard]] BITBOARD get_pieces(PieceType piece, Color color) const;
    [[nodiscard]] BITBOARD get_pieces(Color color) const;

    [[nodiscard]] BITBOARD get_our_pieces();
    [[nodiscard]] BITBOARD get_opp_pieces();
    [[nodiscard]] BITBOARD get_all_pieces() const;
    [[nodiscard]] BITBOARD get_empty_squares() const;

    [[nodiscard]] BITBOARD get_attacked_squares(Color color) const;

    [[nodiscard]] Square get_king_pos(Color color) const;

    [[nodiscard]] bool is_attacked(Square square, Color color) const;

    uint32_t get_non_pawn_material_count() const;

    void remove_piece(Piece piece, Square square);
    void place_piece(Piece piece, Square square);

    void compute_hash_key();

    PLY_TYPE set_fen(const std::string& fen);

    friend std::ostream& operator<<(std::ostream& os, const Position& position);

    void get_pawn_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_pawn_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_knight_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_knight_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_bishop_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_bishop_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_rook_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_rook_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_queen_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_queen_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_king_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_king_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_piece_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, PieceType piece, Square square) const;
    void get_piece_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, PieceType piece, Square square) const;

    void get_pseudo_legal_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    void get_pseudo_legal_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    bool make_move(Move move, State_Struct& state_struct, PLY_TYPE& fifty_move);
    void undo_move(Move move, State_Struct& state_struct, PLY_TYPE& fifty_move);

    void make_null_move(State_Struct& state_struct, PLY_TYPE& fifty_move);
    void undo_null_move(State_Struct& state_struct, PLY_TYPE& fifty_move);

};





#endif //ANTARESCHESSENGINE_POSITION_H
