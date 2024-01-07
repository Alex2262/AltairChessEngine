//
// Created by Alexander Tian on 1/6/24.
//

#ifndef ALTAIRCHESSENGINE_SIMD_H
#define ALTAIRCHESSENGINE_SIMD_H

#include <cstdint>
#include <string>

enum class SIMDArch {
    AVX2,
    AVX512,
    NEON,
    AUTO
};

#if defined(__AVX2__)
#include <immintrin.h>
constexpr SIMDArch SIMD_ARCH = SIMDArch::AVX2;
constexpr size_t REGISTER_SIZE = 8;

#elif defined(__ARM_NEON)
#include <arm_neon.h>
constexpr SIMDArch SIMD_ARCH = SIMDArch::NEON;
constexpr size_t REGISTER_SIZE = 4;

#else
constexpr SIMDArch SIMD_ARCH = SIMDArch::AUTO;
constexpr size_t REGISTER_SIZE = 0;

#endif

#endif //ALTAIRCHESSENGINE_SIMD_H
