#include <iostream>
#include <chrono>
#include "cnn.hpp"
using namespace std;
#define TIME_START start = std::chrono::steady_clock::now();
#define TIME_END                                                                           \
    end = std::chrono::steady_clock::now();                                                \
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
    cout << "took time = " << duration << "ms" << endl;
int main(int argc, char const *argv[])
{
    std::chrono::steady_clock::time_point start, end;
    long long duration;

    // DataBlob<float> A(2, 2, 1);
    // DataBlob<int> B(2, 2, 1);
    // A.generateRandomMatrix();
    // B.generateRandomMatrix();
    // cout<<"A= \n"<<A;
    // cout<<"B= \n"<<B;
    // DataBlob<double> C = A + B;
    // cout << "A + B= \n" << C;
    // C = A - B;
    // cout << "A - B= \n" << C;
    // C = A * B;
    // cout << "A * B= \n" << C;
    // C = A / B;
    // cout << "A / B= \n" << C;

    // DataBlob<float> fmat(5, 5, 1);
    // fmat.generateRandomMatrix();
    // cout << "fmat :" << endl;
    // cout << fmat;
    // DataBlob<int> imat(5, 5, 1);
    // imat.generateRandomMatrix();
    // cout << "imat :" << endl;
    // cout << imat;
    // // DataBlob<int> res = fmat + imat;
    // // cout << res;
    // // cout<<fmat;

    // fmat = fmat * imat;
    // cout << fmat;

    int cols, rows, channels;
    cin >> cols >> rows >> channels;
    int matrixSize = cols * rows * channels;
    DataBlob<float> originalMatrix(cols, rows, channels);
    // random generated matrix

    originalMatrix.generateRandomMatrix();

    // input matrix from by CLI
    // for (size_t i = 0; i < matrixSize; i++)
    // {
    //     cin >> originalMatrix(i);
    // }
    int kcols, krows, numofkernel;
    cin >> numofkernel;
    cin >> kcols >> krows;
    DataBlob<float> *kernelMatrix = new DataBlob<float>[numofkernel];
    int kSize = kcols * krows * channels;

    for (size_t i = 0; i < numofkernel; i++)
    {

        kernelMatrix[i] = DataBlob<float>(krows, kcols, channels);
        // random generated matrix
        kernelMatrix[i].generateRandomMatrix();
        // input matrix from by CLI
        // for (size_t j = 0; j < kSize; j++)
        // {
        //     cin >> kernelMatrix[i](j);
        // }
    }
    // cout << originalMatrix.add_padding(1);

    int outputcols = originalMatrix.getCols() - kcols + 1;
    int outputrows = originalMatrix.getRows() - krows + 1;
    DataBlob<float> outputMatrix(outputcols, outputrows, 1);
    TIME_START
    for (int i = 0; i < numofkernel; i++)
    {
        outputMatrix += convolutional<float>(originalMatrix, kernelMatrix[i]);
    }
    TIME_END
    // cout << outputMatrix.relu();
    // DataBlob<int> res;
    // res = outputMatrix;
    // cout << res;
    // cout << "outputMatrix and res is not the same : " << (outputMatrix != res) << endl;
    delete[] kernelMatrix;
    return 0;
}
