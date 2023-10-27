#include "matrixRND.h"

void randomizeMatrix(int **matrix, int row, int col) {
    srand(time(NULL));
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++)
            matrix[r][c] = rand() % RANGE - RANGE / 2;
    }
}

int getCountRemaindersInMatrix(int **matrix, int row, int col) {
    int count = 0;
    for (int r = 0; r < row; r++)
        for (int c = 0; c < col; c++)
            if (matrix[r][c] % 5 == 1)
                count++;
    return count;
}
