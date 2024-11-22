

#ifndef ALTAIR_MOVE_ORDERING_H
#define ALTAIR_MOVE_ORDERING_H

#include "types.h"
#include "fixed_vector.h"
#include "position.h"

class Thread_State;


enum class MO_Margin : SCORE_TYPE {
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

SCORE_TYPE score_q_bn(Thread_State& thread_state, Move move, Move tt_move);

template<bool qsearch>
SCORE_TYPE score_capture(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, int& good_capture_count);

void get_q_bn_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, int start_index);

void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move, int& good_capture_count, bool qsearch);

enum class Filter : uint16_t {
    None,
    Noisy,
    Good,
    GoodNoisy,
    Quiet
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

    Move tt_move;

    Thread_State *thread_state;
    Position *position;

    int stage = Stage::TT_probe;
    int move_index = 0;
    int good_capture_count = 0;
    int good_capture_found = 0;

    PLY_TYPE search_ply = 0;

    void reset_qsearch(Move tt_move_passed);
    void reset_negamax(Move tt_move_passed);

    ScoredMove sort_next_move(Filter filter);
    ScoredMove next_move(bool qsearch);
};



#endif //ALTAIR_MOVE_ORDERING_H
