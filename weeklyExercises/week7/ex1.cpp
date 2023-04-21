#include <iostream>
#include <string>
#include "match.h"
using namespace std;

int main(int argc, char const *argv[])
{
    string s;
    char ch;

    cout << "Please input a string:" << endl;
    getline(cin, s);
    cout << "Please input a character:" << endl;
    cin >> ch;

    cout << match(s.c_str(), ch)<<endl;
    return 0;
}
