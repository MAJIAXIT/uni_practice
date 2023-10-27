#ifndef CAR
#define CAR
#include "BaseVehicle.h"

class Car : public BaseVehicle
{
public:
    Car();
    Car(string, double, double, string);
    ~Car();
    void ownMethod();
    void showName();
    void start();
    void go(double);
    void fill();
};

#endif