#include <iostream>
#include "stuinfo.hpp"
using namespace std;

int main()
{
    int n;
    cout<<"input number of students: ";
    cin>>n;
    stuinfo *stuarray = new stuinfo[n];
    inputstu(stuarray,n);
    showstu(stuarray,n);
    return 0;
}

