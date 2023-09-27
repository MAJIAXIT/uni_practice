// #include "arrRND.h"
// #include "matrixRND.h"
// #include <stdio.h>
// #include <stdlib.h>

// #define MATRIX_ROW 9
// #define MATRIX_COL 11
// #define ARRLEN 38

// int main() {
//     int **matrix = (int **)malloc(sizeof(int *) * MATRIX_ROW),
//         *arr = (int *)malloc(sizeof(int) * ARRLEN);
//     int count;

//     for (int i = 0; i < MATRIX_ROW; i++)
//         matrix[i] = (int *)malloc(sizeof(int) * MATRIX_COL);

//     int ans = -1;
//     while (ans != 0) {
//         printf("1. Array\n");
//         printf("2. Matrix\n");
//         printf("0. Exit\n:");
//         scanf("%d", &ans);

//         count = 0;
//         if (ans == 1) {
//             randomizeArray(arr, ARRLEN);
//             count = getCountRemaindersInArray(arr, ARRLEN);
//             printf("Count x in array: x %% 5 = 1: %d\n", count);
//         }
//         if (ans == 2) {
//             randomizeMatrix(matrix, MATRIX_ROW, MATRIX_COL);
//             count = getCountRemaindersInMatrix(matrix, MATRIX_ROW, MATRIX_COL);
//             printf("Count x in matrix: x %% 5 = 1: %d\n", count);
//         }
//     }

//     free(arr);
//     for (int i = 0; i < MATRIX_ROW; i++)
//         free(matrix[i]);
//     free(matrix);

//     exit(EXIT_SUCCESS);
// }