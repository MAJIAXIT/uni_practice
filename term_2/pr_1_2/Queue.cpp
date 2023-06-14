#include "Queue.h"

Data::Data() {}

Data::Data(double p) : priceOne(p) {}

Node::Node(Data data) : data(data), next(nullptr) {}

Node::Node() : next(nullptr) {}

Node *Node::getNext()
{
    return next;
}

void Node::setNext(Node *node)
{
    next = node;
}

Data Node::getData()
{
    return data;
}

Queue::Queue() : head(nullptr), tail(nullptr) {}

Queue::Queue(Queue &q)
{
    Node *tmp = q.head;
    while (tmp != nullptr) // Пока не найден последний элемент
    {
        if (isFull()) // Если очередь полна
        {
            while (head != nullptr) // Пока первый элемент существует
            {
                tmp = head;
                head = head->getNext(); // Первый элемент равен следующему
                delete tmp;             // Очистить бывший первый элемент
            }
            tmp = nullptr;
            std::cout << "Error: copy constructor: memory is full." << std::endl;
        }
        else // Иначе
        {
            push(tmp->getData()); // Добавть элемент в конец очереди
            tmp = tmp->getNext(); // Получить следующий элемент
        }
    }
}

void Queue::push(Data data)
{
    Node *tmp = new (std::nothrow) Node(data);
    if (tmp == nullptr)
    {
        std::cout << "Memory is full." << std::endl;
        return;
    }
    if (head == nullptr)   // Если очередь пуста
        head = tail = tmp; // Первый элемент равен последнему равен введенному
    else
    {
        tail->setNext(tmp); // Добавить элемент в конец
        tail = tmp;         // Запомнить последний элемент
    }
}

Data Queue::pop(void)
{
    if (isEmpty()) // Если очередь пуста
    {
        std::cout << "Queue is empty.";
        return Data(0); // Вернуть пустой элемент
    }
    Data d = head->getData();    // Взять первый элемент
    Node *tmp = head->getNext(); // Запомнить следующий после первого
    delete head;                 // Удалить первый
    head = tmp;                  // Следующий после первого теперь первый
    return d;                    // Вернуть данные удаленного
}

Data Queue::safePop(void)
{
    return head->getData();
}

bool Queue::isEmpty(void)
{
    return head == nullptr;
}

bool Queue::isFull(void)
{
    Node *tmp = new (std::nothrow) Node;
    if (tmp == nullptr)
        return true;
    delete tmp;
    return false;
}

Queue::~Queue()
{
    Node *tmp;
    while (head != nullptr) // Пока существует первый элемент
    {
        tmp = head;             // Запомнить первый элемент
        head = head->getNext(); // Первый элемент равен следующему
        delete tmp;             // Очистить бывший первый элемент
    }
}

Queue Queue::operator=(Queue &q)
{
    if (!isEmpty())
    { // проверка, есть ли в очереди какие-либо иэлементы и их очистка
        while (head != nullptr)
        {
            Node *tmp = head;
            head = head->getNext();
            delete tmp;
        }
    }
    Node *tmp = q.head;
    while (tmp != nullptr)
    {
        if (isFull())
        { // проверка на заполненность и удаление элементов, в случае нехватки памяти
            while (head != nullptr)
            {
                tmp = head;
                head = head->getNext();
                delete tmp;
            }
            tmp = nullptr;
        }
        else
        { // добавление элемета в конец очереди
            push(tmp->getData());
            tmp = tmp->getNext();
        }
    }
    return *this;
}