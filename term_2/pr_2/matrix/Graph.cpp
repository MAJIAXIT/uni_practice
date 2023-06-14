#include "Graph.h"

Graph::Graph(ifstream &in)
{
    // Ввод размера матрицы
    if (!(in >> size))
    {
        cerr << "First line of file must be size of matrix. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        weightMatrix = new int *[size];
        for (int i = 0; i < size; ++i)
            weightMatrix[i] = new int[size];
    }
    catch (bad_alloc &xa)
    {
        cerr << "Weight matrix allocation error. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    // Заполнение матрицы из файла
    fill(in);
}

Graph::Graph(Graph &gr) : weightMatrix(gr.weightMatrix), size(gr.size) {}

void Graph::fill(ifstream &in)
{
    unsigned short int type;
    in >> type; // Тип графа в файле
    string line;
    getline(in, line);
    int row = 0, col = 0, lastCol = 0;

    if (type == 0) // Матрица весов
    {
        while (getline(in, line)) // Пока есть строки
        {
            stringstream ss(line);                 // Строковый поток
            while (ss >> weightMatrix[row][col++]) // Ввод вершин
                ;
            if (lastCol != 0 && lastCol != col)
            {
                cerr << "Matrix is not square. Exiting..." << endl;
                exit(EXIT_FAILURE);
            }
            lastCol = col;
            col = 0;
            row++;
        }
        if (row != lastCol - 1)
        {
            cerr << "Matrix is not square. Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (type == 1) // List
    {
        while (getline(in, line)) // Пока есть строки
        {
            stringstream ss(line); // Строковый поток
            int vertex, weight;
            while (ss >> vertex >> weight)          // Ввод вершины и веса
                weightMatrix[row][vertex] = weight; // Вставка в матрицу
            row++;
        }
    }
    else
    {
        cerr << "Unknown file type. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    size = row;
}

int Graph::next(int row, int cur)
{
    while (!weightMatrix[row][++cur] && cur < size)
        ;
    if (cur == size)
        return -1;
    return cur;
}

void Graph::dfsr(int vertex, int sum, char *seen)
{
    // Не рекурсивный случай: найдена вершина на заданном расстоянии
    if (sum == 0)
        seen[vertex] = 1; // Вершина достигнута
    else if (sum > 0)     // Рекурсивный случай
    {
        int idx = 0;
        int cur = next(vertex, -1); // Первая смежная вершина
        while (cur != -1)           // Пока есть смежные
        {
            // Рекурсивный вызов для смежной вершины с уменьшением расстояния
            dfsr(cur, sum - weightMatrix[vertex][cur], seen);
            cur = next(vertex, cur); // Следующая вершина
        }
    }
}

void Graph::findPath(int from, int sum)
{
    char *seen; // Хэш массив достигнутых вершин
    try
    {
        seen = new char[size];
        for (int i = 0; i < size; i++)
            seen[i] = 0;
    }
    catch (bad_alloc &xa)
    {
        cerr << "Memory allocation error. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    dfsr(from, sum, seen); // Поиск в глубину

    // Вывод результата
    cout << "Vertices to which there is a path of length " << sum << " from the vertex " << from << ':' << endl;
    for (int i = 0; i < size; i++)
        if (seen[i])
            cout << i << '\t';

    delete[] seen;
}

Graph::~Graph()
{
    for (int i = 0; i < size; i++)
        delete[] weightMatrix[i];
    delete[] weightMatrix;
}

ostream &operator<<(ostream &out, Graph &gr)
{
    for (int i = 0; i < gr.size; i++)
    {
        for (int j = 0; j < gr.size; j++)
            out << gr.weightMatrix[i][j] << '\t';
        out << endl;
    }
    return out;
}