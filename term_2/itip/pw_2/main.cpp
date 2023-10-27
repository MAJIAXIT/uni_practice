#include "BaseVehicle.h"
#include "Car.h"
#include "Tank.h"
#include "Scoot.h"
#include "Cart.h"

#define MAX_OBJECTS_COUNT 10

// Функция создания нового объекта
void createObject(BaseVehicle **objs, unsigned int &objsCount)
{
    unsigned short int ans;
    cout << "Enter type of object: " << endl
         << "1. Car" << endl
         << "2. Tank" << endl
         << "3. Scoot" << endl
         << "4. Cart" << endl;
    cin >> ans;
    try // Выделение памяти под заданный тип
    {
        switch (ans)
        {
        case 1:
            objs[objsCount] = new Car;
            break;
        case 2:
            objs[objsCount] = new Tank;
            break;
        case 3:
            objs[objsCount] = new Scoot;
            break;
        case 4:
            objs[objsCount] = new Cart;
            break;
        }
    }
    catch (bad_alloc &xa)
    {
        cout << "Memory allocation exception occured.\nExiting..." << endl;
        exit(EXIT_FAILURE);
    }
    // Ввод объекта заданного типа
    while (!(cin >> *objs[objsCount++]))
        ;
}

// Вызов функции базового класса для всех объектов
void baseFunctionCall(BaseVehicle **objs, unsigned int &objsCount)
{
    unsigned short int ans;
    cout << "Enter function to execute from all objects: " << endl
         << "1. showName" << endl
         << "2. start" << endl
         << "3. go" << endl
         << "4. fill" << endl;
    cin >> ans;
    switch (ans)
    {
    case 1:
        for (int i = 0; i < objsCount; i++)
            objs[i]->showName();
        break;
    case 2:
        for (int i = 0; i < objsCount; i++)
            objs[i]->start();
        break;
    case 3:
        int dist;
        cout << "Enter distance: ";
        while (!(cin >> dist))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        for (int i = 0; i < objsCount; i++)
            objs[i]->go(dist);
        break;
    case 4:
        for (int i = 0; i < objsCount; i++)
            objs[i]->fill();
        break;
    }
}

// Вызов уникальной функции класса для всех объектов класса
void objectFunctionCall(BaseVehicle **objs, unsigned int &objsCount)
{
    unsigned short int ans;
    cout << "Enter objects type to execute it function: " << endl
         << "1. Car" << endl
         << "2. Tank" << endl
         << "3. Scoot" << endl
         << "4. Cart" << endl;
    cin >> ans;
    switch (ans)
    {
    case 1:
        for (int i = 0; i < objsCount; i++)
            if (typeid(*objs[i]) == typeid(Car))           // Если найден объект нужного типа
                dynamic_cast<Car *>(objs[i])->ownMethod(); // Вызвать его собственный метод
        break;
    case 2:
        for (int i = 0; i < objsCount; i++)
            if (typeid(*objs[i]) == typeid(Tank))
                dynamic_cast<Tank *>(objs[i])->ownMethod();
        break;
    case 3:
        for (int i = 0; i < objsCount; i++)
            if (typeid(*objs[i]) == typeid(Scoot))
                dynamic_cast<Scoot *>(objs[i])->ownMethod();
        break;
    case 4:
        for (int i = 0; i < objsCount; i++)
            if (typeid(*objs[i]) == typeid(Cart))
                dynamic_cast<Cart *>(objs[i])->ownMethod();
        break;
    }
}

int main(int argc, char **argv)
{
    BaseVehicle **objs;
    try
    {
        objs = new BaseVehicle *[argc > 1 ? atoi(*++argv) : MAX_OBJECTS_COUNT];
    }
    catch (bad_alloc &xa)
    {
        cout << "Memory allocation exception occured.\nExiting..." << endl;
        exit(EXIT_FAILURE);
    }

    unsigned int objsCount = 0;
    unsigned short int ans = 0;
    while (ans < 5)
    {
        cout << endl
             << "Enter command" << endl
             << "1. Create object" << endl
             << "2. Show objects" << endl
             << "3. All object functions call" << endl
             << "4. Specifyed object function call" << endl
             << "5. Exit" << endl;
        cin >> ans;
        switch (ans)
        {
        case 1:
            createObject(objs, objsCount);
            break;
        case 2:
            if (objsCount > 0)
                for (int i = 0; i < objsCount; i++)
                    cout << *objs[i] << endl;
            else
                cout << "There are no objects yet." << endl;
            break;
        case 3:
            if (objsCount > 0)
                baseFunctionCall(objs, objsCount);
            else
                cout << "There are no objects yet." << endl;
            break;
        case 4:
            if (objsCount > 0)
                objectFunctionCall(objs, objsCount);
            else
                cout << "There are no objects yet." << endl;
            break;
        }
    }
    for (int i = 0; i < objsCount; i++)
        delete objs[i];
    delete[] objs;
    exit(EXIT_SUCCESS);
}