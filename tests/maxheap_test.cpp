#include "../src/move_ordering.h"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Running MaxHeap basic test...\n";

    FixedVector<ScoredMove, MAX_MOVES> scored_moves;

    Position position;
    position.set_fen(START_FEN);

    // Add moves with scores
    scored_moves.push_back({Move(position, "a2a4"), -1000});
    scored_moves.push_back({Move(position, "b2b4"), 1000});
    scored_moves.push_back({Move(position, "c2c4"), 2000});
    scored_moves.push_back({Move(position, "d2d4"), -3000});
    scored_moves.push_back({Move(position, "e2e4"), 5000});
    scored_moves.push_back({Move(position, "f2f4"), -1000});
    scored_moves.push_back({Move(position, "g2g4"), -5000});
    scored_moves.push_back({Move(position, "h2h4"), -6000});
    scored_moves.push_back({Move(position, "g1f3"), 8000});
    scored_moves.push_back({Move(position, "b1c3"), 7000});

    std::cout << "Created " << scored_moves.size() << " moves\n";

    FixedVector<ScoredMove, MAX_MOVES> copy = scored_moves;

    MaxHeap max_heap{};
    max_heap.heapify(copy, 0);

    std::cout << "Heapified\n";

    // Extract all moves
    std::vector<ScoredMove> out;
    for (int i = 0; i < 10; i++) {
        ScoredMove scored_move = max_heap.extract(copy);
        out.push_back(scored_move);
        std::cout << "Extracted move " << i << ": score = " << scored_move.score << "\n";
    }

    std::cout << "Extracted all moves\n";

    // Verify ordering (highest to lowest)
    assert(out[0].move == scored_moves[8].move && "Expected g1f3 (8000)");
    assert(out[1].move == scored_moves[9].move && "Expected b1c3 (7000)");
    assert(out[2].move == scored_moves[4].move && "Expected e2e4 (5000)");
    assert(out[3].move == scored_moves[2].move && "Expected c2c4 (2000)");
    assert(out[4].move == scored_moves[1].move && "Expected b2b4 (1000)");
    assert(out[5].move == scored_moves[0].move && "Expected a2a4 (-1000)");
    assert(out[6].move == scored_moves[5].move && "Expected f2f4 (-1000)");
    assert(out[7].move == scored_moves[3].move && "Expected d2d4 (-3000)");
    assert(out[8].move == scored_moves[6].move && "Expected g2g4 (-5000)");
    assert(out[9].move == scored_moves[7].move && "Expected h2h4 (-6000)");

    std::cout << "All assertions passed!\n";
    std::cout << "Test completed successfully.\n";

    return 0;
}