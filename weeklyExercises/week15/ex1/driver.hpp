#include "car.hpp"
class Driver
{
public:
    bool velup(Car &car, int v);   // increase velocity by v
    bool veldown(Car &car, int v); // decrease velocity by v
    void setmode(Car &car);        // If the mode is On, set it to Off,otherwise set it to Off
    bool ison(Car &car) const;     // Check whether the mode is on
};
bool Driver::veldown(Car &car, int v)
{
    if (car.velocity - v >= Car::Minvel)
    {
        car.velocity -= v;
        std::cout << "Decrease velocity by driver, mode is " << (car.ison() ? "On" : "Off") << ", velocity is " << car.velocity << std::endl;
        return true;
    }
    else
    {
        car.velocity -= v;
        std::cout << "Decrease velocity by driver, The velocity is " << car.velocity << ". It is out of Maxvel" << std::endl;
        return false;
    }
}

bool Driver::velup(Car &car, int v)
{

    if (car.velocity + v <= Car::Maxvel)
    {
        car.velocity += v;
        car.velocity += v;
        std::cout << "Increase velocity by driver, mode is " << (car.ison() ? "On" : "Off") << ", velocity is " << car.velocity << std::endl;
        return true;
    }
    else
    {
        std::cout << "Increase velocity by driver, The velocity is " << car.velocity << ". It is out of Maxvel" << std::endl;
        return false;
    }
}

void Driver::setmode(Car &car)
{
    std::cout << "Set the mode of car by driver:" << std::endl;
    if (car.ison())
    {
        std::cout << "The mode of car is:On" << std::endl;
        car.mode = Car::Off;
    }
    else
    {
        std::cout << "The mode of car is:Off" << std::endl;
        car.mode = Car::On;
    }
}

bool Driver::ison(Car &car) const
{
    return car.ison();
}