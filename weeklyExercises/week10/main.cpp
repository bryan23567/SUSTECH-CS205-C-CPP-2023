#include <iostream>
#include "complex.hpp"

int main()
{

    Complex c1;
    Complex c2;
    std::cin>>c1>>c2;

    Complex sum = c1 + c2;
    Complex difference = c1 - c2;
    Complex product = c1 * c2;

    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c1 + c2 = " << sum << std::endl;
    std::cout << "c1 - c2 = " << difference << std::endl;
    std::cout << "c1 * c2 = " << product << std::endl;

    return 0;
}