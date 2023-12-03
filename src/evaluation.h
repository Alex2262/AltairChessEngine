

#ifndef ALTAIR_EVALUATION_H
#define ALTAIR_EVALUATION_H

#include "position.h"
#include "constants.h"
#include "types.h"

struct EvaluationInformation {
    int game_phase = 0;

    int passed_pawn_count[2]{};

    int piece_counts[2][6]{};

    int total_king_ring_attacks[2]{};

    Square king_squares[2]{};

    BITBOARD pawns[2]{};
    BITBOARD pieces[2]{};
    BITBOARD pawn_attacks[2]{};

    BITBOARD piece_relative_occupancies[2][6]{};
};

void initialize_evaluation_information(Position& position, EvaluationInformation& evaluation_information);

Square get_white_relative_square(Square square, Color color);
Square get_black_relative_square(Square square, Color color);


SCORE_TYPE evaluate_king_pawn(File file, Color color, EvaluationInformation& evaluation_information);

SCORE_TYPE evaluate_piece(Position& position, PieceType piece_type, Color color, int& game_phase);
SCORE_TYPE evaluate_pieces(Position& position, int& game_phase);

double evaluate_drawishness(Position& position, EvaluationInformation& evaluation_information);
double evaluate_opposite_colored_bishop_endgames(Position& position, EvaluationInformation& evaluation_information);

SCORE_TYPE evaluate_classic(Position& position);


constexpr SCORE_TYPE S(int mg, int eg) {
    return static_cast<SCORE_TYPE>(static_cast<unsigned int>(eg) << 16) + mg;
}

inline int eg_score(SCORE_TYPE s) {
    const auto eg = static_cast<uint16_t>(static_cast<uint32_t>(s + 0x8000) >> 16);

    int16_t v;
    std::memcpy(&v, &eg, sizeof(eg));

    return static_cast<int>(v);
}

inline int mg_score(SCORE_TYPE s) {
    const auto mg = static_cast<uint16_t>(s);

    int16_t v;
    std::memcpy(&v, &mg, sizeof(mg));

    return static_cast<int>(v);
}

inline int get_manhattan_distance(Square square_1, Square square_2) {
    return abs(static_cast<int>(rank_of(square_1)) - static_cast<int>(rank_of(square_2))) +
           abs(static_cast<int>(file_of(square_1)) - static_cast<int>(file_of(square_2)));
}

inline int get_chebyshev_distance(Square square_1, Square square_2) {
    return std::max(abs(static_cast<int>(rank_of(square_1)) - static_cast<int>(rank_of(square_2))),
                    abs(static_cast<int>(file_of(square_1)) - static_cast<int>(file_of(square_2))));
}

inline bool same_color (Square square_1, Square square_2) {
    return (( 9 * (square_1 ^ square_2)) & 8) == 0;
}

template<int n>
struct KingRing {
    constexpr KingRing() : masks() {
        for (int rings = 1; rings <= n; rings++) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    masks[rings-1][i * 8 + j] = 0ULL;
                    for (int y = i - rings; y <= i + rings; y++){
                        for (int x = j - rings; x <= j + rings; x++) {
                            if (y < 0 || y >= 8 || x < 0 || x >= 8) continue;
                            if (y == i - rings || y == i + rings || x == j - rings || x == j + rings) {
                                masks[rings-1][i * 8 + j] |= 1ULL << (y * 8 + x);
                            }
                        }
                    }
                    //std::cout << i * 8 + j << " " << masks[rings-1][i * 8 + j] << std::endl;
                }
            }
        }
    }

    uint64_t masks[n][64]{};
};

constexpr KingRing king_ring_zone = KingRing<2>();

#endif //ALTAIR_EVALUATION_H
