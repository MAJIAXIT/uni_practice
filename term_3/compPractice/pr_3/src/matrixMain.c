#include "matrixRND.h"
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_ROW 9
#define MATRIX_COL 11

int main() {
    int **matrix = (int **)malloc(sizeof(int *) * MATRIX_ROW);
    int count = 0;

    for (int i = 0; i < MATRIX_ROW; i++)
        matrix[i] = (int *)malloc(sizeof(int) * MATRIX_COL);

    randomizeMatrix(matrix, MATRIX_ROW, MATRIX_COL);
    count = getCountRemaindersInMatrix(matrix, MATRIX_ROW, MATRIX_COL);

    printf("Count x in matrix: x %% 5 = 1: %d\n", count);

    for (int i = 0; i < MATRIX_ROW; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}