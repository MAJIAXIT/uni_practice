#ifndef CART
#define CART
#include "BaseVehicle.h"

class Cart : public BaseVehicle
{
public:
    Cart();
    Cart(string, double, double, string);
    ~Cart();
    void ownMethod();
    void showName();
    void start();
    void go(double);
    void fill();
};

#endif