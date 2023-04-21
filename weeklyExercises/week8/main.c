#include <stdlib.h>
#include <chrono>
#include <stddef.h>
#include <cstdlib>
#include <cstdio>
#include "addvector.h"

#define TIME_START start = std::chrono::steady_clock::now();
#define TIME_END(NAME)                                                                     \
    end = std::chrono::steady_clock::now();                                                \
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
    printf("%s  duration = %ld ms\n", (NAME), duration);

int main(int argc, char const *argv[])
{
    size_t nSize = 200000000;
    // float * p1 = new float[nSize](); //the memory is not aligned
    // float * p2 = new float[nSize](); //the memory is not aligned

    // 256bits aligned, C++17 standard
    float *p1 = static_cast<float *>(aligned_alloc(256, nSize * sizeof(float)));
    float *p2 = static_cast<float *>(aligned_alloc(256, nSize * sizeof(float)));
    float *result = static_cast<float *>(aligned_alloc(256, nSize * sizeof(float)));

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto duration = 0L;

    p1[2] = 2.3f;
    p2[2] = 3.0f;
    p1[nSize - 1] = 2.0f;
    p2[nSize - 1] = 1.1f;

    addvector(p1, p2, result, nSize);
    // addvector(p1, p2,result, nSize);

    TIME_START
    addvector(p1, p2, result, nSize);
    TIME_END("normal")

    TIME_START
    addvector_neon(p1, p2, result, nSize);
    TIME_END("SIMD+neon")

    TIME_START
    addvector_avx2(p1, p2, result, nSize);
    TIME_END("SIMD+avx2")

    TIME_START
    addvector_avx2_omp(p1, p2, result, nSize);
    TIME_END("SIMD+OpenMP+avx2")

    TIME_START
    addvector_neon_omp(p1, p2, result, nSize);
    TIME_END("SIMD+OpenMP+neon")
    return 0;
}
