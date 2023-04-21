#include <iostream>
using namespace std;
void displaySquare(int side = 4, char filledChar = '*');
int main()
{
    displaySquare();
    displaySquare(10, '#');
    displaySquare(4,'&');
    displaySquare(2);
    return 0;
}

void displaySquare(int side, char filledChar)
{
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
            cout << filledChar;
        cout << "\n";
    }
}