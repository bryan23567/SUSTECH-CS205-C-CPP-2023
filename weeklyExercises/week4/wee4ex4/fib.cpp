#include <iostream>
void fib(int num)
{
  
    int a = 0, b = 1;

    // Here we are printing 0th and 1st terms
    std::cout << b << " ";

    int nextTerm;

    // printing the rest of the terms here
    for (int i = 2; i < num; i++)
    {
        nextTerm = a + b;
        a = b;
        b = nextTerm;

        std::cout << nextTerm << " ";
    }
    std::cout<<std::endl;
}