#pragma once
#include <iostream>
class Complex
{
public:
    Complex(double real = 0.0, double imaginary = 0.0) : realPart(real), imaginaryPart(imaginary) {}

    double getRealPart() const;
    double getImaginaryPart() const;

    void setRealPart(double real);

    void setImaginaryPart(double imaginary);
    Complex operator+(const Complex &c) const;
    Complex operator-(const Complex &c) const;
    Complex &operator=(const Complex &c);
    Complex operator*(const Complex &c) const;
    bool operator==(const Complex &c) const;
    bool operator!=(const Complex &c) const;
    friend std::ostream &operator<<(std::ostream &os, const Complex &c);
    friend std::istream &operator>>(std::istream &is, Complex &c);
private:
    double realPart;
    double imaginaryPart;
};