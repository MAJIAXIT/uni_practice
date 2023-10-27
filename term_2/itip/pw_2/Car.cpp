#include "Car.h"

Car::Car() : BaseVehicle()
{
    cout << "Car constructor without parameters." << endl;
}

Car::Car(string name, double engineSize, double maxSpeed, string bodyType) : BaseVehicle(name, engineSize, maxSpeed, bodyType)
{
    cout << "Car constructor with parameters." << endl;
}

void Car::ownMethod()
{
    cout << "Own Car with name " << getName() << " method called." << endl;
}

Car::~Car()
{
    cout << "Car object with name " << getName() << " destructor is called." << endl;
}

void Car::showName()
{
    cout << "class Car with name " << getName() << " derived from BaseVehicle showName." << endl;
}

void Car::start()
{
    cout << "Car " << getName() << " is starting..." << endl;
}

void Car::go(double dist)
{
    cout << "Car " << getName() << " is going on distance: " << dist << "..." << endl;
}

void Car::fill()
{
    cout << "Car " << getName() << " is filling..." << endl;
}