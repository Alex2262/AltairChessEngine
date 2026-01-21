
#pragma once

#include <chrono>
#include <vector>
#include "random.h"
#include "search.h"

inline constexpr int MAX_DG_GAME_LENGTH = 600;

struct EvalFenStruct {
    std::string fen;
    int eval;
};

struct Datagen_Thread {
    int thread_id   = 0;
    int game_length = 0;
    uint64_t total_fens  = 0;
    uint64_t total_games = 0;

    bool ping = false;
    bool paused = false;

    std::string current_stage = "none";

    PRNG prng = PRNG(0);

    FixedVector<ScoredMove, MAX_MOVES> scored_moves;
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    inline Datagen_Thread() {
        thread_id = 0;
    }

    inline explicit Datagen_Thread(int t_id, uint64_t random_seed) {
        thread_id = t_id;
        prng = PRNG(695848653836 + 6 * thread_id + random_seed);
    }
};

class Datagen {

    const uint64_t max_fens     = 10'000'000'000;
    const int soft_node_limit   =          5'000;
    const int hard_node_limit   =        800'000;
    const int max_time_per_move =            500;

    const int initial_random_moves_dfrc     =     8;
    const int initial_random_moves_standard =     8;
    const int opening_max_score             =   300;
    const int dfrc_chance                   =    50; // Out of 100
    // const uint64_t opening_chance        =   100;  // Out of 100

    const int win_adjudication_score   = 2000;
    const int win_adjudication_length  =    3;

    const int minimum_game_length = 15;
    const int fens_per_game       =  0;  // 0 for using all fens

    const std::string WDL_scores[3] = {"1.0", "0.5", "0.0"};

    std::vector<Datagen_Thread> datagen_threads;

    // std::vector<std::string> opening_fens{};

public:
    int threads = 1;
    int running_threads = 1;

    uint64_t random_seed = 0;
    uint64_t start_time;
    uint64_t interval_start_time;
    uint64_t interval_start_fens = 0;

    bool stopped = false;

    void integrity_check();
    void integrity_check_process();
    void start_datagen();

    std::string write_fen(Datagen_Thread& datagen_thread, const EvalFenStruct& eval_fen, double game_result);

    bool randomize_opening(Datagen_Thread& datagen_thread, FixedVector<Move, MAX_MOVES>& legal_moves) const;

    void datagen(Datagen_Thread& datagen_thread);

    std::vector<std::string> get_file_fens(const std::string &file_name);

    void merge();
};
