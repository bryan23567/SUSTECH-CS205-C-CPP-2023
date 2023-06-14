#include "dgemm_opt.hpp"
#include <cblas.h>
#include <iostream>
#include <chrono>
#include <string>
#include <random>

int len[30] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100,
               1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000,
               2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000};

#define TIME_START start = std::chrono::steady_clock::now();
#define TIME_END(name)                                                                   \
  end = std::chrono::steady_clock::now();                                                \
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
  std::cerr << name << "\nm=n=k= " << m << "\ntook time = " << duration << "ms" << std::endl;
void printMatrix(const double *matrix, const int rows, const int cols, std::string note = " ")
{
  std::cout << note << std::endl;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      std::cout << matrix[i * cols + j] << " ";
    }
    std::cout << std::endl;
  }
}
int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1);
  std::chrono::steady_clock::time_point start, end;
  long long duration;

  for (int j = 0; j < 2; j++)
  {
    int n, m, k;
    n = m = k = len[j];
    double alpha, beta;
    alpha = beta = 1;
    double *A = new double[m * k];
    double *B = new double[n * k];
    double *C = new double[n * m];
    double *Cref = new double[n * m];

    for (int i = 0; i < m * k; i++)
    {
      A[i] = distribution(gen);
    }
    for (int i = 0; i < n * k; i++)
    {
      B[i] = distribution(gen);
    }
    for (int i = 0; i < n * m; i++)
    {
      C[i] = distribution(gen);
      Cref[i] = C[i];
    }

    // TIME_START
    // naive_dgemm(m, n, k, alpha, A, k, B, n, beta, C, m);
    // TIME_END("Using naive_dgemm")

    TIME_START
    register_blocking_2x2_dgemm(m, n, k, alpha, A, k, B, n, beta, C, m);
    TIME_END("Using register_blocking_2x2_dgemm")
    printMatrix(C, m, n);
    // TIME_START
    // register_blocking_4x4_dgemm(m, n, k, alpha, A, k, B, n, beta, C, m);
    // TIME_END("Using register_blocking_4x4_dgemm")

    // TIME_START
    // register_blocking_4x4_SSE_dgemm(m, n, k, alpha, A, k, B, n, beta, C, m);
    // TIME_END("Using register_blocking_4x4_SSE_dgemm")
    // TIME_START
    // MY_MMult(m, n, k, alpha, A, k, B, n, beta, C, m);
    // TIME_END("Using register_blocking_4x4_SSE_dgemm")
    // printMatrix(C, m, n);
    // TIME_START
    // cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, k, B, n, beta, Cref, m);
    // TIME_END("Using OpenBlass")
    // printMatrix(Cref, m, n);
    free(A);
    free(B);
    free(C);
    // free(Cref);
  }

  return 0;
}