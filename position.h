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
    Move move = EMPTY_MOVE;
    SCORE_TYPE score = 0;
};

class Position {

public:

    Position() = default;
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

    std::array<FixedVector<ScoredMove, MAX_MOVES>, TOTAL_MAX_DEPTH> scored_moves;

    BITBOARD get_pieces(Piece piece);
    BITBOARD get_pieces(PieceType piece, Color color);

    [[nodiscard]] BITBOARD get_our_pieces();
    [[nodiscard]] BITBOARD get_opp_pieces();
    [[nodiscard]] BITBOARD get_all_pieces() const;
    [[nodiscard]] BITBOARD get_empty_squares() const;

    Square get_king_pos(Color color);

    void remove_piece(Piece piece, Square square);
    void place_piece(Piece piece, Square square);

    void set_fen(const std::string& fen);

    friend std::ostream& operator<<(std::ostream& os, const Position& p);

    void get_pawn_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_pawn_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);

    void get_knight_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_knight_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_bishop_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);
    void get_bishop_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);

    void get_rook_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);
    void get_rook_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);

    void get_queen_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);
    void get_queen_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square);

    void get_king_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;
    void get_king_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const;

    void get_piece_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, PieceType piece, Square square);
    void get_piece_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, PieceType piece, Square square);

    void get_pseudo_legal_attacks(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves);

    void get_pseudo_legal_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves);

};





#endif //ANTARESCHESSENGINE_POSITION_H
