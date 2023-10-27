#include "Scoot.h"

Scoot::Scoot() : BaseVehicle()
{
    cout << "Scoot constructor without parameters." << endl;
}

Scoot::Scoot(string name, double engineSize, double maxSpeed, string bodyType) : BaseVehicle(name, engineSize, maxSpeed, bodyType)
{
    cout << "Scoot constructor with parameters." << endl;
}

void Scoot::ownMethod()
{
    cout << "Own Scoot with name " << getName() << " method called." << endl
         << "Scoot is great vehicle to travel in concrete jungles." << endl;
}

Scoot::~Scoot()
{
    cout << "Scoot object with name " << getName() << " destructor is called." << endl;
}

void Scoot::showName()
{
    cout << "class Scoot with name " << getName() << " derived from BaseVehicle showName." << endl;
}

void Scoot::start()
{
    cout << "Scoot " << getName() << " is starting..." << endl;
}

void Scoot::go(double dist)
{
    cout << "Scoot " << getName() << " is going on distance: " << dist << "..." << endl;
}

void Scoot::fill()
{
    cout << "Scoot " << getName() << " is filling..." << endl;
}