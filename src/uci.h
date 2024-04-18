

#ifndef ALTAIR_UCI_H
#define ALTAIR_UCI_H

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
};



#endif //ALTAIR_UCI_H
