//
// Created by Alex Tian on 9/30/2022.
//

#include <iostream>
#include "uci.h"
#include "useful.h"
#include "move.h"
#include "search.h"
#include "evaluation.h"

void UCI::initialize_uci() {
    position.set_fen(START_FEN);
    //position.undo_move_stack.resize(TOTAL_MAX_DEPTH);
    engine.transposition_table.resize(MAX_TT_SIZE);

    //for (int i = 0; i < MAX_TT_SIZE; i++) {
    //    std::cout << engine.transposition_table[i].evaluation << std::endl;
    //}
    initialize_lmr_reductions();
}


void  UCI::time_handler(long self_time, long inc, long movetime, long movestogo) {
    double rate = 20;
    long time_amt;

    if (position.is_attacked(position.king_positions[position.side])) rate -= 3;
    if (get_is_capture(last_move)) rate -= 1.5;

    if (movetime > 0) time_amt = movetime * 0.9;
    else if (inc > 0 && movestogo > 0) {
        time_amt = (self_time * 0.8 / movestogo) * (20 / rate) + (inc / 2.0);
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
            long bound = static_cast<long>(inc / 2.5 * sqrt(60000.0 / inc));
            if (inc > bound / 2.5) bound = static_cast<long>(inc * sqrt(90000.0 / inc));
            if (inc > bound / 2.5) bound = static_cast<long>(1.5 * inc * sqrt(200000.0 / inc));
            time_amt = std::max(inc * 0.975 + (self_time - bound) / (rate * 1.8), self_time / (rate * 10));
        }
    }
    else if (movestogo > 0) {
        time_amt = (self_time * 0.9 / movestogo) * (20 / rate);
        if (time_amt > self_time * 0.9) time_amt = self_time * 0.95;
    }
    else if (self_time > 0) time_amt = self_time / (rate + 6);
    else time_amt = engine.max_time;

    engine.max_time = time_amt;
}


void UCI::parse_position() {
    if (tokens.size() < 2) return;

    int next_idx;
    engine.game_ply = 0;

    if (tokens[1] == "startpos") {
        position.set_fen(START_FEN);
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
    int d = engine.max_depth;
    long wtime = 0, btime = 0, winc = 0, binc = 0, movetime = 0, movestogo = 0;

    for (int i = 1; i < tokens.size(); i += 2) {
        std::string type = tokens[i];
        int value = std::stoi(tokens[i + 1]);

        if (type == "depth") d = value;

        else if (type == "movetime") movetime = value;

        else if (type == "wtime") wtime = value;
        else if (type == "btime") btime = value;

        else if (type == "winc") winc = value;
        else if (type == "binc") binc = value;

        else if (type == "movestogo") movestogo = value;

    }

    int self_time = (position.side == 0) ? wtime : btime;
    int inc = (position.side == 0) ? winc : binc;

    time_handler(self_time, inc, movetime, movestogo);

    engine.max_depth = d;

    std::cout << engine.max_time << std::endl;

    iterative_search(engine, position);
}


void UCI::uci_loop() {

    while (true) {
        msg = "";
        tokens.clear();

        getline(std::cin, msg);
        tokens = split(msg, ' ');

        if (msg == "quit") {
            engine.stopped = true;
            break;
        }

        if (msg == "stop") engine.stopped = true;

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