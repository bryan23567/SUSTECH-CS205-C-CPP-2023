#include <iostream>
using namespace std;
class Complex
{
private:
    float realPart;
    float imaginaryPart;

public:
    Complex(int rP = 0, int iP = 0) : realPart(rP), imaginaryPart(iP) {}

    Complex add(const Complex &other) const
    {

        return Complex(this->realPart + other.realPart, this->imaginaryPart + other.imaginaryPart);
    }

    Complex substract(const Complex &other) const
    {
        return Complex(this->realPart - other.realPart, this->imaginaryPart - other.imaginaryPart);
    }

    void display() const
    {
        if (imaginaryPart < 0)
        {
            cout << realPart << imaginaryPart << "i" << endl;
        }
        else
        {
            cout << realPart << "+" << imaginaryPart << "i" << endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    Complex sum = c1.add(c2);
    Complex difference = c1.substract(c2);

    sum.display();        // Output: 4 + 6i
    difference.display(); // Output: -2 - 2i

    return 0;
}
