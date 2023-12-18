

#ifndef ALTAIR_MOVE_ORDERING_H
#define ALTAIR_MOVE_ORDERING_H

#include "types.h"
#include "fixed_vector.h"

class Thread_State;

constexpr SCORE_TYPE SEE_MOVE_ORDERING_THRESHOLD = -85;

SCORE_TYPE score_move(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]);

SCORE_TYPE score_capture(Thread_State& thread_state, Move move, Move tt_move);

void get_move_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[]);

void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move);

Move sort_next_move(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, int current_count);

namespace Stage {
    constexpr int TT_probe = 0;
    constexpr int None = 1;
    constexpr int Terminated = 2;
}

class Generator {

public:

    Generator() = default;
    Generator(Thread_State& thread_state_passed);
    ~Generator() = default;

    Move tt_move;
    Thread_State *thread_state;
    Position *position;
    InformativeMove last_moves[LAST_MOVE_COUNTS]{};

    bool moves_generated = false;
    int move_index = 0;
    int stage = Stage::TT_probe;

    PLY_TYPE search_ply = 0;

    void reset_qsearch(Move tt_move_passed);
    void reset_negamax(Move tt_move_passed, InformativeMove last_moves_passed[]);

    void increment() {
        move_index++;
        if (moves_generated && move_index >= position->scored_moves[search_ply].size()) stage = Stage::Terminated;
    }

    template<bool qsearch>
    inline Move next_move() {

        assert(stage != Stage::Terminated);

        if (stage == Stage::TT_probe) {
            stage = Stage::None;

            if (tt_move != NO_MOVE && position->is_pseudo_legal(tt_move)) {
                return tt_move;
            }
        }

        Move picked = NO_MOVE;
        FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves = position->scored_moves[search_ply];

        if (stage == Stage::None) {

            if (!moves_generated) {
                moves_generated = true;

                if constexpr (qsearch) {
                    position->get_pseudo_legal_captures(current_scored_moves);
                    get_capture_scores(*thread_state, current_scored_moves, tt_move);
                }

                else {
                    position->get_pseudo_legal_moves(current_scored_moves);
                    get_move_scores(*thread_state, current_scored_moves, tt_move, last_moves);
                }
            }

            if (!current_scored_moves.empty() && move_index < current_scored_moves.size())
                picked = sort_next_move(current_scored_moves, move_index);
        }

        // std::cout << search_ply << " " << qsearch << " " << picked.get_uci(*position) << " " << move_index << std::endl;
        return picked;
    }
};



#endif //ALTAIR_MOVE_ORDERING_H
