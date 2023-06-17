//
// Created by Alexander Tian on 6/16/23.
//

#include "nnue.h"
#include "incbin.h"

INCBIN(nnue, "gemstone.nnue");
const NNUE_Params &g_nnue = *reinterpret_cast<const NNUE_Params *>(gnnueData);

void NNUE_State::push()
{
    m_accumulator_stack.push_back(*m_curr);
    m_curr = &m_accumulator_stack.back();
}

void NNUE_State::pop()
{
    m_accumulator_stack.pop_back();
    m_curr = &m_accumulator_stack.back();
}


SCORE_TYPE NNUE_State::evaluate(int color) const
{
    const auto output = color == WHITE_COLOR
                        ? screlu_flatten(m_curr->white, m_curr->black, g_nnue.output_weights)
                        : screlu_flatten(m_curr->black, m_curr->white, g_nnue.output_weights);
    return (output + g_nnue.output_bias) * SCALE / QAB;
}


std::pair<size_t , size_t> NNUE_State::feature_indices(PIECE_TYPE piece, SQUARE_TYPE sq)
{
    constexpr size_t color_stride = 64 * 6;
    constexpr size_t piece_stride = 64;

    const auto base = static_cast<PIECE_TYPE>(piece % BLACK_PAWN);
    const size_t color = piece >= BLACK_PAWN;

    // std::cout << piece << " " << sq << " " << base << " " << color << std::endl;
    const auto whiteIdx =  color * color_stride + base * piece_stride +  static_cast<size_t>(sq ^ 56);
    const auto blackIdx =  (color ^ 1) * color_stride + base * piece_stride + (static_cast<size_t>(sq));

    // std::cout << whiteIdx << " " << blackIdx << std::endl;
    return {whiteIdx, blackIdx};
}

int32_t NNUE_State::screlu_flatten(const std::array<int16_t, LAYER1_SIZE> &us,
                                     const std::array<int16_t, LAYER1_SIZE> &them, const std::array<int16_t, LAYER1_SIZE * 2> &weights)
{
    int32_t sum = 0;

    for (size_t i = 0; i < LAYER1_SIZE; ++i)
    {
        sum += screlu(  us[i]) * weights[              i];
        sum += screlu(them[i]) * weights[LAYER1_SIZE + i];
    }

    return sum / QA;
}