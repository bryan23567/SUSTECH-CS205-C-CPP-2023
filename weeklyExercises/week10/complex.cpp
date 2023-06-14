#include "complex.hpp"
double Complex::getRealPart() const
{
    return realPart;
};

double Complex::getImaginaryPart() const
{
    return imaginaryPart;
}

void Complex::setRealPart(double real)
{
    realPart = real;
}

void Complex::setImaginaryPart(double imaginary)
{
    imaginaryPart = imaginary;
}
Complex Complex::operator+(const Complex &c) const
{
    return Complex(realPart + c.realPart, imaginaryPart + c.imaginaryPart);
}
Complex Complex::operator-(const Complex &c) const
{
    return Complex(realPart - c.realPart, imaginaryPart - c.imaginaryPart);
}
Complex &Complex::operator=(const Complex &c)
{
    realPart = c.realPart;
    imaginaryPart = c.imaginaryPart;
    return *this;
}
Complex Complex::operator*(const Complex &c) const
{
    double real = realPart * c.realPart - imaginaryPart * c.imaginaryPart;
    double imaginary = realPart * c.imaginaryPart + imaginaryPart * c.realPart;
    return Complex(real, imaginary);
}
bool Complex::operator==(const Complex &c) const
{
    return (realPart == c.realPart) && (imaginaryPart == c.imaginaryPart);
}

bool Complex::operator!=(const Complex &c) const
{
    return !(*this == c);
}

std::istream &operator>>(std::istream &is, Complex &c)
{
    double real, im;
    is >> real >> im;
    c.setRealPart(real);
    c.setImaginaryPart(im);
    return is;
}
std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    if (c.getImaginaryPart() < 0)
    {
        os << c.getRealPart() << c.getImaginaryPart() << "i";
    }
    else
    {
        os << c.getRealPart() << "+" << c.getImaginaryPart() << "i";
    }
    return os;
}