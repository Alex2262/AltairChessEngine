

#ifndef ALTAIR_UCI_H
#define ALTAIR_UCI_H

#include <memory>
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

    std::string original_fen = START_FEN;
    std::vector<Move> moves;

    FenInfo original_fen_info{};

    void initialize_uci();
    void update_position(std::string& given);
    void parse_position_moves();
    void parse_position();
    void parse_go();
    void uci_loop();
};



#endif //ALTAIR_UCI_H
