#pragma once

#include <cstdint>
#include <string>

namespace SIMD {

    enum class Arch {
        AVX2,
        AVX512,
        NEON,
        AUTO
    };

#if defined(__AVX512F__) && defined(__AVX512BW__)
    #include <immintrin.h>
    constexpr Arch ARCH = Arch::AVX512;
    constexpr size_t REGISTER_SIZE = 32;  // 32 x 16-bit integers

#elif defined(__AVX2__)
    #include <immintrin.h>
    constexpr Arch ARCH = Arch::AVX2;
    constexpr size_t REGISTER_SIZE = 16;

#elif defined(__ARM_NEON)
#include <arm_neon.h>
    constexpr Arch ARCH = Arch::NEON;
    constexpr size_t REGISTER_SIZE = 8;

#else
    constexpr Arch ARCH = Arch::AUTO;
    constexpr size_t REGISTER_SIZE = 0;

#endif

    auto inline int16_load(auto data) {

#if defined(__AVX512F__) && defined(__AVX512BW__)
        return _mm512_loadu_si512(reinterpret_cast<const __m512i*>(data));
#elif defined(__AVX2__)
        return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data));
#elif defined(__ARM_NEON)
        return vld1q_s16(data);
#else
        return 0;
#endif

    }

    auto inline get_int16_vec(auto data) {

#if defined(__AVX512F__) && defined(__AVX512BW__)
        return _mm512_set1_epi16(data);
#elif defined(__AVX2__)
        return _mm256_set1_epi16(data);
#elif defined(__ARM_NEON)
        return vdupq_n_s16(data);
#else
        return 0;
#endif

    }

    auto inline vec_int16_clamp(auto vec, auto min_vec, auto max_vec) {

#if defined(__AVX512F__) && defined(__AVX512BW__)
        vec = _mm512_max_epi16(vec, min_vec);
        vec = _mm512_min_epi16(vec, max_vec);
        return vec;
#elif defined(__AVX2__)
        vec = _mm256_max_epi16(vec, min_vec);
        vec = _mm256_min_epi16(vec, max_vec);
        return vec;
#elif defined(__ARM_NEON)
        vec = vmaxq_s16(vec, min_vec);
        vec = vminq_s16(vec, max_vec);
        return vec;
#else
        return 0;
#endif

    }

    auto inline vec_int16_multiply(auto vec1, auto vec2) {

#if defined(__AVX512F__) && defined(__AVX512BW__)
        return _mm512_mullo_epi16(vec1, vec2);
#elif defined(__AVX2__)
        return _mm256_mullo_epi16(vec1, vec2);
#elif defined(__ARM_NEON)
        return vmulq_s16(vec1, vec2);
#else
        return 0;
#endif

    }

    auto inline vec_int32_zero() {

#if defined(__AVX512F__)
        return _mm512_setzero_si512();
#elif defined(__AVX2__)
        return _mm256_setzero_si256();
#elif defined(__ARM_NEON)
        return vdupq_n_s32(0);
#else
        return 0;
#endif
    }

    auto inline vec_int32_add(auto vec1, auto vec2) {

#if defined(__AVX512F__)
        return _mm512_add_epi32(vec1, vec2);
#elif defined(__AVX2__)
        return _mm256_add_epi32(vec1, vec2);
#elif defined(__ARM_NEON)
        return vaddq_s32(vec1, vec2);
#else
        return 0;
#endif
    }

    auto inline vec_int16_madd_int32(auto vec1, auto vec2) {

#if defined(__AVX512F__) && defined(__AVX512BW__)
        return _mm512_madd_epi16(vec1, vec2);
#elif defined(__AVX2__)
        return _mm256_madd_epi16(vec1, vec2);
#elif defined(__ARM_NEON)
        int32x4_t low_product  = vmull_s16(vget_low_s16 (vec1), vget_low_s16 (vec2));
        int32x4_t high_product = vmull_high_s16(vec1, vec2);

        return vpaddq_s32(low_product, high_product);
#else
        return 0;
#endif

    }

    auto inline vec_int32_hadd(auto vec) {

#if defined(__AVX512F__)
        // AVX512 horizontal add reduction
        return _mm512_reduce_add_epi32(vec);
#elif defined(__AVX2__)
        auto sum_into_4 = _mm256_hadd_epi32(vec, vec);
        auto sum_into_2 = _mm256_hadd_epi32(sum_into_4, sum_into_4);

        auto lane_1 = _mm256_castsi256_si128(sum_into_2);
        auto lane_2 = _mm256_extractf128_si256(sum_into_2, 1);
        auto result = _mm_add_epi32(lane_1, lane_2);
        auto rel    = _mm_extract_epi32(result, 0);

        return rel;
#elif defined(__ARM_NEON)
        return vaddvq_s32(vec);
#else
        return 0;
#endif
    }
}