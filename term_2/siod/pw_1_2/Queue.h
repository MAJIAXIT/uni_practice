#ifndef Queue_h
#define Queue_h

#include <iostream>

struct Data // Данные
{
    double priceOne; // Цена одного товара
    Data();          // Конструктор структуры без параметров
    Data(double);    // Конструктор структуры с параметром
};

class Node // Класс узла
{
    Data data;  // Данные
    Node *next; // Указатель на следующий элемент

public:
    Node(Data);           // Конструктор с параметром
    Node();               // Конструктор без параметра
    Node *getNext();      // Геттер следующего элемента
    void setNext(Node *); // Сеттер следующего элемента
    Data getData();       // Геттер для данных
};

class Queue // Класс очереди
{
    Node *head; // Первый элемент
    Node *tail; // Последний элемент

public:
    Queue();                  // Конструктор без параметров
    Queue(Queue &);           // Конструктор с параметром
    void push(Data);          // Метод добавления в конец очереди
    Data pop();               // Метод извлечения первого из очереди
    Data safePop();           // Метод просмотра первого из очереди
    bool isEmpty();           // Метод проверки очередь на пустоту
    bool isFull();            // Метод проверки очереди на заполненность
    Queue operator=(Queue &); // перегрузка оператора присваивания
    ~Queue();                 // Деструктор очереди
};
#endif
