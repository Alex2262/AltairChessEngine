
#pragma once

#include <vector>
#include <unordered_set>
#include "position.h"
#include "move_ordering.h"

// #define DO_SEARCH_TUNING
// #define SHOW_STATISTICS

constexpr double learning_rate = 0.002;

constexpr int correction_history_grain = 256;
constexpr int correction_history_weight_scale = 1024;
constexpr int correction_history_size = 16384;
constexpr int correction_history_max = correction_history_grain * 64;


struct TT_Entry {                          // 22 bytes --> 24 bytes
    Hash  key        = 0;             // 8 bytes
    Score score      = SCORE_NONE;    // 4 bytes
    Score evaluation = NO_EVALUATION; // 4 bytes
    Move       move       = NO_MOVE;       // 2 bytes
    Ply   depth      = 0;             // 2 bytes
    short      flag       = 0;             // 1 byte
    bool       pv_node    = false;         // 1 byte
};


struct SearchResults {
    int num_searches = 1;
    uint64_t node_count = 0;

    uint64_t qsearch_fail_highs[FAIL_HIGH_STATS_COUNT]{};
    uint64_t search_fail_highs[FAIL_HIGH_STATS_COUNT]{};
    uint64_t search_fail_high_types[6]{};

    uint64_t alpha_raised_count = 0;
    uint64_t search_alpha_raises[ALPHA_RAISE_STATS_COUNT]{};

    Ply depth_reached = 0;

    Move best_move = NO_MOVE;
    Score score = 0;
};




class Thread_State {

public:

    inline Thread_State() :
        generators(TOTAL_MAX_DEPTH),
        searched_quiets(TOTAL_MAX_DEPTH),
        searched_noisy(TOTAL_MAX_DEPTH) {
        reset_generators();
    };

    int thread_id = 0;

    Ply selective_depth = 0;

    Position position{};

    Ply current_search_depth = 0;
    Ply search_ply = 0;
    Ply base_full_moves = 1;
    Ply game_ply = 0;
    Ply fifty_move = 0;

    uint64_t node_count = 0;

    std::unordered_set<uint16_t> excluded_root_moves{};

    InformativeMove killer_moves[2][MAX_AB_DEPTH]{};  // killer moves (2) | max_depth (64)
    Score history_moves[12][64][2][2]{}; // piece | target_square | origin_threat | target_threat
    Score capture_history[2][12][12][64]{};
    Score continuation_history[12][64][12][64]{};
    Score correction_history[2][correction_history_size]{};
    Score correction_history_np[2][correction_history_size]{};
    Score correction_history_major[2][correction_history_size]{};
    Score correction_history_minor[2][correction_history_size]{};

    Hash repetition_table[TOTAL_MAX_DEPTH + MAX_GAME_LENGTH + 5]{};

    bool terminated = true;

    std::vector<Generator> generators;
    std::vector<FixedVector<ScoredMove, MAX_MOVES>> searched_quiets;
    std::vector<FixedVector<ScoredMove, MAX_NOISY>> searched_noisy;

    inline Ply get_full_game_ply() const { return base_full_moves * 2 + game_ply + position.side; }
    bool detect_repetition();

    Score& get_continuation_history_entry(InformativeMove last_move, InformativeMove informative_move);

    void update_correction_history_entry(Score& c_hist_entry, Ply depth, Score diff);
    void update_correction_history_score(Ply depth, Score diff);
    Score get_correction_score(Score& c_hist_entry);
    Score correct_evaluation(Score evaluation);

    inline void reset_generators() {
        for (int ply = 0; ply < static_cast<int>(generators.size()); ply++) {
            Generator& generator = generators[ply];
            generator = Generator(*this);
            generator.search_ply = ply;
            generator.scored_moves.clear();
        }
    }
};


class Engine {

public:
    Engine() = default;

    int num_threads = 1;
    std::vector<Thread_State> thread_states;

    bool stopped = true;
    bool use_nnue = true;
    bool print_thinking = true;
    bool datagen = false;
    bool show_wdl = false;

    int multi_pv = 1;

    int LMR_REDUCTIONS_QUIET[MAX_AB_DEPTH][64]{};

    Ply max_depth = MAX_AB_DEPTH - 1;
    Ply max_q_depth = MAX_QS_DEPTH - 1;
    Ply min_depth = 1;

    int move_overhead = 50;
    uint64_t hard_time_limit = 60000;
    uint64_t soft_time_limit = 60000;
    uint64_t start_time = 0;

    uint64_t soft_node_limit = 0;
    uint64_t hard_node_limit = 0;

    uint64_t node_table[12][64]{};

    Move pv_table[MAX_AB_DEPTH + 1][MAX_AB_DEPTH + 1]{};
    Ply pv_length[MAX_AB_DEPTH + 1] = {0};

    std::vector<TT_Entry> transposition_table;

    SearchResults search_results{};

    std::unordered_set<uint16_t> root_moves{};

    void reset();
    void new_game();
    void initialize_lmr_reductions();

    void clear_tt();
    void resize_tt(uint64_t mb);
    short probe_tt_entry(int thread_id, Hash hash_key, Score alpha, Score beta, Ply depth, TT_Entry& return_entry);
    void record_tt_entry(int thread_id, Hash hash_key, Score score, short tt_flag, Move move, Ply depth, Score static_eval, bool tt_pv);
    short probe_tt_entry_q(int thread_id, Hash hash_key, Score alpha, Score beta, TT_Entry& return_entry);
    void record_tt_entry_q(int thread_id, Hash hash_key, Score score, short tt_flag, Move move, Score static_eval, bool tt_pv);
    Score probe_tt_evaluation(Hash hash_key);
    void tt_prefetch_read(Hash hash_key);

    bool check_time();
    bool check_nodes();

    Score evaluate(int thread_id);
};

void update_history_entry(Score& score, Score bonus, Score max_score);
void update_histories(Thread_State& thread_state, InformativeMove informative_move,
                      InformativeMove last_moves[], bool quiet, bool winning_capture,
                      int bonus);

Score qsearch(Engine& engine, Score alpha, Score beta, Ply depth, int thread_id);
Score negamax(Engine& engine, Score alpha, Score beta, Ply depth, bool do_null, bool cutnode, int thread_id);

void print_thinking(Engine& engine, NodeType node, Score best_score, int pv_number, int thread_id);

Score aspiration_window(Engine& engine, Score previous_score, Ply& asp_depth, Move& best_move, int thread_id);
Score multi_pv_search(Engine& engine, Score previous_score, Ply& asp_depth, Move& best_move, int thread_id);
void iterative_search(Engine& engine, int thread_id);
void lazy_smp_search(Engine& engine);
void search(Engine& engine);

void print_statistics(SearchResults& res);

void print_search_tuning_config();
