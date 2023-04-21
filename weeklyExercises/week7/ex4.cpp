#include <iostream>
#include "compare.cpp"
using namespace std;

int main()
{
    stuinfo *a = new stuinfo({"A", 3});
    stuinfo *b = new stuinfo({"B", 5});
    cout << "Compare of the two integers:" << Compare(2, 3) << endl;
    cout << "Compare of the two floats:" << Compare(4.8f, 3.1f) << endl;
    cout << "Compare of the two characters:" << Compare('b', 'a') << endl;
    cout << "Compare of the two structs:" << Compare(a,b) << endl;
    return 0;
}
