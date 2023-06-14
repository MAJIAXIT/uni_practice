#ifndef VEHICLE_BASE
#define VEHICLE_BASE
#include <iostream>
#include <string>
#include <limits>

using namespace std;

class BaseVehicle // Базовый класс
{
    string name;
    double engineSize;
    double maxSpeed;
    string bodyType;

public:
    BaseVehicle();                               // Конструктор
    BaseVehicle(string, double, double, string); // Конструктор с параметрами
    // Геттеры
    string getName();
    double getEngineSize();
    double getMaxSpeed();
    string getBodyType();
    // Сеттеры
    void setName(string);
    void setEngineSize(double);
    void setMaxSpeed(double);
    void setBodyType(string);
    // Виртуальные функции для реализации вне базового класса

    virtual void showName() = 0; // Вывести имя объекта
    virtual void start() = 0;    // Старт
    virtual void go(double) = 0; // Поехать на расстояние
    virtual void fill() = 0;     // Заправится
    // Перегрузка операторов ввода и вывода
    friend std::istream &operator>>(std::istream &, BaseVehicle &);
    friend std::ostream &operator<<(std::ostream &, BaseVehicle &);
};

#endif