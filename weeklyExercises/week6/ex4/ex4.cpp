#include<iostream>
#include "swap.h"
using namespace std;

int main()
{
    int a,b;
    cin>>a>>b;
    cout<<"a: "<<a<<" b: "<<b<<endl;
    swap(a,b);
    cout<<"after swap:"<<endl;
    cout<<"a: "<<a<<" b: "<<b<<endl;
    return 0;
}
