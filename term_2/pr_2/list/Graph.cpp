#include "Graph.h"

Arc::Arc() : vertex(-1), weight(-1){};
Arc::Arc(int _vertex, int _weight) : vertex(_vertex), weight(_weight){};

Graph::Graph(ifstream &in)
{
    if (!(in >> size)) // Ввод размера списка
    {
        cerr << "In fist line of file must be size of list .Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    try
    { // Выделение памяти под список
        relList = new Arc *[size];
        for (int i = 0; i < size; i++)
            relList[i] = new Arc[size];
    }
    catch (bad_alloc &xa)
    {
        cerr << "Weight list allocation error. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    fill(in); // Заполнение графа из файла
}

Graph::Graph(Graph &gr) : relList(gr.relList), size(gr.size) {}

void Graph::insertNode(int vertex, Arc arc)
{
    int idx;
    // Поиск позиции для вставки
    for (idx = 0; relList[vertex][idx].weight != -1; idx++)
        ;
    relList[vertex][idx] = arc; // Вставка элемента
}

void Graph::fill(ifstream &in)
{
    unsigned short int type;
    in >> type; // Тип представления графа в файле
    // 0 - матрица весов, 1 - список смежности и весов
    string line;
    getline(in, line); // Взять строку из потока
    int row = 0, col = 0, lastCol = 0;

    if (type == 0) // Матрица
    {
        while (getline(in, line)) // Пока есть строки
        {
            stringstream ss(line); // Строковый поток
            int temp;
            while (ss >> temp) // Ввод значения
            {
                if (temp)                            // Если значение не 0
                    insertNode(row, Arc(col, temp)); // Вставить в граф
                col++;
            }

            if (lastCol != 0 && lastCol != col)
            {
                cerr << "Matrix is not square. Exiting..." << endl;
                exit(EXIT_FAILURE);
            }
            lastCol = col;
            col = 0;
            row++;
        }
        if (row != lastCol)
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
            while (ss >> vertex >> weight)            // Ввод вершины и веса дуги
                insertNode(row, Arc(vertex, weight)); // Вставка
            row++;
        }
    }
    else
    {
        cerr << "Unknown file type. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

void Graph::dfsr(int vertex, int sum, char *seen)
{
    // Не рекурсивный случай: найдена вершина на заданном расстоянии
    if (sum == 0)
        seen[vertex] = 1; // Вершина достигнута
    else if (sum > 0)     // Рекурсивный случай
    {
        int idx = 0;
        Arc currVertex = relList[vertex][idx]; // Первая вершина
        while (currVertex.weight != -1)        // Пока есть вершины
        {
            // Рекурсивный вызов для смежной вершины с уменьшением расстояния
            dfsr(currVertex.vertex, sum - currVertex.weight, seen);
            currVertex = relList[vertex][idx++]; // Следующая вершина
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
        delete[] relList[i];
    delete[] relList;
}

ostream &operator<<(ostream &out, Graph &gr)
{
    for (int i = 0; i < gr.size; i++)
    {
        out << i << ": ";
        for (int j = 0; gr.relList[i][j].weight != -1; j++)
            out << '('
                << gr.relList[i][j].vertex
                << ';'
                << gr.relList[i][j].weight
                << ") ";
        out << endl;
    }
    return out;
}