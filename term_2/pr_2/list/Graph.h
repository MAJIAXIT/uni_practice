#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Arc
{
    int vertex;                    // К вершине
    int weight;                    // Вес вершины
    Arc();                         // Конструктор без параметров
    Arc(int _vertex, int _weight); // Конструктор с параметрами
};

class Graph
{
    int size;      // Количество строк списка
    Arc **relList; // Список смежности

public:
    // Конструктор с параметром
    Graph(ifstream &in);
    // Конструктор копирования
    Graph(Graph &gr);
    // Вставка вершины
    void insertNode(int vertex, Arc arc);
    // Заполнение графа из потока
    void fill(ifstream &in);
    // Поиск в глубину
    void dfsr(int vertex, int sum, char *seen);
    // Поиск вершин от from на расстоянии sum
    void findPath(int from, int sum);
    // Деструкторк
    ~Graph();
    // Перегрузка вывода
    friend ostream &operator<<(ostream &out, Graph &gr);
};

#endif