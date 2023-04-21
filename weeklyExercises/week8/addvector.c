#include <stdlib.h>
#include <cstdio>
#include "addvector.h"

#ifdef WITH_AVX2
#include <immintrin.h>
#endif

#ifdef WITH_NEON
#include <arm_neon.h>
#endif

#ifdef _OPENMP
#include <omp.h>
#endif

void addvector(const float *p1, const float *p2, float *result, size_t n)
{

    for (size_t i = 0; i < n; i++)
        result[i] = p1[i] + p2[i];
}

void addvector_avx2(const float *p1, const float *p2, float *result, size_t n)
{
#ifdef WITH_AVX2
    if (n % 8 != 0)
    {
        printf("not multiply of 8!\n");
        return;
    }

    float sum[8] = {0};
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();

    for (size_t i = 0; i < n; i += 8)
    {
        a = _mm256_loadu_ps(p1 + i);
        b = _mm256_loadu_ps(p2 + i);
        c = _mm256_add_ps(a, b);
        _mm256_storeu_ps(result + i, c);
    }

#else
    printf("AVX2 is not supported\n");

#endif
}
void addvector_neon(const float *p1, const float *p2, float *result, size_t n)
{
#ifdef WITH_NEON
    if (n % 4 != 0)
    {
        std::cerr << "The size n must be a multiple of 4." << std::endl;
        return 0.0f;
    }

    float32x4_t a, b;
    float32x4_t c = vdupq_n_f32(0);

    for (size_t i = 0; i < n; i += 4)
    {
        a = vld1q_f32(p1 + i);
        b = vld1q_f32(p2 + i);
        c = vaddq_f32(c, vmulq_f32(a, b));
        vst1q_f32(result + i, c);
    }

#else
    printf("NEON is not supported\n");

#endif
}

void addvector_avx2_omp(const float *p1, const float *p2, float *result, size_t n)
{
#ifdef WITH_AVX2
    if (n % 8 != 0)
    {
        printf("not multiply of 8!\n");
        return;
    }

    
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();

#pragma omp parallel for
    for (size_t i = 0; i < n; i += 8)
    {
        a = _mm256_load_ps(p1 + i);
        b = _mm256_load_ps(p2 + i);
        c = _mm256_add_ps(a, b);
    _mm256_store_ps(result+i, c);

    }

#else
    printf("AVX2 is not supported\n");

#endif
}
void addvector_neon_omp(const float *p1, const float *p2, float *result, size_t n)
{
#ifdef WITH_NEON
    if (n % 4 != 0)
    {
        printf("not multiply of 8!\n");
        return;
    }


    float32x4_t a, b;
    float32x4_t c = vdupq_n_f32(0);

#pragma omp parallel for
    for (size_t i = 0; i < n; i += 4)
    {
        a = vld1q_f32(p1 + i);
        b = vld1q_f32(p2 + i);
        c = vaddq_f32(a, b);
        vst1q_f32(result + i, c);
    }

#else
    printf("NEON is not supported\n");

#endif
}