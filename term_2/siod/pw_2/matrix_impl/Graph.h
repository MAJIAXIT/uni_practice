#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Graph
{
    int size;           // Размер матрицы
    int **weightMatrix; // Матрица весов

public:
    // Конструктор с параметром
    Graph(ifstream &in);
    // Конструктор копирования
    Graph(Graph &gr);
    // Заполнение графа из потока
    void fill(ifstream &in);
    // Поиск в глубину
    void dfsr(int vertex, int sum, char *seen);
    // Поиск вершин от from на расстоянии sum
    void findPath(int from, int sum);
    // Поиск следующей смежной вершины
    int next(int row, int curr);
    // Деструктор
    ~Graph();
    // Перегрузка ввода
    friend ostream &operator<<(ostream &out, Graph &gr);
};

#endif