#include <iostream>
#include "fib.hpp"
using namespace std;

int main()
{
    int n;
    cout<<"Please input a positive integer:";
    cin>>n;
    if (n==0)
    {
        cout<<0<<endl;
        return 0;
    }
    if(n<0){
        return 0;
    }
    fib(n);

    return 0;
}