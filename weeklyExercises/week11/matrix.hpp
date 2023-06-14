#include <memory>
#include <vector>

class Matrix
{
public:
    Matrix(int rows, int cols);
    Matrix(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    Matrix operator+(const Matrix &other) ;

private:
    int rows;
    int cols;
    std::shared_ptr<float[]> data;
};