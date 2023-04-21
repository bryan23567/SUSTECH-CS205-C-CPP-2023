#include <iostream>
using namespace std;
int main()
{
    char *pc, cc = 'A';
    int *pi, ii = 10;
    float *pf, ff = 23.4f;
    double *pd, dd = 123.78;
    pc = &cc;
    pi = &ii;
    pf = &ff;
    pd = &dd;
    cout << "sizeof(cc) = " << sizeof(cc) << ", sizeof(pc) = " << sizeof(pc) << endl;
    cout << "sizeof(ii) = " << sizeof(ii) << ", sizeof(pi) = " << sizeof(pi) << endl;
    cout << "sizeof(ff) = " << sizeof(ff) << ", sizeof(pf) = " << sizeof(pf) << endl;
    cout << "sizeof(dd) = " << sizeof(dd) << ", sizeof(pd) = " << sizeof(pd) << endl;
    cout << "&pc = " << &pc << ", cc = " << &cc << ", pc = " << static_cast<void *>(pc) << ", *pc = " << *pc << endl;
    cout << "&pi = " << &pi << ", pi = " << pi << ", *pi = " << *pi << endl;
    cout << "&pf = " << &pf << ", pf = " << pf << ", *pf = " << *pf << endl;
    cout << "&pd = " << &pd << ", pd = " << pd << ", *pd = " << *pd << endl;
    const char *msg = "C/C++ programming is fun.";
    const char *copy;
    copy = msg;
    cout << "msg = " << msg << ",its address is: " << (void *)msg << ", &msg = " << &msg << endl;
    cout << "copy= " << copy << ",its address is: " << (void *)copy << ", &copy= " << &copy << endl;
    return 0;
}
