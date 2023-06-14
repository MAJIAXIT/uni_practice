#ifndef TANK
#define TANK
#include "BaseVehicle.h"

class Tank : public BaseVehicle
{
public:
    Tank();
    Tank(string, double, double, string);
    ~Tank();
    void ownMethod();
    void showName();
    void start();
    void go(double);
    void fill();
};

#endif