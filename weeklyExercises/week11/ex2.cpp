#include "matrix.hpp"
int main(int argc, char const *argv[])
{
    Matrix a(3, 4);
    Matrix b(3, 4);
    Matrix c = a + b;
    Matrix d = a;
    d = b;
    return 0;
}
