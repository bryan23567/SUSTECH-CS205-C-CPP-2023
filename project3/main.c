#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "conv.h"

#define TIME_START clock_t start = clock();
#define TIME_END                                                \
    clock_t end = clock();                                      \
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC; \
    printf("Program took %f seconds to execute\n", time_taken);

int main(int argc, char const *argv[])
{

    int width, height, channels;
    // printf("input width, height, and the number channels of Matrix: \n");
    scanf("%d %d %d", &width, &height, &channels);
    float *matrix;
    int mSize = width * height * channels;

    int ret1 = posix_memalign((void **)&matrix, 256, mSize * sizeof(float));

    if (ret1 != 0)
    {
        // Handle error...
        printf("Memory aligned failed\n");
        return 0;
    }
    // printf("input the Matrix: \n");
    for (int i = 0; i < mSize; i++)
    {
        scanf("%f", &matrix[i]);
    }
    MatrixData originMatrix = createMatrix(width, height, channels, matrix);
    int kwidth, kheight, numofkernel;
    // printf("please input number of kernel \n");
    scanf("%d", &numofkernel);
    MatrixData *filterMatrix = (MatrixData *)malloc(sizeof(MatrixData) * numofkernel);
    // printf("input width and height of kernel with channels %d: \n", channels);
    scanf("%d %d", &kwidth, &kheight);
    int kSize = kwidth * kheight * channels;

    for (int i = 0; i < numofkernel; i++)
    {
        float *kernel;

        ret1 = posix_memalign((void **)&kernel, 256, kSize * sizeof(float));
        if (ret1 != 0)
        {
            // Handle error...
            printf("Memory aligned failed\n");
            return 0;
        }
        // printf("kernel-%d\n", i + 1);

        // printf("input the Kernel: \n");
        for (int i = 0; i < kSize; i++)
        {
            scanf("%f", &kernel[i]);
        }
        filterMatrix[i] = createMatrix(kwidth, kheight, channels, kernel);
        // free(kernel);
    }
    // after input matrix and kernel
    float *ouputData;

    ret1 = posix_memalign((void **)&ouputData, 256, (originMatrix.width - kwidth + 1) * (originMatrix.height - kheight + 1) * sizeof(float));
    if (ret1 != 0)
    {
        // Handle error...
        printf("Memory aligned failed\n");
        return 0;
    }
    MatrixData featureMap = createMatrix(originMatrix.width - kwidth + 1, originMatrix.height - kheight + 1, 1, ouputData);
    memset(ouputData, 0, (originMatrix.width - kwidth + 1) * (originMatrix.height - kheight + 1) * sizeof(float));
    MatrixData temp;

    // add_padding(&originMatrix, 10); //uncomment this part if you want to use padding the second argument is the number of padding you want to add

    TIME_START // uncomment this part will give you the time execution
        for (int i = 0; i < numofkernel; i++)
    {
        temp = convolutionNd(&originMatrix, &filterMatrix[i]);

        vecAdd(featureMap.data, temp.data, temp.height * temp.width * temp.channels);
        freeMatrix(&temp);
    }
    TIME_END // uncomment this part will give you the time execution

        // relu(&featureMap); //uncomment this part if you want to use relu

        printMatrix(&featureMap);

    // REALEASE THE MEMORY
    for (int i = 0; i < numofkernel; i++)
    {
        free(filterMatrix[i].data);
    }
    freeMatrix(&originMatrix);
    free(filterMatrix);
    freeMatrix(&featureMap);
    return 0;
}
