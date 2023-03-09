#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

int main(int argc, char const *argv[])
{
    srand((float)time(NULL));
    for (int n = 1; n < 1000000000; n *= 10)
    {
        float *vec1 = (float *)malloc(n * sizeof(float));
        float *vec2 = (float *)malloc(n * sizeof(float));
        for (size_t i = 0; i < n; i++)
        {
            vec1[i] = (float)(1 + rand() % 9) / (float)(1 + rand() % 9);
            vec2[i] = (float)(1 + rand() % 9) / (float)(1 + rand() % 9);
        }
        auto start = high_resolution_clock::now();
        float total = 0;
        for (int i = 0; i < n; i++)
        {
            total += vec1[i] * vec2[i];
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        float lenghtV1 = 0;
        for (int i = 0; i < n; i++)
        {
            lenghtV1 += vec1[i] * vec1[i];
        }
        float lenghtV2 = 0;
        for (int i = 0; i < n; i++)
        {
            lenghtV2 += vec2[i] * vec2[i];
        }

        lenghtV1 = sqrt(lenghtV1);
        lenghtV2 = sqrt(lenghtV2);

        cout << "Vector1 with lenght: " << lenghtV1 << " and "
             << "Vector2 with lenght: " << lenghtV2 << " takes time " << duration.count() << " microseconds" << endl;
    }

    return 0;
}
