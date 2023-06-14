#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <stdint.h>

#define A(i,j) A[(i)+(j)*LDA]
#define B(i,j) B[(i)+(j)*LDB]
#define C(i,j) C[(i)+(j)*LDC]
#define M_BLOCKING 192
#define N_BLOCKING 9216
#define K_BLOCKING 384
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

#include <omp.h>

void scale_c_k19(double *C, int M, int N, int LDC, double scalar) {
    int m_count, n_count;
    int M8 = M & -8, N4 = N & -4, LDC2 = LDC << 1, LDC3 = LDC2 + LDC, LDC4 = LDC << 2;
    __m128d vscalar = _mm_set1_pd(scalar);
    double *c_ptr_base1 = C, *c_ptr_base2 = C + LDC, *c_ptr_base3 = C + LDC2, *c_ptr_base4 = C + LDC3;
    double *c_ptr_dyn1, *c_ptr_dyn2, *c_ptr_dyn3, *c_ptr_dyn4;
    for (n_count = 0; n_count < N4; n_count += 4) {
        c_ptr_dyn1 = c_ptr_base1; c_ptr_dyn2 = c_ptr_base2; c_ptr_dyn3 = c_ptr_base3; c_ptr_dyn4 = c_ptr_base4;
        for (m_count = 0; m_count < M8; m_count += 8) {
            _mm_storeu_pd(c_ptr_dyn1, _mm_mul_pd(_mm_loadu_pd(c_ptr_dyn1), vscalar));
            _mm_storeu_pd(c_ptr_dyn2, _mm_mul_pd(_mm_loadu_pd(c_ptr_dyn2), vscalar));
            _mm_storeu_pd(c_ptr_dyn3, _mm_mul_pd(_mm_loadu_pd(c_ptr_dyn3), vscalar));
            _mm_storeu_pd(c_ptr_dyn4, _mm_mul_pd(_mm_loadu_pd(c_ptr_dyn4), vscalar));
            c_ptr_dyn1 += 8; c_ptr_dyn2 += 8; c_ptr_dyn3 += 8; c_ptr_dyn4 += 8;
        }
        for (; m_count < M; m_count++) {
            *c_ptr_dyn1 *= scalar; c_ptr_dyn1++;
            *c_ptr_dyn2 *= scalar; c_ptr_dyn2++;
            *c_ptr_dyn3 *= scalar; c_ptr_dyn3++;
            *c_ptr_dyn4 *= scalar; c_ptr_dyn4++;
        }
        c_ptr_base1 += LDC4; c_ptr_base2 += LDC4; c_ptr_base3 += LDC4; c_ptr_base4 += LDC4;
    }
    for (; n_count < N; n_count++) {
        c_ptr_dyn1 = c_ptr_base1;
        for (m_count = 0; m_count < M8; m_count += 8) {
            _mm_storeu_pd(c_ptr_dyn1, _mm_mul_pd(_mm_loadu_pd(c_ptr_dyn1), vscalar));
            c_ptr_dyn1 += 8;
        }
        for (; m_count < M; m_count++) {
            *c_ptr_dyn1 *= scalar; c_ptr_dyn1++;
        }
        c_ptr_base1 += LDC;
    }
}

void MY_MMult(int M, int N, int K, double alpha, double *A, int LDA, double *B, int LDB, double beta, double *C, int LDC) {
    int m, n, k, kk, mm, nn;
    int Mm = (M / M_BLOCKING) * M_BLOCKING;
    int Nn = (N / N_BLOCKING) * N_BLOCKING;
    int Kk = (K / K_BLOCKING) * K_BLOCKING;
    double packedA[M_BLOCKING * K_BLOCKING] __attribute__((aligned(32)));
    double packedB[K_BLOCKING * N_BLOCKING] __attribute__((aligned(32)));

    for (kk = 0; kk < Kk; kk += K_BLOCKING) {
        for (mm = 0; mm < Mm; mm += M_BLOCKING) {
            for (nn = 0; nn < Nn; nn += N_BLOCKING) {
                for (m = mm; m < mm + M_BLOCKING; m += 8) {
                    for (n = nn; n < nn + N_BLOCKING; n += 4) {
                        __m128d c00_70, c01_71, c10_72, c11_73, c20_74, c21_75, c30_76, c31_77, c40_78, c41_79, c50_80, c51_81, c60_82, c61_83, c70_84, c71_85;
                        c00_70 = _mm_setzero_pd(); c01_71 = _mm_setzero_pd();
                        c10_72 = _mm_setzero_pd(); c11_73 = _mm_setzero_pd();
                        c20_74 = _mm_setzero_pd(); c21_75 = _mm_setzero_pd();
                        c30_76 = _mm_setzero_pd(); c31_77 = _mm_setzero_pd();
                        c40_78 = _mm_setzero_pd(); c41_79 = _mm_setzero_pd();
                        c50_80 = _mm_setzero_pd(); c51_81 = _mm_setzero_pd();
                        c60_82 = _mm_setzero_pd(); c61_83 = _mm_setzero_pd();
                        c70_84 = _mm_setzero_pd(); c71_85 = _mm_setzero_pd();

                        for (k = kk; k < kk + K_BLOCKING; k++) {
                            __m128d b0, b1, a0;
                            b0 = _mm_load_sd(&B(k, n));
                            b1 = _mm_load_sd(&B(k, n + 1));
                            b0 = _mm_shuffle_pd(b0, b0, 0);
                            b1 = _mm_shuffle_pd(b1, b1, 0);

                            a0 = _mm_load_pd(&A(m, k));
                            c00_70 = _mm_add_pd(c00_70, _mm_mul_pd(a0, b0));
                            c01_71 = _mm_add_pd(c01_71, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 2, k));
                            c10_72 = _mm_add_pd(c10_72, _mm_mul_pd(a0, b0));
                            c11_73 = _mm_add_pd(c11_73, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 4, k));
                            c20_74 = _mm_add_pd(c20_74, _mm_mul_pd(a0, b0));
                            c21_75 = _mm_add_pd(c21_75, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 6, k));
                            c30_76 = _mm_add_pd(c30_76, _mm_mul_pd(a0, b0));
                            c31_77 = _mm_add_pd(c31_77, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 8, k));
                            c40_78 = _mm_add_pd(c40_78, _mm_mul_pd(a0, b0));
                            c41_79 = _mm_add_pd(c41_79, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 10, k));
                            c50_80 = _mm_add_pd(c50_80, _mm_mul_pd(a0, b0));
                            c51_81 = _mm_add_pd(c51_81, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 12, k));
                            c60_82 = _mm_add_pd(c60_82, _mm_mul_pd(a0, b0));
                            c61_83 = _mm_add_pd(c61_83, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 14, k));
                            c70_84 = _mm_add_pd(c70_84, _mm_mul_pd(a0, b0));
                            c71_85 = _mm_add_pd(c71_85, _mm_mul_pd(a0, b1));
                        }

                        _mm_store_pd(&packedA[(m - mm) * K_BLOCKING], c00_70);
                        _mm_store_pd(&packedA[(m - mm + 2) * K_BLOCKING], c10_72);
                        _mm_store_pd(&packedA[(m - mm + 4) * K_BLOCKING], c20_74);
                        _mm_store_pd(&packedA[(m - mm + 6) * K_BLOCKING], c30_76);
                        _mm_store_pd(&packedA[(m - mm + 8) * K_BLOCKING], c40_78);
                        _mm_store_pd(&packedA[(m - mm + 10) * K_BLOCKING], c50_80);
                        _mm_store_pd(&packedA[(m - mm + 12) * K_BLOCKING], c60_82);
                        _mm_store_pd(&packedA[(m - mm + 14) * K_BLOCKING], c70_84);

                        _mm_store_pd(&packedB[(n - nn) * K_BLOCKING], c01_71);
                        _mm_store_pd(&packedB[(n - nn + 2) * K_BLOCKING], c11_73);
                        _mm_store_pd(&packedB[(n - nn + 4) * K_BLOCKING], c21_75);
                        _mm_store_pd(&packedB[(n - nn + 6) * K_BLOCKING], c31_77);
                        _mm_store_pd(&packedB[(n - nn + 8) * K_BLOCKING], c41_79);
                        _mm_store_pd(&packedB[(n - nn + 10) * K_BLOCKING], c51_81);
                        _mm_store_pd(&packedB[(n - nn + 12) * K_BLOCKING], c61_83);
                        _mm_store_pd(&packedB[(n - nn + 14) * K_BLOCKING], c71_85);
                    }
                }

                for (m = mm; m < mm + M_BLOCKING; m++) {
                    for (n = nn; n < nn + N_BLOCKING; n++) {
                        double c00 = C(m, n);
                        for (k = kk; k < kk + K_BLOCKING; k++) {
                            c00 += A(m, k) * B(k, n);
                        }
                        C(m, n) = c00;
                    }
                }
            }
        }
    }

    for (; kk < K; kk++) {
        for (mm = 0; mm < Mm; mm += M_BLOCKING) {
            for (nn = 0; nn < Nn; nn += N_BLOCKING) {
                for (m = mm; m < mm + M_BLOCKING; m += 8) {
                    for (n = nn; n < nn + N_BLOCKING; n += 4) {
                        __m128d c00_70, c01_71, c10_72, c11_73, c20_74, c21_75, c30_76, c31_77, c40_78, c41_79, c50_80, c51_81, c60_82, c61_83, c70_84, c71_85;
                        c00_70 = _mm_setzero_pd(); c01_71 = _mm_setzero_pd();
                        c10_72 = _mm_setzero_pd(); c11_73 = _mm_setzero_pd();
                        c20_74 = _mm_setzero_pd(); c21_75 = _mm_setzero_pd();
                        c30_76 = _mm_setzero_pd(); c31_77 = _mm_setzero_pd();
                        c40_78 = _mm_setzero_pd(); c41_79 = _mm_setzero_pd();
                        c50_80 = _mm_setzero_pd(); c51_81 = _mm_setzero_pd();
                        c60_82 = _mm_setzero_pd(); c61_83 = _mm_setzero_pd();
                        c70_84 = _mm_setzero_pd(); c71_85 = _mm_setzero_pd();

                        for (k = kk; k < K; k++) {
                            __m128d b0, b1, a0;
                            b0 = _mm_load_sd(&B(k, n));
                            b1 = _mm_load_sd(&B(k, n + 1));
                            b0 = _mm_shuffle_pd(b0, b0, 0);
                            b1 = _mm_shuffle_pd(b1, b1, 0);

                            a0 = _mm_load_pd(&A(m, k));
                            c00_70 = _mm_add_pd(c00_70, _mm_mul_pd(a0, b0));
                            c01_71 = _mm_add_pd(c01_71, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 2, k));
                            c10_72 = _mm_add_pd(c10_72, _mm_mul_pd(a0, b0));
                            c11_73 = _mm_add_pd(c11_73, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 4, k));
                            c20_74 = _mm_add_pd(c20_74, _mm_mul_pd(a0, b0));
                            c21_75 = _mm_add_pd(c21_75, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 6, k));
                            c30_76 = _mm_add_pd(c30_76, _mm_mul_pd(a0, b0));
                            c31_77 = _mm_add_pd(c31_77, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 8, k));
                            c40_78 = _mm_add_pd(c40_78, _mm_mul_pd(a0, b0));
                            c41_79 = _mm_add_pd(c41_79, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 10, k));
                            c50_80 = _mm_add_pd(c50_80, _mm_mul_pd(a0, b0));
                            c51_81 = _mm_add_pd(c51_81, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 12, k));
                            c60_82 = _mm_add_pd(c60_82, _mm_mul_pd(a0, b0));
                            c61_83 = _mm_add_pd(c61_83, _mm_mul_pd(a0, b1));

                            a0 = _mm_load_pd(&A(m + 14, k));
                            c70_84 = _mm_add_pd(c70_84, _mm_mul_pd(a0, b0));
                            c71_85 = _mm_add_pd(c71_85, _mm_mul_pd(a0, b1));
                        }

                        _mm_store_pd(&packedA[(m - mm) * K_BLOCKING], c00_70);
                        _mm_store_pd(&packedA[(m - mm + 2) * K_BLOCKING], c10_72);
                        _mm_store_pd(&packedA[(m - mm + 4) * K_BLOCKING], c20_74);
                        _mm_store_pd(&packedA[(m - mm + 6) * K_BLOCKING], c30_76);
                        _mm_store_pd(&packedA[(m - mm + 8) * K_BLOCKING], c40_78);
                        _mm_store_pd(&packedA[(m - mm + 10) * K_BLOCKING], c50_80);
                        _mm_store_pd(&packedA[(m - mm + 12) * K_BLOCKING], c60_82);
                        _mm_store_pd(&packedA[(m - mm + 14) * K_BLOCKING], c70_84);

                        _mm_store_pd(&packedB[(n - nn) * K_BLOCKING], c01_71);
                        _mm_store_pd(&packedB[(n - nn + 2) * K_BLOCKING], c11_73);
                        _mm_store_pd(&packedB[(n - nn + 4) * K_BLOCKING], c21_75);
                        _mm_store_pd(&packedB[(n - nn + 6) * K_BLOCKING], c31_77);
                        _mm_store_pd(&packedB[(n - nn + 8) * K_BLOCKING], c41_79);
                        _mm_store_pd(&packedB[(n - nn + 10) * K_BLOCKING], c51_81);
                        _mm_store_pd(&packedB[(n - nn + 12) * K_BLOCKING], c61_83);
                        _mm_store_pd(&packedB[(n - nn + 14) * K_BLOCKING], c71_85);
                    }
                }

                for (m = mm; m < mm + M_BLOCKING; m++) {
                    for (n = nn; n < nn + N_BLOCKING; n++) {
                        double c00 = C(m, n);
                        for (k = kk; k < K; k++) {
                            c00 += A(m, k) * B(k, n);
                        }
                        C(m, n) = c00;
                    }
                }
            }
        }
    }
}
