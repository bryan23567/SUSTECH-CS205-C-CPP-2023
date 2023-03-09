#include <iostream>

using namespace std;
enum Day
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
};
enum Weather
{
    Sunny,
    Rainy,
    Cloudy,
};
struct DayInfo
{
    enum Day day;
    enum Weather weather;
};

bool canTravel(DayInfo dayInfo)
{
    if ((dayInfo.day == Saturday || dayInfo.day == Sunday) && dayInfo.weather == Sunny)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    DayInfo day1 = {Saturday, Sunny};
    cout << "Is the day good? " << canTravel(day1) << endl;
    day1 = {Monday, Sunny};
    cout << "Is the day good? " << canTravel(day1) << endl;
    return 0;
}
