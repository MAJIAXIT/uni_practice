#include "Queue.h"

Data::Data() {}

Data::Data(int a, double p) : amount(a), priceOne(p) {}

std::istream &operator>>(std::istream &in, Data &data)
{
    std::cout << "priceOne: ";
    in >> data.priceOne;
    return in;
}

std::ostream &operator<<(std::ostream &out, Data &data)
{
    out << " priceOne: " << data.priceOne;
    return out;
}

Node::Node(Data *data) : data(data), next(nullptr) {}

Node::Node() : next(nullptr) {}

Node *Node::getNext()
{
    return next;
}

void Node::setNext(Node *node)
{
    next = node;
}

Data *Node::getData()
{
    return data;
}

Node::~Node()
{
    delete data;
}

Queue::Queue() : head(nullptr), tail(nullptr) {}

Queue::Queue(Queue &q)
{
    Node *tmp = q.head;
    while (tmp != nullptr)
    {
        if (isFull())
        {
            while (head != nullptr)
            {
                tmp = head;
                head = head->getNext();
                delete tmp;
            }
            tmp = nullptr;
            std::cout << "Error: copy constructor: memory is full." << std::endl;
        }
        else
        {
            push(tmp->getData());
            tmp = tmp->getNext();
        }
    }
}

void Queue::push(Data *data)
{
    Node *tmp = new (std::nothrow) Node(data);
    if (head == nullptr)
        head = tail = tmp;
    else
    {
        tail->setNext(tmp);
        tail = tmp;
    }
}

Data *Queue::pop(void)
{
    if (isEmpty())
    {
        std::cout << "Queue is empty.";
        return nullptr;
    }
    Data *d = head->getData();
    Node *tmp = head->getNext();
    delete head;
    head = tmp;
    return d;
}

Data Queue::safePop(void)
{
    return *(head->getData());
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
    while (head != nullptr)
    {
        tmp = head;
        head = head->getNext();
        delete tmp;
    }
}