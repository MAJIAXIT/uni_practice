#include <stdio.h>
#include <stdlib.h>
#include "tools.c"

#define A_ROW 6
#define A_COLUMN 9
#define B_ROW 6
#define B_COLUMN 7
#define A_DEL_VAL 1
#define B_DEL_VAL 0

int deleteRowByEntry(int **, int, int, int);

int main()
{
    int **matrix_a = (int **)malloc(sizeof(int *) * A_ROW), **matrix_b = (int **)malloc(sizeof(int *) * B_ROW);
    int aRowCount, bRowCount;

    // Выделение памяти. Если память не выделилась, выйти из программы
    if (allocMatrixMemory(matrix_a, A_ROW, A_COLUMN))
        return 1;
    if (allocMatrixMemory(matrix_b, B_ROW, B_COLUMN))
        return 1;

    // Ввод матрицы
    inputMatrix(matrix_a, A_ROW, A_COLUMN);
    inputMatrix(matrix_b, B_ROW, B_COLUMN);

    // Удаление строк из матрицы по вхождению числа
    aRowCount = deleteRowByEntry(matrix_a, A_ROW, A_COLUMN, A_DEL_VAL);
    bRowCount = deleteRowByEntry(matrix_b, B_ROW, B_COLUMN, B_DEL_VAL);

    // Вывод матриц
    printMatrix(matrix_a, aRowCount, A_COLUMN);
    printMatrix(matrix_b, bRowCount, B_COLUMN);

    // Освобождение памяти матриц
    freeMatrixMemory(matrix_a, aRowCount);
    freeMatrixMemory(matrix_b, bRowCount);
    return 0;
}

// Удаление строки по вхождению
int deleteRowByEntry(int **matrix, int rowCount, int colCount, int delVal)
{
    int *temp, i, j, row = rowCount;
    // Для всех строк матрицы b
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < colCount; j++)  // Для всех колонок
            if (matrix[i][j] == delVal) // Если найден ноль
            {
                // Сдвинуть строку в конец матрицы
                for (int curr = i; curr < row - 1; curr++)
                {
                    temp = matrix[curr];
                    matrix[curr] = matrix[curr + 1];
                    matrix[curr + 1] = temp;
                }
                row--;             // Количество строк матрицы b
                free(matrix[row]); // Освободить память последней строки
                i--;               // Проверяем индекс текущей строки из-за смещения
                break;
            }
    }
    return row; // Количество строк в матрице после смещений
}