#include <stdio.h>
#include <stdlib.h>
#include "tools.c"

#define ARRAY_SIZE 57
#define ROW 7
#define COLUMN 5

int main()
{
    // Выделение памяти для массива и матрицы
    int *arr = (int *)calloc(sizeof(int), ARRAY_SIZE), **matrix = (int **)malloc(sizeof(int *) * ROW);
    int matrixMinIdx_i = 0, matrixMinIdx_j = 0, arrMinIdx = 0, tempMin, count = 1;

    // Если выделить память не удалось
    if (arr == NULL)
    {
        printf("Error while allocating memory");
        return 1; // Выход из программы с ошибкой
    }

    // Выделение памяти для матрицы. Значение 1 - ошибка, 0 - успех
    if (allocMatrixMemory(matrix, ROW, COLUMN))
        return 1;

    inputArray(arr, ARRAY_SIZE);      // Ввод массива
    inputMatrix(matrix, ROW, COLUMN); // Ввод матрицы

    // Поиск индекса минимального элемента в массиве
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (arr[i] == arr[arrMinIdx]) // Если число уже встречалось 
            count++; // Увеличить счетчик
        if (arr[i] < arr[arrMinIdx])  // Если найдено минимальное 
        {
            arrMinIdx = i; // Запомнить индекс
            count = 1; // Обнулить количество 
        }
    }
    if (count > 1) // Если больше одного минимального 
    {
        printf("Incorrect array: 2 or more minimal values!\n");
        exit(1); // Выход с ошибкой
    }

    count = 1; // Обнуление количества 
    for (int i = 0; i < ROW; i++) // Поиск индекса минимального элемента в матрице
        for (int j = 0; j < COLUMN; j++)
        {
            if (matrix[i][j] == matrix[matrixMinIdx_i][matrixMinIdx_j]) // Если число уже встречалось
                count++; // Увеличить счетчик
            if (matrix[i][j] < matrix[matrixMinIdx_i][matrixMinIdx_j]) // Если найдено
            {
                matrixMinIdx_i = i; // Запомнить индекс строки
                matrixMinIdx_j = j; // Запомнить индекс колонки
                count = 1; // Обнулить количество 
            }
        }

    if (count > 1) // Если больше одного минимального 
    {
        printf("Incorrect matrix: 2 or more minimal values!\n");
        exit(2); // Выход с ошибкой
    }
    // Перестановка минимального элемента массива и матрицы
    tempMin = matrix[matrixMinIdx_i][matrixMinIdx_j];
    matrix[matrixMinIdx_i][matrixMinIdx_j] = arr[arrMinIdx];
    arr[arrMinIdx] = tempMin;

    printArray(arr, ARRAY_SIZE);      // Вывод массива
    printMatrix(matrix, ROW, COLUMN); // Вывод матрицы

    free(arr);                     // Освободить память массива
    freeMatrixMemory(matrix, ROW); // Освободить память матрицы

    return 0; // Выход из программы
}