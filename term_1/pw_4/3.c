#include <stdlib.h>
#include <stdio.h>

#define ROW 8 // Количество рядов
#define COLUMN 5 // Количество колонок

void _swap(int line[], int i, int j); // Функция меняющая местами элементы массива. Принимает массив, элементы, которые необходимо поменять местами
void _qsort(int line[], int left, int right); // Функция быстрой сортировки массива чисел типа int. Принимает массив, индекс левого элемента массива и правого элемента

int main()
{
    int matrix[ROW][COLUMN]; // матрица 8x5
    int row = 0, column = 0; // строка, колонка
    
    printf("Enter matrix %dx%d:\n", ROW, COLUMN);
    
    while (row < ROW) // Пока строка меньше количества строк
    {
        column = 0; // Первая колонка
        // printf("Enter %d row: ", row + 1);
        while (column < COLUMN) // Пока колонка меньше количества колонок
        {
            scanf("%d", &matrix[row][column]); // Запись значения в матрицу
            column++; // Следующая колонка
        }
        row++; // Следующий ряд
    }

    for (int _row = 0; _row < ROW; _row++) // Для каждого ряда матрицы
        _qsort(matrix[_row], 0, COLUMN - 1); // Сортировка ряда

    printf("====================\n"); // Разделитель
    for (int _row = 0; _row < ROW; _row++) // Для каждого ряда матрицы
    {
        for (int _column = 0; _column < COLUMN; _column++) // Для каждой колонки ряда матрицы
            printf("%3d ", matrix[_row][_column]); // Вывод значения колонки матрицы
        printf("\n"); // Вывод пустой строки
    }
    
    return 0;
}

void _qsort(int line[], int left, int right)
{
    int i, last;
    if (left >= right) // Ничего не делается, если в массиве менее двух элементов
        return;
    _swap(line, left, (left + right) / 2); // Поместить левый элемент в середину массива
    last = left; // Запомнить середину как опорный элемент
    for (i = left + 1; i <= right; ++i) // Пока следующий элемент больше предыдущего
        if (line[i] < line[left]) // Если элемент массива меньше предыдущего
            _swap(line, ++last, i); // Поменять элементы местами
    _swap(line, left, last); // Поменять средний элемент с последним
    _qsort(line, left, last - 1); // Рекурсивное обращение с предпоследним элементом
    _qsort(line, last + 1, right); // Рекурсивное обращение со следующим от середины элементом
}

void _swap(int line[], int i, int j)
{
    int temp; // Переменная для хранения значения
    temp = line[i]; // Запомнить i-ый элемент
    line[i] = line[j]; // Поменять местами значения элементов
    line[j] = temp; // Поместить в j-ый элемент запомненное значение 
}