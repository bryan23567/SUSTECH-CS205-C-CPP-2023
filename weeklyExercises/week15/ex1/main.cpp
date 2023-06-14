
#include "driver.hpp"


int main(int argc, char const *argv[])
{
    Car car;
    Driver driver;

    car.showinfo();
    car.velup(120);
    driver.setmode(car);
    car.showinfo();
    driver.veldown(car, 100);
    car.velup(150);
    return 0;
}
