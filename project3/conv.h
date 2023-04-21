#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct matrixData
{

    int width;
    int height;
    int channels;
    float *data;

} MatrixData;
MatrixData createMatrix(float, float, float, float *);
void freeMatrix(MatrixData *);
float dotproduct(const float *, const float *, int);
bool relu(MatrixData *);
bool add_padding(MatrixData *m, int padding);
void printMatrix(MatrixData *);
MatrixData convolution1d(MatrixData *inputMatrix, MatrixData *kernel, int start);
MatrixData convolutionNd(MatrixData *inputMatrix, MatrixData *kernel);
bool vecAdd(float *p2, const float *p1, int num);