#ifndef Queue_h
#define Queue_h

#include <iostream>

struct Data
{
    int amount;
    double priceOne;
    Data();
    Data(int, double);
    friend std::istream &operator>>(std::istream &, Data &);
    friend std::ostream &operator<<(std::ostream &, Data &);
};

class Node
{
    Data *data;
    Node *next;

public:
    Node(Data *);
    Node();
    Node *getNext();
    void setNext(Node *);
    Data *getData();
    ~Node();
};

class Queue
{
    Node *head;
    Node *tail;

public:
    Queue();
    Queue(Queue &);
    void push(Data *);
    Data *pop();
    Data safePop();
    bool isEmpty();
    bool isFull();
    ~Queue();
};
#endif