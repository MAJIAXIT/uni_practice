#include "Tank.h"

Tank::Tank() : BaseVehicle()
{
    cout << "Tank constructor without parameters." << endl;
}

Tank::Tank(string name, double engineSize, double maxSpeed, string bodyType) : BaseVehicle(name, engineSize, maxSpeed, bodyType)
{
    cout << "Tank constructor with parameters." << endl;
}

void Tank::ownMethod()
{
    cout << "Own Tank with name " << getName() << " method called." << endl
         << "It can shoot btw... PIU... PIU..." << endl;
}

Tank::~Tank()
{
    cout << "Tank object with name " << getName() << " destructor is called." << endl;
}

void Tank::showName()
{
    cout << "class Tank with name " << getName() << " derived from BaseVehicle showName." << endl;
}

void Tank::start()
{
    cout << "Tank " << getName() << " is starting..." << endl;
}

void Tank::go(double dist)
{
    cout << "Tank " << getName() << " is going on distance: " << dist << "..." << endl;
}

void Tank::fill()
{
    cout << "Tank " << getName() << " is filling..." << endl;
}