

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

SCORE_TYPE score_q_bn(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]);

template<bool qsearch>
SCORE_TYPE score_capture(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, int& good_capture_count);

void get_q_bn_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[], int start_index);

template<bool qsearch>
void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move, int& good_capture_count);

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
    InformativeMove last_moves[LAST_MOVE_COUNTS]{};

    int stage = Stage::TT_probe;
    int move_index = 0;
    int good_capture_count = 0;
    int good_capture_found = 0;

    PLY_TYPE search_ply = 0;

    void reset_qsearch(Move tt_move_passed);
    void reset_negamax(Move tt_move_passed, InformativeMove last_moves_passed[]);

    template<Filter filter>
    inline ScoredMove sort_next_move() {
        auto& current_scored_moves = position->scored_moves[search_ply];

        auto best_score = current_scored_moves[move_index].score;
        auto best_idx = move_index;
        for (auto next_count = move_index + 1; next_count < static_cast<int>(current_scored_moves.size()); next_count++) {
            ScoredMove& scored_move = current_scored_moves[next_count];

            if constexpr (filter == Filter::Noisy) {
                if (!scored_move.move.is_capture(*position)) continue;
            }

            else if constexpr (filter == Filter::Good) {
                if (!scored_move.winning_capture) continue;
            }

            else if constexpr (filter == Filter::GoodNoisy) {
                if (!scored_move.move.is_capture(*position)) continue;
                if (!scored_move.winning_capture) continue;
            }

            else if constexpr (filter == Filter::Quiet) {
                if (scored_move.move.is_capture(*position)) continue;
            }

            if (scored_move.move == tt_move) continue;

            if (best_score < scored_move.score) {
                best_score = scored_move.score;
                best_idx = next_count;
            }
        }

        std::swap(current_scored_moves[move_index], current_scored_moves[best_idx]);
        return current_scored_moves[move_index];
    }

    template<bool qsearch>
    inline ScoredMove next_move() {

        assert(stage != Stage::Terminated);

        ScoredMove picked = {NO_MOVE, 0, false};
        auto& current_scored_moves = position->scored_moves[search_ply];

        if (stage == Stage::TT_probe) {
            stage = Stage::GenNoisy;
            if (position->is_pseudo_legal(tt_move)) return {tt_move, static_cast<SCORE_TYPE>(MO_Margin::TT), true};
        }

        if (stage == Stage::GenNoisy) {
            move_index = 0;
            good_capture_count = 0;
            good_capture_found = 0;

            if constexpr (qsearch) position->get_pseudo_legal_moves<Movegen::Qsearch, true>(current_scored_moves);
            else position->get_pseudo_legal_moves<Movegen::Noisy, true>(current_scored_moves);

            get_capture_scores<qsearch>(*thread_state, current_scored_moves, tt_move, good_capture_count);
            stage = Stage::Noisy;
        }

        if (stage == Stage::Noisy) {

            if (current_scored_moves[move_index].move == tt_move) move_index++;

            if (good_capture_found >= good_capture_count) {
                if constexpr (!qsearch) stage = Stage::GenQ_BN;
                else if (move_index >= static_cast<int>(current_scored_moves.size())) stage = Stage::Terminated;
            }

            if (stage == Stage::Noisy) {
                if constexpr (qsearch) picked = sort_next_move<Filter::None>();
                else picked = sort_next_move<Filter::Good>();

                good_capture_found++;
                move_index++;
            }
        }

        if (stage == Stage::GenQ_BN) {
            assert(!qsearch);

            position->get_pseudo_legal_moves<Movegen::Quiet, false>(current_scored_moves);
            get_q_bn_scores(*thread_state, current_scored_moves, tt_move, last_moves, move_index);

            stage = Stage::Q_BN;
        }

        if (stage == Stage::Q_BN) {
            assert(!qsearch);

            if (current_scored_moves[move_index].move == tt_move) move_index++;

            if (move_index >= static_cast<int>(current_scored_moves.size())) {
                stage = Stage::Terminated;
            }

            else {
                picked = sort_next_move<Filter::None>();
                move_index++;
            }
        }

        if (stage == Stage::Noisy) {
            assert(picked.move.type() != MOVE_TYPE_CASTLE);
        }
        return picked;
    }
};



#endif //ALTAIR_MOVE_ORDERING_H
