//
// Created by Alex Tian on 9/30/2022.
//

#ifndef ANTARESCHESSENGINE_UCI_H
#define ANTARESCHESSENGINE_UCI_H

#include <thread>
#include <vector>
#include "position.h"
#include "search.h"

class UCI {

public:
    UCI() = default;
    ~UCI() = default;

    std::string msg{};
    std::vector<std::string> tokens{};

    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    Move last_move = NO_MOVE;

    std::vector<std::thread> search_threads{};

    void initialize_uci() const;
    void parse_position();
    void parse_go();
    void uci_loop();
    void time_handler(double self_time, double inc, double movetime, long movestogo) const;
};



#endif //ANTARESCHESSENGINE_UCI_H
