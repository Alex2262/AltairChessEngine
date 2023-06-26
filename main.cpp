

#include <iostream>
#include "position.h"

int main(int argc, char* argv[]) {

    Position position{};
    position.set_fen("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ");
    std::cout << position;

    position.get_pseudo_legal_moves(position.scored_moves[0]);
    std::cout << position.scored_moves[0].size() << std::endl;

    for (ScoredMove scored_move : position.scored_moves[0]) {
        std::cout << scored_move.move.get_uci(position) << std::endl;
    }

    /*
    UCI main_uci;
    main_uci.initialize_uci();

    // BENCH arg-parsing

    bool bench_flag = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "bench") == 0) {
            bench_flag = true;
        }
    }


    if (bench_flag) {
        run_bench(*main_uci.engine, BENCH_DEPTH);
        return 0;
    }


    // Begin the UCI input loop
    main_uci.uci_loop();
    */

    return 0;
}
