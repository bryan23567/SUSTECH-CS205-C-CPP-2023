#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    // int * arr = (int*) malloc(sizeof(int)*5);
    int * arr = new int[5];
    *(arr) = 1;
    *(arr+1) = 2;
    *(arr+2) = 3;
    *(arr+3) = 4;
    *(arr+4) = 5;
    for (int i = 4; i >= 0; i--)
    {
        cout<<*(arr+i)<<endl;
    }
    
    delete []arr;
    return 0;
}
