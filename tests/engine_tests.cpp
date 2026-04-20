#include "../src/constants.h"
#include "../src/move_ordering.h"
#include "../src/perft.h"
#include "test_common.h"

#include <string>
#include <vector>

namespace {

    Move move_from_uci(const Position& position, const std::string& uci_text) {
        std::string uci = uci_text;
        return Move(position, uci);
    }

    void test_max_heap_orders_scores() {
        FixedVector<ScoredMove, MAX_MOVES> scored_moves;

        Position position;
        position.set_fen(std::string(START_FEN));

        scored_moves.push_back({move_from_uci(position, "a2a4"), -1000});
        scored_moves.push_back({move_from_uci(position, "b2b4"), 1000});
        scored_moves.push_back({move_from_uci(position, "c2c4"), 2000});
        scored_moves.push_back({move_from_uci(position, "d2d4"), -3000});
        scored_moves.push_back({move_from_uci(position, "e2e4"), 5000});
        scored_moves.push_back({move_from_uci(position, "f2f4"), -1000});
        scored_moves.push_back({move_from_uci(position, "g2g4"), -5000});
        scored_moves.push_back({move_from_uci(position, "h2h4"), -6000});
        scored_moves.push_back({move_from_uci(position, "g1f3"), 8000});
        scored_moves.push_back({move_from_uci(position, "b1c3"), 7000});

        FixedVector<ScoredMove, MAX_MOVES> heap_data = scored_moves;
        MaxHeap max_heap{};
        max_heap.heapify(heap_data, 0);

        const std::vector<Move> expected = {
            scored_moves[8].move, scored_moves[9].move, scored_moves[4].move, scored_moves[2].move, scored_moves[1].move,
            scored_moves[0].move, scored_moves[5].move, scored_moves[3].move, scored_moves[6].move, scored_moves[7].move
        };

        for (size_t i = 0; i < expected.size(); ++i) {
            const ScoredMove extracted = max_heap.extract(heap_data);
            expect(extracted.move == expected[i], "MaxHeap extracted moves in the wrong order");
        }
    }

void test_position_fen_round_trip() {
    Position position;
    const FenInfo fen_info = position.set_fen(std::string(START_FEN));

        expect(fen_info.fifty_move_counter == 0, "Start position should default the fifty-move counter to 0");
        expect(fen_info.full_move_counter == 1, "Start position should default the full-move counter to 1");
        expect(position.get_fen(fen_info.fifty_move_counter) == std::string(START_FEN) + "0",
               "Position::get_fen should round-trip the standard start position");

        const std::string complex_fen = "r3k2r/pppq1ppp/2npbn2/3Np3/2P1P3/2N1B3/PP3PPP/R2QKB1R b KQkq c3 7 12";
    const FenInfo complex_info = position.set_fen(complex_fen);

    expect(complex_info.fifty_move_counter == 7, "Complex FEN should parse the half-move clock");
    expect(complex_info.full_move_counter == 12, "Complex FEN should parse the full-move counter");
    expect(position.get_fen(complex_info.fifty_move_counter) == "r3k2r/pppq1ppp/2npbn2/3Np3/2P1P3/2N1B3/PP3PPP/R2QKB1R b KQkq c3 7",
           "Position::get_fen should preserve board, side, castling, EP, and half-move state");

    const std::string trailing_empty_fen = "rnbqk2r/ppp1ppbp/3p1np1/8/2P5/2NP2PN/PP2PPBP/R1BQ1RK1 b kq - 4 1";
    position.set_fen(trailing_empty_fen);
    expect(position.get_fen(4) == "rnbqk2r/ppp1ppbp/3p1np1/8/2P5/2NP2PN/PP2PPBP/R1BQ1RK1 b kq - 4",
           "Position::get_fen should keep trailing empty squares on the last rank");
}

    void test_start_position_perft() {
        Position position;
        position.set_fen(std::string(START_FEN));

        Perft perft;
        expect(fast_perft(perft, position, 2, 0) == 400, "Start position perft depth 2 should be 400");
        expect(fast_perft(perft, position, 6, 0) == 119060324, "Start position perft depth 6 should be 119060324");
    }

    void test_perft_exhaustive() {
        Perft perft;
        Position position;

        position.set_fen(std::string("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "));
        expect(fast_perft(perft, position, 5, 0) == 193690690, "kiwipete depth 5 incorrect");

        position.set_fen(std::string("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1"));
        expect(fast_perft(perft, position, 7, 0) == 178633661, "perft failed");

        position.set_fen(std::string("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"));
        expect(fast_perft(perft, position, 5, 0) == 15833292, "perft failed");

        position.set_fen(std::string("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1"));
        expect(fast_perft(perft, position, 5, 0) == 15833292, "perft failed");

        position.set_fen(std::string("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"));
        expect(fast_perft(perft, position, 5, 0) == 89941194, "perft failed");

        position.set_fen(std::string("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"));
        expect(fast_perft(perft, position, 5, 0) == 164075551, "perft failed");
    }


    void test_perft_960_exhaustive() {
        Perft perft;
        Position position;
        position.fischer_random_chess = true;

        position.set_fen(std::string("bqnb1rkr/pp3ppp/3ppn2/2p5/5P2/P2P4/NPP1P1PP/BQ1BNRKR w HFhf - 2 9")); // 0
        expect(fast_perft(perft, position, 6, 0) == 227689589, "perft failed");

        position.set_fen(std::string("qnbnr1kr/ppp1b1pp/4p3/3p1p2/8/2NPP3/PPP1BPPP/QNB1R1KR w HEhe - 1 9")); // 6
        expect(fast_perft(perft, position, 5, 0) == 24851983, "perft failed");

        position.set_fen(std::string("qn1rbbkr/ppp2p1p/1n1pp1p1/8/3P4/P6P/1PP1PPPK/QNNRBB1R w hd - 2 9")); // 10
        expect(fast_perft(perft, position, 5, 0) == 19836606, "perft failed");

        position.set_fen(std::string("rknqbbr1/p1pp1pp1/1p4n1/4p2p/4P1P1/6RB/PPPP1P1P/RKNQB2N w Aga - 0 9")); // 826
        expect(fast_perft(perft, position, 6, 0) == 507563675, "perft failed");
    }

}  // namespace

int main() {
    try {
        run_test("MaxHeap orders moves by score", test_max_heap_orders_scores);
        run_test("Position FEN round-trips important state", test_position_fen_round_trip);
        run_test("Start position perft sanity", test_start_position_perft);
        run_test("test perft", test_perft_exhaustive);
        run_test("test perft 960", test_perft_960_exhaustive);
        std::cout << "engine_tests: ok\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "engine_tests: failed: " << ex.what() << "\n";
        return 1;
    }
}
