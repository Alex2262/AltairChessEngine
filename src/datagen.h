//
// Created by Alexander Tian on 8/16/23.
//

#ifndef ALTAIRCHESSENGINE_DATAGEN_H
#define ALTAIRCHESSENGINE_DATAGEN_H

#include <vector>
#include "random.h"
#include "search.h"

constexpr int MAX_GAME_LENGTH = 600;

struct Datagen_Thread {
    int thread_id   = 0;
    int total_fens  = 0;
    int total_games = 0;
    int game_length = 0;

    PRNG prng = PRNG(695848653836736222);

    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> start_time_point;

    explicit Datagen_Thread(int t_id) {thread_id = t_id; }
};

class Datagen {

    const int max_fens          = 100'000'000;
    const int nodes_per_move    =      80'000;
    const int max_time_per_move =         100;

    const int initial_random_moves      =   8;
    const int opening_max_score         = 400;
    const uint64_t opening_chance       = 100;  // Out of 100

    const int win_adjudication_score   = 400;
    const int win_adjudication_length  =   5;
    const int draw_adjudication_plies  =  70;
    const int draw_adjudication_score  =   8;
    const int draw_adjudication_length =  10;

    const int minimum_game_length = 20;
    const int fens_per_game       =  0;  // 0 for using all fens

    const std::string WDL_scores[3] = {"1.0", "0.5", "0.0"};

    std::vector<std::string> opening_fens{};

public:
    int threads = 1;

    bool stopped = false;

    void start_datagen();

    std::string write_fen(Datagen_Thread& datagen_thread, std::string& fen, double game_result);
    bool randomize_opening(Datagen_Thread& datagen_thread, FixedVector<Move, MAX_MOVES>& legal_moves) const;

    void datagen(Datagen_Thread datagen_thread);

    std::vector<std::string> get_file_fens(const std::string &file_name);

    void merge();
};


#endif //ALTAIRCHESSENGINE_DATAGEN_H