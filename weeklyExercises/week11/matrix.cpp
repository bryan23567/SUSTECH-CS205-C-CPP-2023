#include "matrix.hpp"

Matrix::Matrix(int rows, int cols)
    : rows(rows),
      cols(cols),
      data(new float[rows * cols]) {}

Matrix::Matrix(const Matrix &other)
    : rows(other.rows),
      cols(other.cols),
      data(other.data) {}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (other.rows == this->rows || other.cols != this->rows)
    {
        return Matrix(0,0);
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        (result.data)[i] = (data)[i] + (other.data)[i];
    }
    return result;
}