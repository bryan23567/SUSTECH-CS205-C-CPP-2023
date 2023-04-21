#include <iostream>
#include "stuinfo.hpp"

void inputstu(stuinfo stu[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cin >> stu[i].name >> stu[i].score[0] >> stu[i].score[1] >> stu[i].score[2];
        stu[i].ave = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / (double)3;
    }
}
void showstu(stuinfo stu[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("no: %d ", i+1);
        printf("name: %s ", stu[i].name);
        printf("scores (1,2,3): %.2lf %.2lf %.2lf ", stu[i].score[0], stu[i].score[1], stu[i].score[2]);
        printf("average: %.2lf\n", stu[i].ave);
    }
}
