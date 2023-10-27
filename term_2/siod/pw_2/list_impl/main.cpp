#include "Graph.h"

int main(int argc, char **argv)
{
    // Открыть файл с именем из аргументов или константы
    ifstream in(argc > 1 ? *++argv : "matrix_graph.txt");
    if (!in)
    {
        cerr << "Cannot open file: " << (argc > 1 ? *argv : "matrix_graph.txt") << endl;
        exit(EXIT_FAILURE);
    }

    Graph graph(in);       // Создание графа из данных файла
    cout << graph << endl; // Вывод графа

    int root, len;
    cout << "Enter root: ";
    cin >> root;
    cout << "Enter len: ";
    cin >> len;
    graph.findPath(root, len); // Поиск вершин на заданном расстоянии

    in.close();
    exit(EXIT_SUCCESS);
}