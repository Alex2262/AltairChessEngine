//
// Created by Alex Tian on 9/22/2022.
//

#ifndef ANTARESCHESSENGINE_SEARCH_H
#define ANTARESCHESSENGINE_SEARCH_H

#include "position.h"

struct TT_Entry {
    HASH_TYPE key = 0;
    SCORE_TYPE score = 0;
    SCORE_TYPE evaluation = NO_EVALUATION;
    MOVE_TYPE move = NO_MOVE;
    PLY_TYPE depth = 0;
    short flag = 0;
};

class Engine {

public:

    Engine() = default;

    PLY_TYPE max_depth = 64;
    PLY_TYPE max_q_depth = 64;
    PLY_TYPE min_depth = 2;
    PLY_TYPE current_search_depth = 0;
    PLY_TYPE search_ply = 0;
    PLY_TYPE game_ply = 0;
    PLY_TYPE fifty_move = 0;

    long max_time = 60000;
    long start_time = 0;

    long long node_count = 0;

    MOVE_TYPE pv_table[64][64]{};
    unsigned short pv_length[65] = {0};

    MOVE_TYPE killer_moves[2][64]{};  // # of killer moves (2) | max_depth (64)
    SCORE_TYPE history_moves[12][64]{}; // # piece | square
    MOVE_TYPE counter_moves[12][64]{}; // # piece | square

    // TT_Entry transposition_table[MAX_TT_SIZE]{};
    std::vector<TT_Entry> transposition_table;

    HASH_TYPE repetition_table[TOTAL_MAX_DEPTH+250] = {0};

    bool stopped = true;

    void clear_tt();

    void reset();
    void new_game();
    bool detect_repetition();

    SCORE_TYPE probe_tt_entry(HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth);
    void record_tt_entry(HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, MOVE_TYPE move, PLY_TYPE depth,
                         SCORE_TYPE static_eval);
    SCORE_TYPE probe_tt_entry_q(HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta);
    void record_tt_entry_q(HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, MOVE_TYPE move,
                           SCORE_TYPE static_eval);
    SCORE_TYPE probe_tt_evaluation(HASH_TYPE hash_key);


};

SCORE_TYPE qsearch(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth);
SCORE_TYPE negamax(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth,  bool do_null);

void iterative_search(Engine& engine, Position& position);

void initialize_lmr_reductions();

#endif //ANTARESCHESSENGINE_SEARCH_H
