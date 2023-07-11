//
// Created by Alex Tian on 9/22/2022.
//

#ifndef ANTARESCHESSENGINE_SEARCH_H
#define ANTARESCHESSENGINE_SEARCH_H

#include <vector>
#include "position.h"

struct TT_Entry {
    HASH_TYPE key = 0;
    SCORE_TYPE score = 0;
    SCORE_TYPE evaluation = NO_EVALUATION;
    Move move = NO_MOVE;
    PLY_TYPE depth = 0;
    short flag = 0;
};


struct Search_Results {
    int num_searches = 1;
    uint64_t node_count = 0;

    uint64_t qsearch_fail_highs[FAIL_HIGH_STATS_COUNT]{};
    uint64_t search_fail_highs[FAIL_HIGH_STATS_COUNT]{};
    uint64_t search_fail_high_types[6]{};

    uint64_t alpha_raised_count = 0;
    uint64_t search_alpha_raises[ALPHA_RAISE_STATS_COUNT]{};

    PLY_TYPE depth_reached = 0;
};

struct T {
    std::string name;
    int min;
    int max;
    int value;
    int step;
};

struct Tuning_Parameters {

    T tuning_parameter_array[N_TUNING_PARAMETERS] = {
            T{"LMR_divisor_quiet", 150, 230, 185, 20},
            T{"LMR_base_quiet", 100, 170, 155, 20},
            T{"delta_margin", 100, 400, 175, 40},
            T{"RFP_depth", 5, 11, 9, 2},
            T{"RFP_margin", 50, 200, 126, 30},
            T{"LMP_depth", 2, 4, 3, 1},
            T{"LMP_margin", 6, 15, 10, 1},
            T{"quiet_LMP_depth", 3, 10, 7, 1},
            T{"quiet_LMP_margin", 5, 12, 5, 1},
            T{"quiet_LMP_improving_margin", -1, 2, 2, 1},
            T{"history_pruning_depth", 4, 20, 12, 2},
            T{"history_pruning_divisor", 4000, 20000, 12062, 1000},
            T{"NMP_depth", 0, 4, 2, 1},
            T{"NMP_base", 1, 5, 3, 1},
            T{"NMP_depth_divisor", 2, 6, 4, 1},
            T{"NMP_eval_divisor", 100, 350, 297, 40},
            T{"LMR_divisor_noisy", 180, 400, 270, 50},
            T{"LMR_base_noisy", 0, 150, 80, 20}
    };

    int LMR_divisor_quiet = tuning_parameter_array[0].value;
    int LMR_base_quiet = tuning_parameter_array[1].value;

    int LMR_divisor_noisy = tuning_parameter_array[16].value;
    int LMR_base_noisy = tuning_parameter_array[17].value;

    int delta_margin = tuning_parameter_array[2].value;

    int RFP_depth = tuning_parameter_array[3].value;
    int RFP_margin = tuning_parameter_array[4].value;

    int LMP_depth = tuning_parameter_array[5].value;
    int LMP_margin = tuning_parameter_array[6].value;

    int quiet_LMP_depth = tuning_parameter_array[7].value;
    int quiet_LMP_margin = tuning_parameter_array[8].value;
    int quiet_LMP_improving_margin = tuning_parameter_array[9].value;

    int history_pruning_depth = tuning_parameter_array[10].value;
    int history_pruning_divisor = tuning_parameter_array[11].value;

    int NMP_depth = tuning_parameter_array[12].value;
    int NMP_base = tuning_parameter_array[13].value;
    int NMP_depth_divisor = tuning_parameter_array[14].value;
    int NMP_eval_divisor = tuning_parameter_array[15].value;
};


struct Move_Ordering_Parameters {
    T tuning_parameter_array[8] = {
            T{"winning_capture_margin", 5000, 50000, 50000, 1750},
            T{"base_capture_margin", -10000, 8000, -500, 2000},
            T{"capture_scale", 1, 20, 3, 2},
            T{"queen_promotion_margin", 20000, 200000, 100000, 1500},
            T{"other_promotion_margin", -20000, 10000, -30000, 2000},
            T{"first_killer_margin", 5000, 50000, 30000, 1000},
            T{"second_killer_margin", 1000, 49000, 25000, 1500},
            T{"castle_margin", 0, 2000, 1200, 200},
    };

    int winning_capture_margin = tuning_parameter_array[0].value;
    int base_capture_margin = tuning_parameter_array[1].value;
    int capture_scale = tuning_parameter_array[2].value;
    int queen_promotion_margin = tuning_parameter_array[3].value;
    int other_promotion_margin = tuning_parameter_array[4].value;
    int first_killer_margin = tuning_parameter_array[5].value;
    int second_killer_margin = tuning_parameter_array[6].value;
    int castle_margin = tuning_parameter_array[7].value;
};


class Thread_State {

public:

    Thread_State() = default;

    Position position{};

    PLY_TYPE current_search_depth = 0;
    PLY_TYPE search_ply = 0;
    PLY_TYPE game_ply = 0;
    PLY_TYPE fifty_move = 0;

    InformativeMove killer_moves[2][MAX_AB_DEPTH]{};  // killer moves (2) | max_depth (64)
    SCORE_TYPE history_moves[12][64]{}; // piece | target_square
    SCORE_TYPE capture_history[12][12][64]{};
    SCORE_TYPE continuation_history[12][64][12][64]{};

    HASH_TYPE repetition_table[TOTAL_MAX_DEPTH + 512] = {0};

    bool do_move_ordering_tuning = false;
    Move_Ordering_Parameters move_ordering_parameters{};

    bool terminated = true;

    bool detect_repetition();
};


class Engine {

public:

    Engine() = default;

    int num_threads = 1;
    std::vector<Thread_State> thread_states;

    bool stopped = true;

    double LMR_REDUCTIONS_QUIET[MAX_AB_DEPTH][64]{};
    double LMR_REDUCTIONS_NOISY[MAX_AB_DEPTH][64]{};

    PLY_TYPE selective_depth = 0;

    PLY_TYPE max_depth = MAX_AB_DEPTH - 1;
    PLY_TYPE max_q_depth = TOTAL_MAX_DEPTH - MAX_AB_DEPTH;
    PLY_TYPE min_depth = 1;

    int move_overhead = 10;
    uint64_t hard_time_limit = 60000;
    uint64_t soft_time_limit = 60000;
    uint64_t start_time = 0;

    uint64_t max_nodes = 0;
    uint64_t primary_thread_node_count = 0;
    uint64_t node_count = 0;
    uint64_t node_table[12][64]{};

    Move pv_table[MAX_AB_DEPTH + 1][MAX_AB_DEPTH + 1]{};
    PLY_TYPE pv_length[MAX_AB_DEPTH + 1] = {0};

    // TT_Entry transposition_table[MAX_TT_SIZE]{};
    std::vector<TT_Entry> transposition_table;

    bool show_stats = false;
    Search_Results search_results{};

    bool do_tuning = false;
    Tuning_Parameters tuning_parameters{};

    void clear_tt();

    void reset();
    void new_game();

    void initialize_lmr_reductions();

    short probe_tt_entry(int thread_id, HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth,
                         TT_Entry& return_entry);
    void record_tt_entry(int thread_id, HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, Move move, PLY_TYPE depth,
                         SCORE_TYPE static_eval, bool pv_node);
    short probe_tt_entry_q(int thread_id, HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta,
                           SCORE_TYPE& return_score, Move& tt_move);
    void record_tt_entry_q(int thread_id, HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, Move move,
                           SCORE_TYPE static_eval);
    SCORE_TYPE probe_tt_evaluation(HASH_TYPE hash_key);

    void tt_prefetch_read(HASH_TYPE hash_key);
    void tt_prefetch_write(HASH_TYPE hash_key);

    bool check_time();
};

void update_history_entry(SCORE_TYPE& score, SCORE_TYPE bonus);

SCORE_TYPE qsearch(Engine& engine, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth, int thread_id);
SCORE_TYPE negamax(Engine& engine, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth,  bool do_null, int thread_id);

void print_thinking(Engine& engine, NodeType node, SCORE_TYPE best_score, int thread_id);
SCORE_TYPE aspiration_window(Engine& engine, SCORE_TYPE previous_score, PLY_TYPE& asp_depth, Move& best_move, int thread_id);
void iterative_search(Engine& engine, int thread_id);
void lazy_smp_search(Engine& engine);

void print_statistics(Search_Results& res);

void print_search_tuning_config(Tuning_Parameters& tuning_parameters);
void print_move_ordering_tuning_config(Move_Ordering_Parameters& tuning_parameters);

#endif //ANTARESCHESSENGINE_SEARCH_H
