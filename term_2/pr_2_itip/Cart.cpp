#include "Cart.h"

Cart::Cart() : BaseVehicle()
{
    cout << "Cart constructor without parameters." << endl;
}

Cart::Cart(string name, double engineSize, double maxSpeed, string bodyType) : BaseVehicle(name, engineSize, maxSpeed, bodyType)
{
    cout << "Cart constructor with parameters." << endl;
}

void Cart::ownMethod()
{
    cout << "Own Cart with name " << getName() << " method called." << endl
         << "Yes it is a vehicle too:)" << endl;
}

Cart::~Cart()
{
    cout << "Cart object with name " << getName() << " destructor is called." << endl;
}

void Cart::showName()
{
    cout << "class Cart with name " << getName() << " derived from BaseVehicle showName." << endl;
}

void Cart::start()
{
    cout << "Cart " << getName() << " is starting..." << endl;
}

void Cart::go(double dist)
{
    cout << "Cart " << getName() << " is going on distance: " << dist << "..." << endl;
}

void Cart::fill()
{
    cout << "Cart " << getName() << " is filling..." << endl;
}