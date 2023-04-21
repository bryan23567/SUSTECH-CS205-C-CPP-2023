#include <iostream>
#include <cstring>
using namespace std;
struct stuinfo
{
    std::string name;
    int age;
};
template <typename T>
int Compare(const T &a, const T &b)
{

    if (a > b)
    {
        return 1;
    }
    else if (a < b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

template<>
int Compare<stuinfo>(const stuinfo &a, const stuinfo &b)
{
    if (a.age > b.age)
    {
        return 1;
    }
    else if (a.age < b.age)
    {
        return -1;
    }
    else
    {
        return 0;
    }
};