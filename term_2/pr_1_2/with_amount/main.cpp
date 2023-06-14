#include "Queue.h"

using namespace std;

void sell(Queue *queue)
{
    int amount = 0;
    if (queue->isEmpty())
        cout << "Stock is empty." << endl;
    else
    {
        cout << "Enter amount: ";
        while (!(cin >> amount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Incorrect data, please enter positive values." << endl;
            cout << "Enter amount: ";
        }

        Data *data;
        int totalAm = 0;
        double totalPr = 0;

        while (!(queue->isEmpty()) && queue->safePop().amount < amount)
        {
            data = queue->pop();
            amount -= data->amount;
            totalAm += data->amount;
            totalPr += data->amount * data->priceOne;
        }
        if (queue->isEmpty() && amount > 0)
        {
            cout << "Stock is empty" << endl;
            cout << "Not sold: " << amount << endl;
        }
        else
        {
            data = &(queue->safePop());
            data->amount -= amount;
            if (data->amount == 0)
                queue->pop();
            totalAm += amount;
            totalPr += amount *= data->priceOne;
        }
        cout << "Total sold: " << totalAm << " total price: " << totalPr * 1.2 << endl;
    }
}

void buy(Queue *queue)
{
    Data *data = new Data(-1, -1);
    while (!(cin >> *data))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect data, please enter positive values." << endl;
    }

    queue->push(data);
    cout << "Amount: " << data->amount << " Price: " << data->priceOne << " Total: " << data->priceOne * data->amount << endl;
}

int main(void)
{
    Queue *queue = new Queue;
    char ans;
    do
    {
        cout << "To exit enter 'x'" << endl;
        cout << "Enter prefix: s - sell, r - buy: " << endl;
        cin >> ans;
        switch (ans)
        {
        case 'r':
            buy(queue);
            break;
        case 's':
            sell(queue);
            break;
        }
    } while (ans != 'x');
    delete queue;
    return 0;
}