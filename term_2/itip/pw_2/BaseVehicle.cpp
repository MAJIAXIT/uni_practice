#include "BaseVehicle.h"

BaseVehicle::BaseVehicle()
{
    engineSize = 0.0;
    maxSpeed = 0.0;
    cout << "BaseVehicle constructed without parameters." << endl;
}

BaseVehicle::BaseVehicle(string _name, double _engineSize, double _maxSpeed, string _bodyType)
{
    name = _name;
    engineSize = _engineSize;
    maxSpeed = _maxSpeed;
    bodyType = _bodyType;
    cout << "BaseVehicle constructed with parameters." << endl;
}

string BaseVehicle::getName() { return name; }
double BaseVehicle::getEngineSize() { return engineSize; }
double BaseVehicle::getMaxSpeed() { return maxSpeed; }
string BaseVehicle::getBodyType() { return bodyType; }

void BaseVehicle::setName(string _name) { name = _name; }
void BaseVehicle::setBodyType(string _bodyType) { bodyType = _bodyType; }
void BaseVehicle::setEngineSize(double enSize) { engineSize = enSize; }
void BaseVehicle::setMaxSpeed(double speed) { maxSpeed = speed; }

std::istream &operator>>(std::istream &in, BaseVehicle &vehicle)
{
    cout << "Enter vehicle name: ";
    getline(in >> ws, vehicle.name);
    cout << "Enter vehicle engine size: ";
    while (!(in >> vehicle.engineSize))
    {
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter vehicle max speed: ";
    while (!(in >> vehicle.maxSpeed))
    {
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter vehicle body type: ";
    getline(in >> ws, vehicle.bodyType);
    return in;
}

std::ostream &operator<<(std::ostream &out, BaseVehicle &veh)
{
    out << "Object name: " << typeid(veh).name() << endl
        << "Fields:" << endl
        << "string name\t\tvalue: " << veh.name << endl
        << "double engineSize\tvalue: " << veh.engineSize << endl
        << "double maxSpeed\t\tvalue: " << veh.maxSpeed << endl
        << "string bodyType\t\tvalue: " << veh.bodyType << endl;
    return out;
}