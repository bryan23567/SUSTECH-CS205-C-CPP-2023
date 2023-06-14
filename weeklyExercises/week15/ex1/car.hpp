#include <iostream>
class Car
{
private:
    enum
    {
        Off,
        On
    }; // Off- non automatically drive, On-automatically drive
    enum
    {
        Minvel,
        Maxvel = 200
    };        // range of velocity from 0 to 200
    int mode; // mode of car, Off or On
    int velocity;

public:
    friend class Driver;
    Car(int m = On, int v = 50) : mode(m), velocity(v) {}
    bool velup(int v);     // increase velocity by v
    bool veldown(int v);   // decrease velocity by v
    bool ison() const;     // Check whether the mode is on
    int getvel() const;    // get the velocity
    void showinfo() const; // show the mode and velocity of car
};
bool Car::velup(int v)
{

    if (velocity + v <= Maxvel)
    {
        velocity += v;
        std::cout << "Increase velocity by car, mode is " << (ison() ? "On" : "Off") << ", velocity is " << velocity << std::endl;
        return true;
    }
    else
    {
        velocity += v;
        std::cout << "Increase velocity by car, The velocity is " << velocity << ". It is out of Maxvel" << std::endl;
        return false;
    }
}

bool Car::veldown(int v)
{
    if (velocity - v <= Maxvel)
    {
        velocity -= v;
        std::cout << "Decrease velocity by car, mode is " << (ison() ? "On" : "Off") << ", velocity is " << velocity << std::endl;
        return true;
    }
    else
    {
        velocity -= v;
        std::cout << "Decrease velocity by car, The velocity is " << velocity << ". It is out of Maxvel" << std::endl;
        return false;
    }
}

bool Car::ison() const
{
    return (mode == Car::On);
}

int Car::getvel() const
{
    return velocity;
}

void Car::showinfo() const
{
    std::cout << "The information of car:"
              << "mode is " << (ison() ? "On, " : "Off, ") << "velocity is " << getvel() << std::endl;
}