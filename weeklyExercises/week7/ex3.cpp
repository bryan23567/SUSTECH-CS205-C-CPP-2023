#include <iostream>

bool vabs(int *p, size_t n)
{
    if (p == NULL)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (p[i] < 0)
        {
            p[i] = -p[i];
        }
    }
    return true;
}
bool vabs(double *p, size_t n)
{
    if (p == NULL)
    {
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i] < 0)
        {
            p[i] = -p[i];
        }
    }
    return true;
}
bool vabs(float *p, size_t n)
{
    if (p == NULL)
    {
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i] < 0)
        {
            p[i] = -p[i];
        }
    }
    return true;
}
int main()
{
    int arr1[] = {-1, 2, -3, 4, -5};
    float arr2[] = {-1.1, 2.2, -3.3, 4.4, -5.5};
    double arr3[] = {-1.1, 2.2, -3.3, 4.4, -5.5};

    if (vabs(arr1, 5))
    {
        for (int i = 0; i < 5; i++)
        {

            std::cout << arr1[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        "Array error";
    }
    if (vabs(arr2, 5))
    {
        for (int i = 0; i < 5; i++)
        {

            std::cout << arr2[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        "Array error";
    }
    if (vabs(arr3, 5))
    {
        for (int i = 0; i < 5; i++)
        {

            std::cout << arr3[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        "Array error";
    }

    return 0;
}