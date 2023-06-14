#include <random>
#include <iostream>
#include "cnn.hpp"
#ifdef WITH_AVX2
#include <immintrin.h>
#endif

#ifdef WITH_NEON
#include <arm_neon.h>
#endif

#ifdef _OPENMP
#include <omp.h>
#endif
template <>
void DataBlob<float>::generateRandomMatrix()
{
    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0, 100.0);
    for (size_t i = 0; i < rows * cols * channels; i++)
    {
        data[i] = distribution(gen);
    }
}
template <>
void DataBlob<int>::generateRandomMatrix()
{
    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 100);
    for (int i = 0; i < rows * cols * channels; i++)
    {
        data[i] = distribution(gen);
    }
}

template <>
DataBlob<float> DataBlob<float>::operator+(const DataBlob &other) const
{
    if (isEmpty() || other.isEmpty())
    {
        std::cerr << "DataBlob is empty" << std::endl;
        return DataBlob<float>();
    }

    if (rows != other.rows || cols != other.cols || channels != other.channels)
    {
        std::cerr << "size is not the same!" << std::endl;
        return DataBlob<float>();
    }
    size_t n = rows * cols * channels;
    DataBlob<float> result(cols, rows, channels);
    size_t startIndex = 0;
#if defined(WITH_AVX2)
    __m256 a, c;
#pragma omp parallel for
    for (size_t i = 0; i < n - (n % 8); i += 8)
    {
        a = _mm256_load_ps(data + i);
        c = _mm256_load_ps(other.data + i);
        c = _mm256_add_ps(a, c);
        _mm256_store_ps(result.data + i, c);
    }
    startIndex = n - (n % 8);
#elif defined(WITH_NEON)
    float32x4_t a, b, c;
    for (size_t i = 0; i < n - (n % 4); i += 4)
    {
        a = vld1q_f32(data + i);
        b = vld1q_f32(other.data + i);
        c = vaddq_f32(a, b);
        vst1q_f32(result.data + i, c);
    }
    startIndex = n - (n % 4);

#endif
    for (size_t i = startIndex; i < n; i++)
    {

        result.data[i] = data[i] + other.data[i];
    }

    return result;
}
template <>
DataBlob<float> DataBlob<float>::operator/(const DataBlob &other) const
{
    if (isEmpty() || other.isEmpty())
    {
        std::cerr << "DataBlob is empty" << std::endl;
        return DataBlob<float>();
    }

    if (rows != other.rows || cols != other.cols || channels != other.channels)
    {
        std::cerr << "size is not the same!" << std::endl;
        return DataBlob<float>();
    }

    size_t n = rows * cols * channels;
    DataBlob<float> result(cols, rows, channels);
    size_t startIndex = 0;
#if defined(WITH_AVX2)
    __m256 a, c;
    __m256 reciprocal;
#pragma omp parallel for
    for (size_t i = 0; i < n - (n % 8); i += 8)
    {
        a = _mm256_load_ps(data + i);
        c = _mm256_load_ps(other.data + i);
        reciprocal = _mm256_div_ps(a, c);
        _mm256_store_ps(result.data + i, reciprocal);
    }
    startIndex = n - (n % 8);
#elif defined(WITH_NEON)
    float32x4_t a, b, c;
    float32x4_t reciprocal;
    for (size_t i = 0; i < n - (n % 4); i += 4)
    {
        a = vld1q_f32(data + i);
        b = vld1q_f32(other.data + i);
        reciprocal = vdivq_f32(a, b);
        vst1q_f32(result.data + i, reciprocal);
    }
    startIndex = n - (n % 4);
#endif

    for (size_t i = startIndex; i < n; i++)
    {
        result.data[i] = data[i] / other.data[i];
    }

    return result;
}

template <>
float dotproduct(const DataBlob<float> &p1, const DataBlob<float> &p2, size_t n)
{
    float sum = 0.0f;
    size_t startIndex = 0;
#if defined(WITH_AVX2)
    // printf("WITH_AVX2\n");

    __m256 a, b;
    __m256 c = _mm256_setzero_ps();

#pragma omp parallel for
    for (size_t i = 0; i < n - (n % 8); i += 8)
    {
        a = _mm256_load_ps(p1 + i);
        b = _mm256_load_ps(p2 + i);
        c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
    }
    startIndex = n - (n % 8);
    c = _mm256_hadd_ps(c, c);
    c = _mm256_hadd_ps(c, c);
    sum = ((float *)&c)[0] + ((float *)&c)[4];
#elif defined(WITH_NEON)
    // printf("WITH_NEON\n");

    float32x4_t a,
        b;
    float32x4_t c = vdupq_n_f32(0);
    startIndex = n - (n % 4);
    for (size_t i = 0; i < n - (n % 4); i += 4)
    {
        a = vld1q_f32(p1 + i);
        b = vld1q_f32(p2 + i);
        c = vaddq_f32(c, vmulq_f32(a, b));
    }
    sum += vgetq_lane_f32(c, 0);
    sum += vgetq_lane_f32(c, 1);
    sum += vgetq_lane_f32(c, 2);
    sum += vgetq_lane_f32(c, 3);

    // printf("WITH_NORMAL\n");

#endif
    for (size_t i = startIndex; i < n; i++)
        sum += (p1(i) * p2(i));
    return sum;
}
template <>
DataBlob<float> &DataBlob<float>::relu()
{
    if (isEmpty())
    {
        std::cerr << "data blob is empty" << std::endl;
        return *this;
    }
    int len = this->cols * this->rows * this->channels;
#if defined(WITH_AVX2)

    __m256 a, b;
    b = _mm256_setzero_ps(); // zeros
#pragma omp parallel for
    for (size_t i = 0; i < len; i += 8)
    {
        a = _mm256_load_ps(*this + i);
        a = _mm256_max_ps(a, b);
        _mm256_store_ps(*this + i, a);
    }

#elif defined(WITH_NEON)

    float32x4_t a, b;
    b = vdupq_n_f32(0.0f); // zeros
    for (size_t i = 0; i < len; i += 4)
    {
        a = vld1q_f32(*this + i);
        a = vmaxq_f32(a, b);
        vst1q_f32(*this + i, a);
    }
#else
    // printf("WITH_NORMAL\n");
    for (size_t i = 0; i < len; i++)
        (*this)(i) = (*this)(i) > 0 ? (*this)(i) : 0;
#endif
    return *this;
};

template <>
DataBlob<float> DataBlob<float>::operator-(const DataBlob &other) const
{
    if (isEmpty() || other.isEmpty())
    {
        std::cerr << "DataBlob is empty" << std::endl;
        return DataBlob<float>();
    }

    if (rows != other.rows || cols != other.cols || channels != other.channels)
    {
        std::cerr << "size is not the same!" << std::endl;
        return DataBlob<float>();
    }

    size_t n = rows * cols * channels;
    DataBlob<float> result(cols, rows, channels);
    size_t startIndex = 0;

#if defined(WITH_AVX2)
    __m256 a, c;
#pragma omp parallel for
    for (size_t i = 0; i < n - (n % 8); i += 8)
    {
        a = _mm256_load_ps(data + i);
        c = _mm256_load_ps(other.data + i);
        c = _mm256_sub_ps(a, c); // subtraction instead of addition
        _mm256_store_ps(result.data + i, c);
    }
    startIndex = n - (n % 8);

#elif defined(WITH_NEON)
    float32x4_t a, b, c;
    for (size_t i = 0; i < n - (n % 4); i += 4)
    {
        a = vld1q_f32(data + i);
        b = vld1q_f32(other.data + i);
        c = vsubq_f32(a, b); // subtraction instead of addition
        vst1q_f32(result.data + i, c);
    }
    startIndex = n - (n % 4);

#endif

    for (size_t i = startIndex; i < n; i++)
    {
        result.data[i] = data[i] - other.data[i]; // subtraction instead of addition
    }

    return result;
}

template <>
DataBlob<float> DataBlob<float>::operator*(const DataBlob &other) const
{
    if (isEmpty() || other.isEmpty())
    {
        std::cerr << "DataBlob is empty" << std::endl;
        return DataBlob();
    }
    if (rows != other.rows || cols != other.cols || channels != other.channels)
    {
        std::cerr << "size is not the same!" << std::endl;
        return DataBlob();
    }
    DataBlob result(cols, rows, channels);
    size_t n = rows * cols * channels;
    size_t startIndex = 0;
#if defined(WITH_AVX2)
    // printf("WITH_AVX2\n");

    __m256 a, b;
    __m256 c = _mm256_setzero_ps();

#pragma omp parallel for
    for (size_t i = 0; i < n - (n % 8); i += 8)
    {
        a = _mm256_load_ps(data + i);
        b = _mm256_load_ps(other + i);
        c = _mm256_mul_ps(a, b);
        _mm256_store_ps(result.data + i, c);
    }
    startIndex = n - (n % 8);
#elif defined(WITH_NEON)
    // printf("WITH_NEON\n");

    float32x4_t a,
        b;
    float32x4_t c = vdupq_n_f32(0);
    startIndex = n - (n % 4);
    for (size_t i = 0; i < n - (n % 4); i += 4)
    {
        a = vld1q_f32(data + i);
        b = vld1q_f32(other.data + i);
        c = vmulq_f32(a, b);
        vst1q_f32(result.data + i, c);
    }

    // printf("WITH_NORMAL\n");

#endif
    for (size_t i = startIndex; i < n; i++)
    {

        result.data[i] = data[i] * other.data[i];
    }
    return result;
}