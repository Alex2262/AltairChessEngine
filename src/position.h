
#pragma once

#include <string>
#include "constants.h"
#include "types.h"
#include "fixed_vector.h"
#include "bitboard.h"
#include "attacks.h"
#include "move.h"
#include "nnue.h"


constexpr int bishop_ordering_1[2][4] = {
        { 1,  3,  5,  7},
        {57, 59, 61, 63}
};

constexpr int bishop_ordering_2[2][4] = {
        { 0,  2,  4,  6},
        {56, 58, 60, 62}
};

struct ScoredMove {
    Move move = NO_MOVE;
    Score score = 0;
    bool winning_capture = false;
};

struct NNUpdate {
    Piece  piece;
    Square square;
};

struct KingBucketUpdate {
    bool update_necessary = false;
    Color side = WHITE;
    int bucket = 0;
};

struct State {
    Hash current_hash_key = 0ULL;
    Hash current_pawn_hash_key = 0ULL;
    Hash current_np_hash_key = 0ULL;
    Hash current_major_hash_key = 0ULL;
    Hash current_minor_hash_key = 0ULL;

    Bitboard threats = 0ULL;

    Square current_ep_square = NO_SQUARE;
    uint8_t current_castle_ability_bits = 0;
    Ply current_fifty_move = 0;

    InformativeMove move = NO_INFORMATIVE_MOVE;
    Move excluded_move = NO_MOVE;

    Score static_eval = NO_EVALUATION;

    int double_extensions = 0;
    int in_check = -1;

    FixedVector<NNUpdate, 4> activations{};
    FixedVector<NNUpdate, 4> deactivations{};
    KingBucketUpdate king_bucket_update{};
    bool NNUE_pushed = false;
};

struct FenInfo {
    Ply fifty_move_counter = 0;
    Ply full_move_counter  = 1;
};

enum Movegen {
    All,
    Noisy,
    Qsearch,
    Quiet
};

class Position {

public:
    Position() = default;

    NNUE_State nnue_state{};

    bool fischer_random_chess = false;

    Bitboard all_pieces{};
    Bitboard our_pieces{};
    Bitboard opp_pieces{};
    Bitboard empty_squares{};
    Bitboard threats{};

    Bitboard pieces[12]{};

    Piece board[64]{};

    Color side = WHITE;

    uint8_t castle_ability_bits = 0;
    Square starting_rook_pos[2][2]{};

    Square ep_square         = NO_SQUARE;
    Hash hash_key       = 0;
    Hash pawn_hash_key  = 0;
    Hash np_hash_key    = 0;
    Hash major_hash_key = 0;
    Hash minor_hash_key = 0;

    std::array<State, TOTAL_MAX_DEPTH> state_stack{};

    std::array<FixedVector<ScoredMove, MAX_MOVES>, TOTAL_MAX_DEPTH> scored_moves{};

    void clear_state_stack();
    void set_state(State& state, Ply fifty_move) const;

    inline Bitboard get_pieces(Piece piece) const { return pieces[piece]; }
    inline Bitboard get_pieces(PieceType piece, Color color) const { return pieces[piece + color * COLOR_OFFSET]; }
    inline Bitboard get_pieces(Color color) const {
        return get_pieces(PAWN, color) |
               get_pieces(KNIGHT, color) |
               get_pieces(BISHOP, color) |
               get_pieces(ROOK, color) |
               get_pieces(QUEEN, color) |
               get_pieces(KING, color);
    }
    inline Bitboard get_our_pieces() const { return get_pieces(side); }
    inline Bitboard get_opp_pieces() const { return get_pieces(~side); }
    inline Bitboard get_all_pieces() const { return our_pieces | opp_pieces; }
    inline Bitboard get_empty_squares() const { return ~all_pieces; }

    Bitboard get_attacked_squares(Color color) const;
    Square get_king_pos(Color color) const;
    bool is_attacked(Square square, Color color) const;
    uint32_t get_non_pawn_material_count() const;

    void remove_piece(Piece piece, Square square);
    void place_piece(Piece piece, Square square);

    void compute_hash_key();

    FenInfo set_fen(const std::string& fen);
    std::string get_fen(Ply fifty_move);

    void set_frc_side(Color color, int index);
    void set_dfrc(int index);

    void ensure_stable();

    void compute_threats();

    friend std::ostream& operator<<(std::ostream& os, const Position& position);

    bool is_pseudo_legal(Move move);

    void make_null_move(State& state, Ply& fifty_move);
    void undo_null_move(State& state, Ply& fifty_move);

    bool make_move(Move move, State& state, Ply& fifty_move);
    void undo_move(Move move, State& state, Ply& fifty_move);

    void update_nnue(State& state);

    template<Movegen movegen>
    inline void get_pawn_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    template<Movegen movegen>
    void get_knight_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    template<Movegen movegen>
    void get_bishop_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    template<Movegen movegen>
    void get_rook_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    template<Movegen movegen>
    void get_queen_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    template<Movegen movegen>
    void get_king_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;

    template<Movegen movegen, bool clear>
    void get_pseudo_legal_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const;
};


#include "position.inl"
