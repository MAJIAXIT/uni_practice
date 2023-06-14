#ifndef SCOOT
#define SCOOT
#include "BaseVehicle.h"

class Scoot : public BaseVehicle
{
public:
    Scoot();
    Scoot(string, double, double, string);
    ~Scoot();
    void ownMethod();
    void showName();
    void start();
    void go(double);
    void fill();
};

#endif