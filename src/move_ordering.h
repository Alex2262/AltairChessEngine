
#pragma once

#include "types.h"
#include "fixed_vector.h"
#include "position.h"

class Thread_State;

constexpr Score BAD_SCORE = -1000000;


enum class MO_Margin : Score {
    TT = 500000,
    winning_capture = 50000,
    base_capture = -3000,
    capture_scale = 3,
    queen_promotion = 100000,
    other_promotion = -30000,
    killer_1 = 30000,
    killer_2 = 25000,
    castle = 1200
};

Score score_q_bn(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]);

template<bool qsearch>
Score score_noisy(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, size_t& good_noisy_count);

void get_q_bn_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[], int start_index);

template<bool qsearch>
void get_noisy_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                      Move tt_move, size_t& good_noisy_count);

enum class Filter : uint16_t {
    None,
    Good
};


namespace Stage {
    constexpr int TT_probe = 0;
    constexpr int GenNoisy = 1;
    constexpr int Noisy = 2;    // Only play good noisy moves in this stage for negamax
    constexpr int GenQ_BN = 3;
    constexpr int Q_BN = 4;  // Quiet + Bad Noisy
    constexpr int Terminated = 5;
}

class Generator {

public:
    Generator() = default;
    Generator(Thread_State& thread_state_passed);
    ~Generator() = default;

    FixedVector<ScoredMove, MAX_MOVES> scored_moves;

    Move tt_move;
    Thread_State *thread_state;
    Position *position;
    InformativeMove last_moves[LAST_MOVE_COUNTS]{};

    int stage = Stage::TT_probe;
    size_t move_index = 0;
    size_t good_noisy_count = 0;
    size_t good_noisy_found = 0;

    Ply search_ply = 0;

    void reset_qsearch(Move tt_move_passed);
    void reset_negamax(Move tt_move_passed, InformativeMove last_moves_passed[]);

    template<Filter filter>
    inline ScoredMove sort_next_move();
    template<bool qsearch>
    inline ScoredMove next_move();
};


#include "move_ordering.inl"