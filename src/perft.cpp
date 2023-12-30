
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

    position.set_state(position.state_stack[ply], fifty);
    position.get_pseudo_legal_moves<Movegen::All, true>(position.scored_moves[ply]);

    for (ScoredMove& scored_move : position.scored_moves[ply]) {

        Move move = scored_move.move;
        // std::cout << "move: " << get_uci_from_move(position, move) << std::endl;

        bool attempt = position.make_move<NO_NNUE>(move, position.state_stack[ply], fifty);

        if (!attempt) {
            position.undo_move<NO_NNUE>(move, position.state_stack[ply], fifty);
            continue;
        }

        if (depth == 1) {
            int move_type = move.type();

            if (move.is_capture(position)) {
                res.capture_amount += 1;
            }
            else if (move_type == MOVE_TYPE_EP) {
                res.capture_amount += 1;
                res.ep_amount += 1;
            }
            else if (move_type == MOVE_TYPE_PROMOTION) res.promotion_amount += 1;
            else if (move_type == MOVE_TYPE_CASTLE) res.castle_amount += 1;

            if (position.is_attacked(position.get_king_pos(position.side), position.side)) res.check_amount += 1;
        }

        debug_perft(position, res, depth - 1, ply + 1);

        position.undo_move<NO_NNUE>(move, position.state_stack[ply], fifty);
    }

}



long long fast_perft(Position& position, PLY_TYPE depth, PLY_TYPE ply) {

    // std::cout << position.state_stack[ply - 1].move.normal_move().get_uci(position) << std::endl;
    // std::cout << position;

    /*
    if (depth == 0) {
        return 1;
    }
    */

    PLY_TYPE fifty = 0;

    position.set_state(position.state_stack[ply], fifty);
    position.get_pseudo_legal_moves<Movegen::All, true>(position.scored_moves[ply]);

    long long amt = 0;

    for (ScoredMove& scored_move : position.scored_moves[ply]) {

        Move move = scored_move.move;

        bool attempt = position.make_move<NO_NNUE>(move, position.state_stack[ply], fifty);

        if (!attempt) {
            position.undo_move<NO_NNUE>(move, position.state_stack[ply], fifty);
            continue;
        }

        amt += depth == 1 ? 1 : fast_perft(position, depth - 1, ply + 1);
        // amt += fast_perft(position, depth - 1, ply + 1);

        position.undo_move<NO_NNUE>(move, position.state_stack[ply], fifty);
    }

    return amt;

}


long long uci_perft(Position& position, PLY_TYPE depth, PLY_TYPE ply) {

    PLY_TYPE fifty = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    if (depth == 0) {
        return 1;
    }

    position.set_state(position.state_stack[ply], fifty);
    position.get_pseudo_legal_moves<Movegen::All, true>(position.scored_moves[ply]);

    long long total_amt = 0;

    for (ScoredMove& scored_move : position.scored_moves[ply]) {

        Move move = scored_move.move;

        bool attempt = position.make_move<NO_NNUE>(move, position.state_stack[ply], fifty);

        if (!attempt) {
            position.undo_move<NO_NNUE>(move, position.state_stack[ply], fifty);
            continue;
        }

        long long amt = depth == 1 ? 1 : fast_perft(position, depth - 1, ply + 1);
        total_amt += amt;

        position.undo_move<NO_NNUE>(move, position.state_stack[ply], fifty);

        std::cout << move.get_uci(position) << ": " << amt << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Nodes searched: " << total_amt << std::endl;
    std::cout << "Perft speed: " << double(total_amt) / ms_int.count() / 1000 << "mn/s" << std::endl;
    std::cout << "Total time: " << ms_int.count() << std::endl;

    return total_amt;

}