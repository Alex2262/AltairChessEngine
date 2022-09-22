//
// Created by Alex Tian on 9/18/2022.
//

#include <iostream>
#include <chrono>
#include "perft.h"
#include "move_generator.h"
#include "move.h"

void debug_perft(Position& position, Perft_Result_Type& res, PLY_TYPE depth) {

    // position.print_board();
    // std::cout << depth << std::endl;

    if (depth == 0) {
        res.total_amount += 1;
        return;
    }

    std::vector<MOVE_TYPE> moves = get_pseudo_legal_moves(position);

    SQUARE_TYPE current_ep_square = position.ep_square;
    uint16_t current_castle_ability_bits = position.castle_ability_bits;
    uint64_t current_hash_key = position.hash_key;

    for (MOVE_TYPE move : moves) {

        // std::cout << "move: " << get_uci_from_move(move) << std::endl;

        bool attempt = position.make_move(move);

        if (!attempt) {
            position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
            continue;
        }

        position.side ^= 1;

        if (depth == 1) {
            int move_type = get_move_type(move);

            if (get_is_capture(move)) res.capture_amount += 1;
            else if (move_type == MOVE_TYPE_EP) {
                res.capture_amount += 1;
                res.ep_amount += 1;
            }
            else if (move_type == MOVE_TYPE_PROMOTION) res.promotion_amount += 1;
            else if (move_type == MOVE_TYPE_CASTLE) res.castle_amount += 1;

            if (position.is_attacked(position.king_positions[position.side])) res.check_amount += 1;
        }

        debug_perft(position, res, depth - 1);

        position.side ^= 1;
        position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
    }

}



int fast_perft(Position& position, PLY_TYPE depth) {

    if (depth == 0) {
        return 1;
    }

    std::vector<MOVE_TYPE> moves = get_pseudo_legal_moves(position);

    SQUARE_TYPE current_ep_square = position.ep_square;
    uint16_t current_castle_ability_bits = position.castle_ability_bits;
    uint64_t current_hash_key = position.hash_key;

    int amt = 0;

    for (MOVE_TYPE move : moves) {

        bool attempt = position.make_move(move);

        if (!attempt) {
            position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
            continue;
        }

        position.side ^= 1;

        amt += fast_perft(position, depth - 1);

        position.side ^= 1;
        position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
    }

    return amt;

}


int uci_perft(Position& position, PLY_TYPE depth) {

    auto start_time = std::chrono::high_resolution_clock::now();

    if (depth == 0) {
        return 1;
    }

    std::vector<MOVE_TYPE> moves = get_pseudo_legal_moves(position);

    SQUARE_TYPE current_ep_square = position.ep_square;
    uint16_t current_castle_ability_bits = position.castle_ability_bits;
    uint64_t current_hash_key = position.hash_key;

    int total_amt = 0;

    for (MOVE_TYPE move : moves) {

        bool attempt = position.make_move(move);

        if (!attempt) {
            position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
            continue;
        }

        position.side ^= 1;

        int amt = fast_perft(position, depth - 1);
        total_amt += amt;

        position.side ^= 1;
        position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);

        std::cout << "Move " + get_uci_from_move(move) << ": " << amt << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Nodes searched: " << total_amt << std::endl;
    std::cout << "Perft speed: " << double(total_amt) / ms_int.count() / 1000 << "kn/s" << std::endl;
    std::cout << "Total time: " << ms_int.count();

    return total_amt;

}