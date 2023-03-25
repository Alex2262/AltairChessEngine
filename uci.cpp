//
// Created by Alex Tian on 9/30/2022.
//

#include <iostream>
#include <unistd.h>
#include "uci.h"
#include "useful.h"
#include "move.h"
#include "search.h"
#include "evaluation.h"
#include "perft.h"

void UCI::initialize_uci() {
    position.set_fen(START_FEN);
    //engine.transposition_table.resize(MAX_TT_SIZE);

    int mb = 2048;
    engine.transposition_table.resize(mb * (1000000 / 24));

    initialize_lmr_reductions();

    std::cout << engine.transposition_table.size() << " number of hash entries" << std::endl;
}


void  UCI::time_handler(double self_time, double inc, double movetime, long movestogo) {
    double rate = 20;
    double time_amt;

    if (position.is_attacked(position.king_positions[position.side])) rate -= 3;
    if (get_is_capture(last_move)) rate -= 1.5;

    if (movetime > 0) time_amt = movetime * 0.9;
    else if (inc > 0 && movestogo > 0) {
        time_amt = (self_time * 0.8 / static_cast<double>(movestogo)) * (20 / rate) + (inc / 2.0);
        if (time_amt > self_time * 0.8) time_amt = self_time * 0.85 + (inc / 2.0);
    }
    else if (inc > 0) {

        // we always want to have more time than our increment.
        // This ensures we use a lot of our remaining time, but
        // since our increment is larger, it doesn't matter.
        if (self_time < inc) time_amt = self_time / (rate / 10);
        else {
            // If our remaining time is less than the boundary, we should use less time than our increment
            // to get back above the boundary.
            double bound = inc / 2.5 * sqrt(60000.0 / inc);
            if (inc > bound / 2.5) bound = inc * sqrt(90000.0 / inc);
            if (inc > bound / 2.5) bound = 1.5 * inc * sqrt(200000.0 / inc);
            time_amt = std::max(inc * 0.975 + (self_time - bound) / (rate * 1.8), self_time / (rate * 10));
        }
    }
    else if (movestogo > 0) {
        time_amt = (self_time * 0.9 / static_cast<double>(movestogo)) * (20 / rate);
        if (time_amt > self_time * 0.9) time_amt = self_time * 0.95;
    }
    else if (self_time > 0) time_amt = self_time / (rate + 6);
    else time_amt = static_cast<double>(engine.hard_time_limit);

    engine.hard_time_limit = static_cast<long>(time_amt * 2.3);
    engine.soft_time_limit = static_cast<long>(time_amt * 0.7);

    if (engine.hard_time_limit > static_cast<long>(self_time * 0.7)) {
        for (int multiplier = 18; multiplier >= 10; multiplier -= 1) {
            engine.hard_time_limit = static_cast<long>(time_amt * (multiplier / 10.0));
            if (engine.hard_time_limit <= static_cast<long>(self_time * 0.7)) break;
        }
    }

    if (engine.hard_time_limit > static_cast<long>(movetime) && movetime != 0.0) {
        engine.hard_time_limit = static_cast<long>(time_amt);
    }

    std::cout << time_amt << " " << engine.hard_time_limit << " " << engine.soft_time_limit << std::endl;
}


void UCI::parse_position() {
    if (tokens.size() < 2) return;

    int next_idx;
    engine.game_ply = 0;

    if (tokens[1] == "startpos") {
        engine.fifty_move = position.set_fen(START_FEN);
        next_idx = 2;
    }

    else if (tokens[1] == "fen") {
        std::string fen;
        for (int i = 2; i < 8; i++) {
            fen += tokens[i];
            fen += " ";
        }

        engine.fifty_move = position.set_fen(fen);
        next_idx = 8;
    }

    else return;

    if (tokens.size() <= next_idx || tokens[next_idx] != "moves") return;

    for (int i = next_idx + 1; i < tokens.size(); i++) {
        // std::cout << tokens[i] << std::endl;
        MOVE_TYPE move = get_move_from_uci(position, tokens[i]);
        last_move = move;
        // std::cout << move << " " << get_uci_from_move(move) << std::endl;
        position.make_move(move, 0, engine.fifty_move);

        engine.game_ply++;
        engine.fifty_move++;
        engine.repetition_table[engine.game_ply] = position.hash_key;

        position.side ^= 1;
    }

    // std::cout << engine.detect_repetition() << std::endl;

    // position.print_board();
}


void UCI::parse_go() {
    PLY_TYPE d = 0, perft_depth = -1;
    double wtime = 0, btime = 0, winc = 0, binc = 0, movetime = 0;
    long movestogo = 0;
    bool infinite = false;

    for (int i = 1; i < tokens.size(); i += 2) {
        std::string type = tokens[i];

        uint64_t value = 0;

        if (tokens.size() > i + 1) value = std::stoi(tokens[i + 1]);

        if (type == "depth") d = static_cast<PLY_TYPE>(value);

        else if (type == "perft") perft_depth = static_cast<PLY_TYPE>(value);

        else if (type == "nodes") engine.max_nodes = value;

        else if (type == "movetime") movetime = static_cast<double>(value);

        else if (type == "wtime") wtime = static_cast<double>(value);
        else if (type == "btime") btime = static_cast<double>(value);

        else if (type == "winc") winc = static_cast<double>(value);
        else if (type == "binc") binc = static_cast<double>(value);

        else if (type == "movestogo") movestogo = static_cast<long>(value);
        else if (type == "infinite") infinite = true;

    }

    if (perft_depth > -1) {
        position.print_board();
        uci_perft(position, perft_depth, 0);
        return;
    }
    if (infinite || (d && tokens.size() == 3)) {
        engine.hard_time_limit = 86400000;
        engine.soft_time_limit = 86400000;
    }
    else {
        double self_time = (position.side == 0) ? wtime : btime;
        double inc = (position.side == 0) ? winc : binc;

        time_handler(self_time, inc, movetime, movestogo);
    }

    if (d) engine.max_depth = d;

    engine.stopped = true;
    if (!search_threads.empty()) {
        search_threads[0].join();

        while (!engine.terminated);  // to prevent some stupid exceptions
        if (engine.terminated) search_threads.erase(search_threads.end() - 1);
    }

    search_threads.emplace_back(iterative_search, std::ref(engine), std::ref(position));

    //iterative_search(engine, position);
}


void UCI::uci_loop() {

    while (true) {
        msg = "";
        tokens.clear();

        getline(std::cin, msg);
        tokens = split(msg, ' ');

        if (msg == "quit") {
            break;
        }

        if (msg == "stop") {
            engine.stopped = true;
            if (!search_threads.empty()) {
                search_threads[0].join();

                while (!engine.terminated);  // to prevent some stupid exceptions
                if (engine.terminated) search_threads.erase(search_threads.end() - 1);
            }
        }

        else if (msg == "uci") {
            std::cout << "id name Altair" << std::endl;
            std::cout << "id author Alexander_Tian" << std::endl;

            std::cout << "option name Hash type spin default " << "64" << " min " << "1" << " max " << 1024
                      << std::endl;

            std::cout << "uciok" << std::endl;
        }

        else if (tokens[0] == "setoption" && tokens[2] == "Hash" && tokens.size() >= 5) {
            int mb = std::stoi(tokens[4]);
            mb = std::min(1024, std::max(1, mb));
            engine.transposition_table.resize(mb * (1000000 / 24));
            std::cout << engine.transposition_table.size() << " number of hash entries" << std::endl;
        }

        else if (msg == "isready") {
            std::cout << "readyok" << std::endl;
        }

        else if (msg == "ucinewgame") {
            position.set_fen(START_FEN);
            engine.new_game();
        }

        else if (tokens[0] == "position") {
            parse_position();
        }

        else if (tokens[0] == "go") {
            parse_go();
        }
    }
}