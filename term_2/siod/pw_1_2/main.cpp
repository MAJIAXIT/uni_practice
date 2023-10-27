#include "Queue.h"

using namespace std;

void sell(Queue *queue)
{
    int amount = -1;
    if (queue->isEmpty())                  // Если очередь пуста
        cout << "Stock is empty." << endl; // Вывести сообщение о пустоте
    else                                   // Иначе
    {
        cout << "Enter amount: ";
        while (!(cin >> amount) || amount < 0) // Ввод количества на продажу пока ввод не корректен
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Incorrect data, please enter positive values." << endl;
            cout << "Enter amount: ";
        }

        Data data;
        int totalAm = 0, lastAm = 0;
        double totalPr = 0, lastPr;

        lastPr = queue->safePop().priceOne;         // Запомнить цену первого
        while (!(queue->isEmpty()) && amount-- > 0) // Пока не продано нужное количество и очередь не пуста
        {
            data = queue->pop();      // Взять элемент из очереди
            totalAm++;                // Инкремент количества проданных
            totalPr += data.priceOne; // Увеличение итоговой суммы продажи
            lastAm++;                 // Инкремент количества проданных с текущей ценой

            if (data.priceOne != lastPr) // Если цена текущего элемента отличается от предыдущего
            {
                cout << --lastAm << " items by " << lastPr * 1.2 << " each" << endl; // Вывести старую позицию товара
                lastAm = 1;                                                          // Обнулить количество проданных с текущей ценой
                lastPr = data.priceOne;                                              // Запомнить цену товара
            }
        }
        cout << lastAm << " items by " << lastPr * 1.2 << " each" << endl;
        if (queue->isEmpty() && amount > 0) // Если очередь пуста, но не продано заданное количество
        {
            // Вывод сообщения и количества недостающего товара
            cout << "Stock is empty" << endl;
            cout << "Not sold: " << amount << endl;
        }
        // Сообщение с количеством проданного итого
        cout << "Total sold: " << totalAm << " total price: " << totalPr * 1.2 << endl;
    }
}

void buy(Queue *queue)
{
    int amount = -1, tmp;
    double priceOne = -1;

    cout << "Enter amount and price of one:" << endl;
    while (!(cin >> amount >> priceOne) || amount < 0 || priceOne < 0) // Вводить пока ввод не корректен
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect data, please enter positive values." << endl;
    }
    tmp = amount; // Запомнить количесво товара

    // Добавить в очередь введенное количество товаров с введенной ценой
    while (tmp-- > 0)
        queue->push(Data(priceOne));

    // Сообщение о покупке
    cout << "Amount: " << amount << " Price: " << priceOne << " Total: " << priceOne * amount << endl;
}

int main(void)
{
    Queue *queue = new Queue; // Создание очереди
    char ans;
    do
    {
        cout << "To exit enter 'x'" << endl;
        cout << "Enter prefix: s - sell, r - buy: " << endl;
        cin >> ans;
        switch (ans)
        {
        case 'r':
            buy(queue); // Купить
            break;
        case 's':
            sell(queue); // Продать
            break;
        }
    } while (ans != 'x');
    delete queue; // Очиста очереди

    return 0;
}
