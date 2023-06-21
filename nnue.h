//
// Created by Alexander Tian on 6/16/23.
//

#ifndef ALTAIRCHESSENGINE_NNUE_H
#define ALTAIRCHESSENGINE_NNUE_H

#include <cstring>
#include <array>
#include <span>
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

extern const NNUE_Params &g_nnue;

template <size_t HiddenSize>
struct alignas(64) Accumulator
{
    std::array<int16_t, HiddenSize> white;
    std::array<int16_t, HiddenSize> black;

    inline void init(std::span<const int16_t, HiddenSize> bias)
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
    explicit NNUE_State()
    {
        m_accumulator_stack.reserve(TOTAL_MAX_DEPTH);
    }

    ~NNUE_State() = default;

    void push();

    void pop();

    template <bool Activate>
    inline void update_feature(PIECE_TYPE piece, SQUARE_TYPE square) {
        const auto [white_idx, black_idx] = feature_indices(piece, square);

        if constexpr (Activate)
        {
            add_to_all(m_curr->white, g_nnue.feature_weights, white_idx * LAYER1_SIZE);
            add_to_all(m_curr->black, g_nnue.feature_weights, black_idx * LAYER1_SIZE);
        }
        else
        {
            subtract_from_all(m_curr->white, g_nnue.feature_weights, white_idx * LAYER1_SIZE);
            subtract_from_all(m_curr->black, g_nnue.feature_weights, black_idx * LAYER1_SIZE);
        }
    }

    [[nodiscard]] SCORE_TYPE evaluate(int color) const;

    std::vector<Accumulator<LAYER1_SIZE>> m_accumulator_stack{};
    Accumulator<LAYER1_SIZE> *m_curr{};

    template <size_t size, size_t weights>
    inline void add_to_all(std::array<int16_t, size> &input, const std::array<int16_t, weights> &delta, size_t offset)
    {
        for (size_t i = 0; i < size; ++i)
        {
            input[i] += delta[offset + i];
        }
    }

    template <size_t size, size_t weights>
    inline void subtract_from_all(std::array<int16_t, size> &input, const std::array<int16_t, weights> &delta, size_t offset)
    {
        for (size_t i = 0; i < size; ++i)
        {
            input[i] -= delta[offset + i];
        }
    }

    static std::pair<size_t , size_t> feature_indices(PIECE_TYPE piece, SQUARE_TYPE sq);

    static int32_t screlu_flatten(const std::array<int16_t, LAYER1_SIZE> &us,
                                         const std::array<int16_t, LAYER1_SIZE> &them,
                                         const std::array<int16_t, LAYER1_SIZE * 2> &weights);

    void reset_nnue(Position& position);
};
#endif //ALTAIRCHESSENGINE_NNUE_H
