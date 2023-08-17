//
// Created by Alexander Tian on 8/16/23.
//

#ifndef ALTAIRCHESSENGINE_DATAGEN_H
#define ALTAIRCHESSENGINE_DATAGEN_H

constexpr int MAX_GAME_LENGTH = 500;

class Datagen {

    const int max_fens = 6'000'000;
    const int nodes_per_move = 15'000;
    const int max_time_per_move = 2'000;
    const int threads = 8;

    const int initial_random_moves = 8;
    const int adjudication_score = 1500;
    const int adjudication_length = 5;

    const int minimum_game_length = 20;

    const std::string WDL_scores[3] = {"1.0", "0.5", "0.0"};

public:
    bool stopped = false;

    void start_datagen();
    void datagen(int thread_id);
    std::vector<std::string> get_file_fens(const std::string &file_name);
    void merge();
};


#endif //ALTAIRCHESSENGINE_DATAGEN_H
