
#include <iostream>
#include <chrono>
#include "position.h"
#include "perft.h"
#include "search.h"
#include "uci.h"

int main() {

    /*Position main_position;
    Engine main_engine;

    main_position.set_fen(KIWIPETE_FEN);
    main_position.print_board();

    std::cout << "hi" << std::endl;*/

    /*for (int i = 1; i <= 5; i++) {
        Perft_Result_Type res = {0};

        auto start_time = std::chrono::high_resolution_clock::now();
        debug_perft(main_position, res, i, 0);
        auto end_time = std::chrono::high_resolution_clock::now();

        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "info depth " << i << " time " << ms_int.count() << " total " << res.total_amount << " captures "
                  << res.capture_amount << " checks " << res.check_amount << " ep " << res.ep_amount
                  << " castles " << res.castle_amount << " promotions " << res.promotion_amount << std::endl;
    }*/

    // uci_perft(main_position, 5, 0);

    // iterative_search(main_engine, main_position);

    UCI main_uci;

    main_uci.initialize_uci();
    main_uci.uci_loop();


    return 0;
}
