#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "conv.h"

#ifdef WITH_AVX2
#include <immintrin.h>
#endif

#ifdef WITH_NEON
#include <arm_neon.h>
#endif

#ifdef _OPENMP
#include <omp.h>
#endif

MatrixData createMatrix(float w, float h, float c, float *d)
{
    MatrixData m;
    m.width = w;
    m.height = h;
    m.channels = c;
    m.data = d;
    return m;
}
bool vecAdd(float *p2, const float *p1, int n)
{
    int startIndex = 0;
#if defined(WITH_AVX2)
    __m256 a, c;
#pragma omp parallel for
    for (int i = 0; i < n - (n % 8); i += 8)
    {
        a = _mm256_load_ps(p1 + i);
        c = _mm256_load_ps(p2 + i);
        c = _mm256_add_ps(a, c);
        _mm256_store_ps(p2 + i, c);
    }
    startIndex = n - (n % 8);
#elif defined(WITH_NEON)
    float32x4_t a, b, c;
    for (int i = 0; i < n - (n % 4); i += 4)
    {
        a = vld1q_f32(p1 + i);
        b = vld1q_f32(p2 + i);
        c = vaddq_f32(a, b);
        vst1q_f32(p2 + i, c);
    }
    startIndex = n - (n % 4);

#endif
    for (int i = startIndex; i < n; i++)
    {

        p2[i] += p1[i];
    }
    return true;
}
void freeMatrix(MatrixData *m)
{
    if (m->data != NULL)
        free(m->data);
    m->width = m->height = m->channels = 0;
    m->data = NULL;
}
MatrixData convolution1d(MatrixData *inputMatrix, MatrixData *kernel, int start)
{

    int tempMatrixSize = kernel->width * kernel->height;
    float *tempMatrix;
    int outputWidth = inputMatrix->width - kernel->width + 1;
    int outputHeight = inputMatrix->height - kernel->height + 1;
    int outputSize = outputHeight * outputWidth;
    float *output;
    int ret1 = posix_memalign((void **)&output, 256, outputSize * sizeof(float));
    if (ret1 != 0)
    {
        // Handle error...
        printf("Memory aligned failed\n");
        return createMatrix(0, 0, 0, NULL);
    }

    int ret2 = posix_memalign((void **)&tempMatrix, 256, tempMatrixSize * sizeof(float));
    if (ret2 != 0)
    {
        // Handle error...
        printf("Memory aligned failed\n");
        return createMatrix(0, 0, 0, NULL);
    }
    int temp_matrix_index = 0;

    int output_matrix_index = 0;
    int firstInd = start;

    for (int k = 1; k <= outputHeight; start++)
    {
        // take the temp matrix

        for (int i = start; i < (inputMatrix->width * inputMatrix->height) + start; i += inputMatrix->width)
        {
            for (int j = i; j < kernel->width + i; j++)
            {

                tempMatrix[temp_matrix_index++] = inputMatrix->data[j];
            }

            if (temp_matrix_index == tempMatrixSize)
            {
                temp_matrix_index = 0;
                break;
            }
        }

        output[output_matrix_index++] = dotproduct(tempMatrix, kernel->data, tempMatrixSize);
        if (start == (inputMatrix->width * k) - kernel->width + firstInd)
        {

            start += kernel->width - 1;
            k++;
        }
    }

    free(tempMatrix);

    return createMatrix(outputWidth, outputHeight, 1, output);
}

MatrixData convolutionNd(MatrixData *inputMatrix, MatrixData *kernel)
{

    int outputWidth = inputMatrix->width - kernel->width + 1;
    int outputHeight = inputMatrix->height - kernel->height + 1;
    int outputSize = outputHeight * outputWidth;
    MatrixData temp;
    MatrixData output;

    int ret1 = posix_memalign((void **)&output.data, 256, outputSize * sizeof(float));
    if (ret1 != 0)
    {
        // Handle error...
        printf("Memory aligned failed\n");
        return createMatrix(0, 0, 0, NULL);
    }
    output.width = outputWidth;
    output.height = outputHeight;
    output.channels = 1;
    int oneMatrixsize = inputMatrix->height * inputMatrix->width;
    memset(output.data, 0, outputSize * sizeof(float));
    for (int i = 0, k = 0; i < inputMatrix->channels; i++, k += oneMatrixsize)
    {

        temp = convolution1d(inputMatrix, kernel, k);

        if (vecAdd(output.data, temp.data, outputSize) == false)
        {
            freeMatrix(&temp);
            return createMatrix(0, 0, 0, NULL);
        }
        freeMatrix(&temp);
    }
    return output;
}

bool relu(MatrixData *m)
{
    if (m->data == NULL)
    {
        printf("Input is not valid\n");
        return false;
    }
    int len = m->width * m->height * m->channels;
#if defined(WITH_AVX2)

    __m256 a, b;
    b = _mm256_setzero_ps(); // zeros
#pragma omp parallel for
    for (int i = 0; i < len; i += 8)
    {
        a = _mm256_load_ps(m->data + i);
        a = _mm256_max_ps(a, b);
        _mm256_store_ps(m->data + i, a);
    }

#elif defined(WITH_NEON)

    float32x4_t a, b;
    b = vdupq_n_f32(0.0f); // zeros
    for (int i = 0; i < len; i += 4)
    {
        a = vld1q_f32(m->data + i);
        a = vmaxq_f32(a, b);
        vst1q_f32(m->data + i, a);
    }
#else
    // printf("WITH_NORMAL\n");
    for (int i = 0; i < len; i++)
        m->data[i] = m->data[i] > 0 ? m->data[i] : 0;
#endif
    return true;
}

float dotproduct(const float *p1, const float *p2, int n)
{
    float sum = 0.0f;
    int startIndex = 0;
#if defined(WITH_AVX2)
    // printf("WITH_AVX2\n");

    __m256 a, b;
    __m256 c = _mm256_setzero_ps();

#pragma omp parallel for
    for (int i = 0; i < n - (n % 8); i += 8)
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
    for (int i = startIndex; i < n; i++)
        sum += (p1[i] * p2[i]);
    return sum;
}

bool add_padding(MatrixData *m, int padding)
{
    int padded_width = m->width + 2 * padding;
    int padded_height = m->height + 2 * padding;
    int ch = m->channels;
    int padded_size = padded_width * padded_height * ch;
    float *padded;
    int ret1 = posix_memalign((void **)&padded, 256, padded_size * sizeof(float));

    if (ret1 != 0)
    {
        // Handle error...
        printf("Memory aligned failed\n");
        return 0;
    }
    memset(padded, 0, padded_size * sizeof(float));
    for (int c = 0; c < ch; c++)
    {
        for (int y = 0; y < m->height; y++)
        {
            for (int x = 0; x < m->width; x++)
            {
                int index = (c * m->height + y) * m->width + x;
                int padded_index = ((c * padded_height) + (y + padding)) * padded_width + (x + padding);
                padded[padded_index] = m->data[index];
            }
        }
    }
    freeMatrix(m);
    *m = createMatrix(padded_width, padded_height, ch, padded);

    return true;
}

void printMatrix(MatrixData *m)
{
    int mSize = m->width * m->height * m->channels;
    for (int i = 0; i < mSize; i++)
    {

        printf("%.2f ", m->data[i]);
        if ((i + 1) % m->width == 0)
        {
            printf("\n");
        }
    }
}