//
// Created by Alexander Tian on 6/16/23.
//

#ifndef ALTAIR_NNUE_H
#define ALTAIR_NNUE_H

#include <cstring>
#include <array>
#include <span>
#include <vector>
#include <algorithm>
#include "constants.h"

class Position;

constexpr size_t INPUT_SIZE = 768;
constexpr size_t LAYER1_SIZE = 768;

constexpr SCORE_TYPE CRELU_MIN = 0;
constexpr SCORE_TYPE CRELU_MAX = 255;

constexpr SCORE_TYPE SCALE = 400;

constexpr SCORE_TYPE QA = 255;
constexpr SCORE_TYPE QB = 64;

constexpr SCORE_TYPE QAB = QA * QB;

struct alignas(64) NNUE_Params {
    std::array<int16_t, INPUT_SIZE * LAYER1_SIZE> feature_weights;
    std::array<int16_t, LAYER1_SIZE> feature_bias;
    std::array<int16_t, LAYER1_SIZE * 2> output_weights;
    int16_t output_bias;
};

extern const NNUE_Params &nnue_parameters;

template <size_t hidden_size>
struct alignas(64) Accumulator
{
    std::array<int16_t, hidden_size> white;
    std::array<int16_t, hidden_size> black;

    inline void init(std::span<const int16_t, hidden_size> bias)
    {
        std::memcpy(white.data(), bias.data(), bias.size_bytes());
        std::memcpy(black.data(), bias.data(), bias.size_bytes());
    }
};

constexpr int32_t screlu(int16_t x)
{
    const auto clipped = std::clamp(static_cast<int32_t>(x), CRELU_MIN, CRELU_MAX);
    return clipped * clipped;
}

class NNUE_State {
public:
    explicit NNUE_State() {
        accumulator_stack.reserve(TOTAL_MAX_DEPTH);
    }

    ~NNUE_State() = default;

    std::vector<Accumulator<LAYER1_SIZE>> accumulator_stack{};
    Accumulator<LAYER1_SIZE> *current_accumulator{};

    void push();
    void pop();

    SCORE_TYPE evaluate(Color color) const;

    static std::pair<size_t, size_t> get_feature_indices(Piece piece, Square sq);

    static int32_t screlu_flatten(const std::array<int16_t, LAYER1_SIZE> &our,
                                  const std::array<int16_t, LAYER1_SIZE> &opp,
                                  const std::array<int16_t, LAYER1_SIZE * 2> &weights);

    void reset_nnue(Position& position);

    template <bool Activate>
    inline void update_feature(Piece piece, Square square) {
        const auto [white_idx, black_idx] = get_feature_indices(piece, square);

        if constexpr (Activate)
        {
            activate_all(current_accumulator->white, white_idx * LAYER1_SIZE);
            activate_all(current_accumulator->black, black_idx * LAYER1_SIZE);
        }
        else
        {
            deactivate_all(current_accumulator->white, white_idx * LAYER1_SIZE);
            deactivate_all(current_accumulator->black, black_idx * LAYER1_SIZE);
        }
    }

    static inline void activate_all(std::array<int16_t, LAYER1_SIZE>& input, size_t offset) {
        for (size_t i = 0; i < LAYER1_SIZE; ++i) input[i] += nnue_parameters.feature_weights[offset + i];
    }

    static inline void deactivate_all(std::array<int16_t, LAYER1_SIZE>& input, size_t offset) {
        for (size_t i = 0; i < LAYER1_SIZE; ++i) input[i] -= nnue_parameters.feature_weights[offset + i];
    }
};
#endif //ALTAIR_NNUE_H