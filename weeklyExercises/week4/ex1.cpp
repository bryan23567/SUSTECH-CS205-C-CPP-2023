#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    int cards[4]{};
    int hands[4];
    int price[] = {2, 3, 5, 9};
    char direction[5]{'L', 'A', 'U', 'R'};
    char title[] = "ChartGPT is an awesome tool.";
    cout << "sizeof(cards) = " << sizeof(cards) << ",sizeof of cards[0] = " << sizeof(cards[0]) << endl;
    cout << "sizeof(price) = " << sizeof(price) << ",sizeof of price[0] = " << sizeof(price[1]) << endl;
    cout << "sizeof(direction) = " << sizeof(direction) << ",length of direction = " << strlen(direction) << endl;
    cout << "sizeof(title) = " << sizeof(title) << ",length of title = " << strlen(title) << endl;
    // Print the value and address of each element in cards and hands respectively.
    for (int i = 0; i < 4; i++)
    {
        cout << "cards " << i << " address " << &cards[i] << " and value " << cards[i] << endl;
    }
    for (int i = 0; i < 4; i++)
    {
        cout << "hands " << i << " address " << &hands[i] << " and value " << hands[i] << endl;
    }
    return 0;
}
