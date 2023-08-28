//
// Created by Alexander Tian on 7/31/23.
//

#ifndef ALTAIRCHESSENGINE_MCTS_H
#define ALTAIRCHESSENGINE_MCTS_H

#include "constants.h"
#include "position.h"

class Node {
public:
    uint32_t parent = 0;
    uint32_t children_start = 0;
    uint32_t children_end = 0;
    double win_count = 0;
    int visits = 1;
    Move last_move;

    Node(uint32_t c_parent, Move c_last_move) {
        parent = c_parent;
        win_count = 0;
        visits = 1;
        last_move = c_last_move;
    }
};


class Tree {
public:
    std::vector<Node> graph{};
};

class MCTS {
public:
    MCTS() = default;

    Position position{};
    Position test_position{};

    uint64_t start_time = 0;
    PLY_TYPE seldepth = 0;
    int iterations = 0;

    uint64_t max_time = MAX_TIME;

    uint32_t root_node_index = 0;

    PLY_TYPE temp_fifty_move = 0;

    Tree tree{};

    void new_game();
    void update_tree(Move move);
    void print_info();

    uint32_t select_best_child(uint32_t node_index);
    uint32_t selection();
    void expansion(uint32_t node_index);

    double evaluate_mcts();
    void back_propagation(uint32_t node_index, double evaluation, int result);
    uint32_t get_best_node();
    void search();

    void flatten_tree();
};

#endif //ALTAIRCHESSENGINE_MCTS_H
