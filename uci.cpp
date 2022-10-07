//
// Created by Alex Tian on 9/30/2022.
//

#include <iostream>
#include "uci.h"
#include "useful.h"
#include "move.h"
#include "evaluation.h"

void UCI::initialize_uci() {
    position.set_fen(START_FEN);
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

        position.set_fen(fen);
        next_idx = 8;
    }

    else return;

    if (tokens.size() <= next_idx || tokens[next_idx] != "moves") return;

    for (int i = next_idx + 1; i < tokens.size(); i++) {
        // std::cout << tokens[i] << std::endl;
        MOVE_TYPE move = get_move_from_uci(position, tokens[i]);
        // std::cout << move << " " << get_uci_from_move(move) << std::endl;
        position.make_move(move, engine.fifty_move);

        engine.game_ply++;
        engine.fifty_move++;
        engine.repetition_table[engine.game_ply] = position.hash_key;

        position.side ^= 1;
    }

    // std::cout << engine.detect_repetition() << std::endl;

    // position.print_board();
}


void UCI::parse_go() {
    int d = engine.max_depth, wtime = 0, btime = 0, winc = 0, binc = 0, movetime = 0, movestogo = 0;

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

    if (movetime != 0) engine.max_time = movetime / 10 * 9;
    else engine.max_time = int(self_time / 25.0 + inc / 2.0);

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
            std::cout << "id name AntaresCpp0.00" << std::endl;
            std::cout << "id author Alexander_Tian" << std::endl;
            std::cout << "uciok" << std::endl;
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