#include <iostream>
using namespace std;
class Polygon
{
protected:
    int width, height;

public:
    void set_values(int a, int b)
    {
        width = a;
        height = b;
    }
    int area()
    {
        return 0;
    }
};

class Rectangle : public Polygon
{
public:
    int area()
    {
        return width * height;
    }
};
class Triangle : public Polygon
{
public:
    int area()
    {
        return width * height / 2;
    }
};

int main()
{
    Rectangle rect;
    Triangle trgl;
    Polygon *ppoly1 = &rect;
    Polygon *ppoly2 = &trgl;
    ppoly1->set_values(4, 5);
    ppoly2->set_values(2, 5);

    cout << rect.area() << endl;
    cout << trgl.area() << endl;
    cout << ppoly1->area() << endl;
    cout << ppoly2->area() << endl;
    return 0;
}
