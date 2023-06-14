#include "dgemm_opt.hpp"
#ifdef WITH_SSE
#include "immintrin.h"
#endif
#define A(i, j) A[(i) + (j)*LDA]
#define B(i, j) B[(i) + (j)*LDB]
#define C(i, j) C[(i) + (j)*LDC]

void scalar_times_matrix(double *C, int M, int N, int LDC, double scalar)
{
    int i, j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            C(i, j) *= scalar;
        }
    }
}

void naive_dgemm(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    if (beta != 1.0)
        scalar_times_matrix(C, M, N, LDC, beta);
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < K; k++)
            {
                C(i, j) += alpha * A(i, k) * B(k, j);
            }
        }
    }
}

void register_blocking_2x2_dgemm_inner(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            double tmp = C(i, j);
            for (k = 0; k < K; k++)
            {
                tmp += alpha * A(i, k) * B(k, j);
            }
            C(i, j) = tmp;
        }
    }
}

void register_blocking_2x2_dgemm(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    if (beta != 1.0)
        scalar_times_matrix(C, M, N, LDC, beta);
    int M2 = M & -2, N2 = N & -2;
    for (i = 0; i < M2; i += 2)
    {
        for (j = 0; j < N2; j += 2)
        {
            double c00 = C(i, j);
            double c01 = C(i, j + 1);
            double c10 = C(i + 1, j);
            double c11 = C(i + 1, j + 1);
            for (k = 0; k < K; k++)
            {
                double a0 = alpha * A(i, k);
                double a1 = alpha * A(i + 1, k);
                double b0 = B(k, j);
                double b1 = B(k, j + 1);
                c00 += a0 * b0;
                c01 += a0 * b1;
                c10 += a1 * b0;
                c11 += a1 * b1;
            }
            C(i, j) = c00;
            C(i, j + 1) = c01;
            C(i + 1, j) = c10;
            C(i + 1, j + 1) = c11;
        }
    }
    if (M2 == M && N2 == N)
        return;
    // boundary conditions
    if (M2 != M)
        register_blocking_2x2_dgemm_inner(M - M2, N, K, alpha, A + M2, LDA, B, LDB, 1.0, &C(M2, 0), LDC);
    if (N2 != N)
        register_blocking_2x2_dgemm_inner(M2, N - N2, K, alpha, A, LDA, &B(0, N2), LDB, 1.0, &C(0, N2), LDC);
}
void register_blocking_4x4_dgemm_inner(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            double tmp = C(i, j);
            for (k = 0; k < K; k++)
            {
                tmp += alpha * A(i, k) * B(k, j);
            }
            C(i, j) = tmp;
        }
    }
}

void register_blocking_4x4_dgemm(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    if (beta != 1.0)
        scalar_times_matrix(C, M, N, LDC, beta);
    int M4 = M & -4, N4 = N & -4;
    for (i = 0; i < M4; i += 4)
    {
        for (j = 0; j < N4; j += 4)
        {
            double c00 = C(i, j);
            double c01 = C(i, j + 1);
            double c02 = C(i, j + 2);
            double c03 = C(i, j + 3);
            double c10 = C(i + 1, j);
            double c11 = C(i + 1, j + 1);
            double c12 = C(i + 1, j + 2);
            double c13 = C(i + 1, j + 3);
            double c20 = C(i + 2, j);
            double c21 = C(i + 2, j + 1);
            double c22 = C(i + 2, j + 2);
            double c23 = C(i + 2, j + 3);
            double c30 = C(i + 3, j);
            double c31 = C(i + 3, j + 1);
            double c32 = C(i + 3, j + 2);
            double c33 = C(i + 3, j + 3);
            for (k = 0; k < K; k++)
            {
                double a0 = alpha * A(i, k);
                double a1 = alpha * A(i + 1, k);
                double a2 = alpha * A(i + 2, k);
                double a3 = alpha * A(i + 3, k);
                double b0 = B(k, j);
                double b1 = B(k, j + 1);
                double b2 = B(k, j + 2);
                double b3 = B(k, j + 3);
                c00 += a0 * b0;
                c01 += a0 * b1;
                c02 += a0 * b2;
                c03 += a0 * b3;
                c10 += a1 * b0;
                c11 += a1 * b1;
                c12 += a1 * b2;
                c13 += a1 * b3;
                c20 += a2 * b0;
                c21 += a2 * b1;
                c22 += a2 * b2;
                c23 += a2 * b3;
                c30 += a3 * b0;
                c31 += a3 * b1;
                c32 += a3 * b2;
                c33 += a3 * b3;
            }
            C(i, j) = c00;
            C(i, j + 1) = c01;
            C(i, j + 2) = c02;
            C(i, j + 3) = c03;
            C(i + 1, j) = c10;
            C(i + 1, j + 1) = c11;
            C(i + 1, j + 2) = c12;
            C(i + 1, j + 3) = c13;
            C(i + 2, j) = c20;
            C(i + 2, j + 1) = c21;
            C(i + 2, j + 2) = c22;
            C(i + 2, j + 3) = c23;
            C(i + 3, j) = c30;
            C(i + 3, j + 1) = c31;
            C(i + 3, j + 2) = c32;
            C(i + 3, j + 3) = c33;
        }
    }
    if (M4 == M && N4 == N)
        return;
    // boundary conditions
    if (M4 != M)
        register_blocking_4x4_dgemm_inner(M - M4, N, K, alpha, A + M4, LDA, B, LDB, 1.0, &C(M4, 0), LDC);
    if (N4 != N)
        register_blocking_4x4_dgemm_inner(M4, N - N4, K, alpha, A, LDA, &B(0, N4), LDB, 1.0, &C(0, N4), LDC);
}
#ifdef WITH_SSE
void register_blocking_4x4_SSE_dgemm_inner(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            double tmp = C(i, j);
            for (k = 0; k < K; k++)
            {
                tmp += alpha * A(i, k) * B(k, j);
            }
            C(i, j) = tmp;
        }
    }
}

void register_blocking_4x4_SSE_dgemm(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC)
{
    int i, j, k;
    if (beta != 1.0)
        scalar_times_matrix(C, M, N, LDC, beta);
    int M4 = M & -4, N4 = N & -4;
    __m128d valpha = _mm_set1_pd(alpha); // broadcast alpha to a 128-bit vector
    for (i = 0; i < M4; i += 4)
    {
        for (j = 0; j < N4; j += 4)
        {
            __m128d c0 = _mm_setzero_pd();
            __m128d c1 = _mm_setzero_pd();
            __m128d c2 = _mm_setzero_pd();
            __m128d c3 = _mm_setzero_pd();
            for (k = 0; k < K; k++)
            {
                __m128d a = _mm_mul_pd(valpha, _mm_loadu_pd(&A(i, k)));
                __m128d b0 = _mm_load1_pd(&B(k, j));
                __m128d b1 = _mm_load1_pd(&B(k, j + 1));
                __m128d b2 = _mm_load1_pd(&B(k, j + 2));
                __m128d b3 = _mm_load1_pd(&B(k, j + 3));
                c0 = _mm_add_pd(_mm_mul_pd(a, b0), c0);
                c1 = _mm_add_pd(_mm_mul_pd(a, b1), c1);
                c2 = _mm_add_pd(_mm_mul_pd(a, b2), c2);
                c3 = _mm_add_pd(_mm_mul_pd(a, b3), c3);
            }
            _mm_storeu_pd(&C(i, j), _mm_add_pd(c0, _mm_loadu_pd(&C(i, j))));
            _mm_storeu_pd(&C(i, j + 1), _mm_add_pd(c1, _mm_loadu_pd(&C(i, j + 1))));
            _mm_storeu_pd(&C(i, j + 2), _mm_add_pd(c2, _mm_loadu_pd(&C(i, j + 2))));
            _mm_storeu_pd(&C(i, j + 3), _mm_add_pd(c3, _mm_loadu_pd(&C(i, j + 3))));
        }
    }
    if (M4 == M && N4 == N)
        return;
    // boundary conditions
    if (M4 != M)
        register_blocking_4x4_SSE_dgemm_inner(M - M4, N, K, alpha, A + M4, LDA, B, LDB, 1.0, &C(M4, 0), LDC);
    if (N4 != N)
        register_blocking_4x4_SSE_dgemm_inner(M4, N - N4, K, alpha, A, LDA, &B(0, N4), LDB, 1.0, &C(0, N4), LDC);
}
#endif