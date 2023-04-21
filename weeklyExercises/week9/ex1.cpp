#include <iostream>
using namespace std;
class Demo
{
public:
    static int num;
    void display()
    {
        cout << "The value of the static member variable num is: " << num << endl;
    }
    void anotherDisplay()
    {
        display();
    }
};
int Demo::num = 0;
int main()
{
    Demo obj;
    obj.anotherDisplay();
    return 0;
}
