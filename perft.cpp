//
// Created by Alex Tian on 9/18/2022.
//

#include <iostream>
#include <chrono>
#include "perft.h"
#include "move.h"

void debug_perft(Position& position, Perft_Result_Type& res, PLY_TYPE depth, PLY_TYPE ply) {

    // position.print_board();
    // std::cout << depth << std::endl;

    if (depth == 0) {
        res.total_amount += 1;
        return;
    }

    PLY_TYPE fifty = 0;

    position.set_state(ply, fifty, NO_EVALUATION);
    position.get_pseudo_legal_moves(ply);

    for (MOVE_TYPE move : position.moves[ply]) {

        // std::cout << "move: " << get_uci_from_move(move) << std::endl;

        bool attempt = position.make_move(move, ply, fifty);

        if (!attempt) {
            position.undo_move(move, ply, fifty);
            continue;
        }

        position.side ^= 1;

        if (depth == 1) {
            int move_type = get_move_type(move);

            if (get_is_capture(move)) {
                res.capture_amount += 1;
            }
            else if (move_type == MOVE_TYPE_EP) {
                res.capture_amount += 1;
                res.ep_amount += 1;
            }
            else if (move_type == MOVE_TYPE_PROMOTION) res.promotion_amount += 1;
            else if (move_type == MOVE_TYPE_CASTLE) res.castle_amount += 1;

            if (position.is_attacked(position.king_positions[position.side])) res.check_amount += 1;
        }

        debug_perft(position, res, depth - 1, ply + 1);

        position.side ^= 1;
        position.undo_move(move, ply, fifty);
    }

}



long long fast_perft(Position& position, PLY_TYPE depth, PLY_TYPE ply) {

    if (depth == 0) {
        return 1;
    }

    PLY_TYPE fifty = 0;

    position.set_state(ply, fifty, NO_EVALUATION);
    position.get_pseudo_legal_moves(ply);

    long long amt = 0;

    for (MOVE_TYPE move : position.moves[ply]) {

        bool attempt = position.make_move(move, ply, fifty);

        if (!attempt) {
            position.undo_move(move, ply, fifty);
            continue;
        }

        position.side ^= 1;

        amt += fast_perft(position, depth - 1, ply + 1);

        position.side ^= 1;
        position.undo_move(move, ply, fifty);
    }

    return amt;

}


long long uci_perft(Position& position, PLY_TYPE depth, PLY_TYPE ply) {

    PLY_TYPE fifty = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    if (depth == 0) {
        return 1;
    }

    position.set_state(ply, fifty, NO_EVALUATION);
    position.get_pseudo_legal_moves(ply);

    long long total_amt = 0;

    for (MOVE_TYPE move : position.moves[ply]) {

        bool attempt = position.make_move(move, ply, fifty);

        if (!attempt) {
            position.undo_move(move, ply, fifty);
            continue;
        }

        position.side ^= 1;

        long long amt = fast_perft(position, depth - 1, ply + 1);
        total_amt += amt;

        position.side ^= 1;
        position.undo_move(move, ply, fifty);

        std::cout << "Move " + get_uci_from_move(move) << ": " << amt << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Nodes searched: " << total_amt << std::endl;
    std::cout << "Perft speed: " << double(total_amt) / ms_int.count() / 1000 << "mn/s" << std::endl;
    std::cout << "Total time: " << ms_int.count() << std::endl;

    return total_amt;

}