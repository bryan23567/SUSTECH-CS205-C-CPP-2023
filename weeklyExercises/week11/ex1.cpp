#include <iostream>
#include <memory>
using namespace std;
int main()
{
    double *p_reg = new double(5);
    shared_ptr<double> pd;
    // pd = p_reg;
    pd = make_shared<double>(*p_reg);
    cout << "*pd = " << *pd << endl;
    // shared_ptr<double> pshared = p_reg;
    shared_ptr<double> pshared(p_reg);
    cout << "*pshred = " << *pshared << endl;
    
    string str("Hello World!");
    shared_ptr<string> pstr =make_shared<string>(str);
    cout << "*pstr = " << *pstr << endl;
    return 0;
}
