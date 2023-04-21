#include <iostream>
using namespace std;
#define SIZE 5
int sum(const int *pArray, int n);
int main()
{
    int const *pa = new int[SIZE]{3,5,8,2,6};
    int total = sum(pa,SIZE);
    cout << "sum = " << total << endl;
    delete[]pa;
    return 0;
}
int sum(const int *pArray, int n)
{
    int s = 0;
    if (pArray == NULL)
    {
        cout<<"error"<<endl;
       return 0;
    }
    
    for(int i = 0; i < n; i++)
         s += pArray[i];
     return s;
}
