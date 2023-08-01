

#include <iostream>
#include "position.h"
#include "perft.h"
#include "uci.h"

int main(int argc, char* argv[]) {

    /*
    Position position{};
    position.set_fen(START_FEN);

    uci_perft(position, 6, 0);

    return 0;
     */

    UCI main_uci;
    main_uci.initialize_uci();

    // Begin the UCI input loop
    main_uci.uci_loop();


    return 0;
}
