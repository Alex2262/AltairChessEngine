//
// Created by Alexander Tian on 7/31/23.
//

#include <iostream>
#include <cmath>
#include <queue>
#include "mcts.h"
#include "evaluation.h"


void MCTS::new_game() {
    tree.graph.clear();
    root_node_index = 0;
    temp_fifty_move = 0;

    tree.graph.emplace_back(root_node_index, NO_MOVE);
}

void MCTS::update_tree(Move move) {
    for (int i = 0; i < tree.graph[root_node_index].children_end - tree.graph[root_node_index].children_start; i++) {
        uint32_t current_child_index = tree.graph[root_node_index].children_start + i;
        if (tree.graph[current_child_index].last_move == move) {
            root_node_index = current_child_index;
            return;
        }
    }

    tree.graph.emplace_back(root_node_index, move);
    root_node_index = tree.graph.size() - 1;
}

void MCTS::print_info() {

    std::string pv_line{};

    uint32_t original_root_node_index = root_node_index;

    std::vector<Move> attempted_moves{};

    while(true) {
        position.set_state(position.state_stack[attempted_moves.size()], temp_fifty_move);

        uint32_t best_node_index = get_best_node();
        if (tree.graph[best_node_index].visits < 2) break;

        pv_line += tree.graph[best_node_index].last_move.get_uci(position) + " ";

        root_node_index = best_node_index;
        if (tree.graph[root_node_index].children_end - tree.graph[root_node_index].children_start == 0) break;

        position.make_move(tree.graph[root_node_index].last_move, position.state_stack[attempted_moves.size()], temp_fifty_move);
        attempted_moves.push_back(tree.graph[root_node_index].last_move);
    }

    for (int i = attempted_moves.size() - 1; i >= 0; i--) {
        position.undo_move(attempted_moves[i], position.state_stack[i], temp_fifty_move);
    }

    root_node_index = original_root_node_index;

    uint32_t best_node_index = get_best_node();

    auto score = static_cast<int>(tree.graph[best_node_index].win_count /
                                  static_cast<double>(tree.graph[best_node_index].total_nodes)
                                  * CP_SCALE);

    std::cout << "info iteration " << iterations << " depth " << seldepth << " score cp " << score << " pv "
              << pv_line << std::endl;
}


uint32_t MCTS::selection() {
    uint32_t leaf_node_index = root_node_index;
    test_position = position;

    int depth = 0;
    while (true) {
        // std::cout << "selecting: " << leaf_node_index << std::endl;
        uint32_t current_node_index = leaf_node_index;
        uint32_t n_children = tree.graph[current_node_index].children_end - tree.graph[current_node_index].children_start;

        // std::cout << n_children << std::endl;
        if (n_children == 0) {
            break;
        }

        double best_uct = -1000000;

        for (int i = 0; i < n_children; i++) {
            uint32_t child_node_index = tree.graph[current_node_index].children_start + i;
            // assert(tree.graph[child_node_index].own_index == child_node_index);
            Node child_node = tree.graph[child_node_index];

            double exploitation_value = double(child_node.win_count) / child_node.total_nodes;
            double exploration_value = sqrt(std::log(tree.graph[current_node_index].total_nodes)
                                            / child_node.total_nodes);

            double uct_value = exploitation_value + EXPLORATION_CONSTANT * exploration_value;

            if (uct_value > best_uct) {

                leaf_node_index = child_node_index;
                best_uct = uct_value;
            }
        }

        test_position.set_state(test_position.state_stack[0], temp_fifty_move);
        test_position.make_move(tree.graph[leaf_node_index].last_move, test_position.state_stack[0], temp_fifty_move);

        depth++;

    }

    seldepth = std::max<PLY_TYPE>(seldepth, depth);
    return leaf_node_index;
}

void MCTS::expansion(uint32_t node_index) {

    test_position.get_pseudo_legal_moves(test_position.scored_moves[0]);
    test_position.set_state(test_position.state_stack[0], temp_fifty_move);
    tree.graph[node_index].children_start = tree.graph.size();

    for (ScoredMove scored_move : test_position.scored_moves[0]) {

        bool attempt = test_position.make_move(scored_move.move, test_position.state_stack[0], temp_fifty_move);

        test_position.undo_move(scored_move.move, test_position.state_stack[0], temp_fifty_move);

        if (!attempt) continue;

        tree.graph.emplace_back(node_index, scored_move.move);
    }

    tree.graph[node_index].children_end = tree.graph.size();
}

double MCTS::evaluate_mcts() {
    return tanh(evaluate(test_position) / CP_SCALE);
}

void MCTS::back_propagation(uint32_t node_index, double evaluation, int result) {

    uint32_t current_node_index = node_index;
    int current_side = test_position.side ^ 1;
    while (true) {
        Node& current_node = tree.graph[current_node_index];

        current_node.total_nodes++;
        if (current_side == result) current_node.win_count += 5;
        else if ((current_side ^ 1) == result) current_node.win_count -= 5;
        else if (result != DRAW_RESULT) {
            if (current_side == test_position.side) current_node.win_count += evaluation;
            else current_node.win_count -= evaluation;
        }

        if (current_node.parent == current_node_index) break;  // Hit root

        current_node_index = current_node.parent;
        current_side ^= 1;
    }
}

uint32_t MCTS::get_best_node() {
    int best = -1;
    uint32_t best_index = 0;
    for (int i = 0; i < tree.graph[root_node_index].children_end - tree.graph[root_node_index].children_start; i++) {
        Node& node = tree.graph[tree.graph[root_node_index].children_start + i];
        if (node.total_nodes >= best) {
            best = node.total_nodes;
            best_index = tree.graph[root_node_index].children_start + i;
        }
    }

    return best_index;
}

void MCTS::search() {
    seldepth = 0;
    iterations = 0;
    auto time = std::chrono::high_resolution_clock::now();
    start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

    flatten_tree();

    test_position = position;

    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
        iterations = iteration;

        // std::cout << "iteration " << iterations << std::endl;

        // std::cout << "selection" << std::endl;
        uint32_t selected_node_index = selection();

        tree.graph[selected_node_index].visits++;

        int node_result = NO_RESULT;

        if (tree.graph[selected_node_index].visits >= 2) {

            // std::cout << "expansion" << std::endl;
            expansion(selected_node_index);

            if (tree.graph[selected_node_index].children_end > tree.graph[selected_node_index].children_start) {
                test_position.set_state(test_position.state_stack[0], temp_fifty_move);

                int random_index = rand() % (tree.graph[selected_node_index].children_end - tree.graph[selected_node_index].children_start);
                selected_node_index = tree.graph[selected_node_index].children_start + random_index;

                test_position.make_move(tree.graph[selected_node_index].last_move, test_position.state_stack[0], temp_fifty_move);
            } else {
                node_result = test_position.is_attacked(test_position.get_king_pos(test_position.side), test_position.side) ?
                        test_position.side ^ 1 : DRAW_RESULT;
            }
        }

        double evaluation = evaluate_mcts();

        // std::cout << "back propagation" << std::endl;
        back_propagation(selected_node_index, evaluation, node_result);

        if ((iteration & 1023) == 0) {
            auto time = std::chrono::high_resolution_clock::now();
            uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

            if (current_time - start_time >= max_time) {
                break;
            }
        }

        if ((iteration % 10000) == 0 && iteration != 0) {
            print_info();
        }
    }

    print_info();
    std::cout << "bestmove " << tree.graph[get_best_node()].last_move.get_uci(position) << std::endl;
}

void MCTS::flatten_tree() {
    std::vector copy_graph = tree.graph;

    auto start_size = tree.graph.size();

    tree.graph.clear();

    std::queue<std::pair<uint32_t, uint32_t>> next_nodes_index;
    next_nodes_index.push({root_node_index, 0});
    tree.graph.push_back(copy_graph[root_node_index]);

    root_node_index = 0;

    tree.graph[0].parent = root_node_index;

    while (!next_nodes_index.empty()) {
        auto current_node_index = next_nodes_index.front();
        uint32_t old_node_index = current_node_index.first;
        uint32_t new_node_index = current_node_index.second;

        Node& current_old_node = copy_graph[old_node_index];
        Node& current_new_node = tree.graph[new_node_index];

        current_new_node.children_start = tree.graph.size();
        for (int i = 0; i < current_old_node.children_end - current_old_node.children_start; i++) {
            tree.graph.push_back(copy_graph[current_old_node.children_start + i]);
            tree.graph[tree.graph.size() - 1].parent = new_node_index;

            next_nodes_index.push({current_old_node.children_start + i, tree.graph.size() - 1});
        }

        current_new_node.children_end = tree.graph.size();

        next_nodes_index.pop();
    }

    std::cout << "Tree flattened from " << start_size << " to " << tree.graph.size() << std::endl;
}


