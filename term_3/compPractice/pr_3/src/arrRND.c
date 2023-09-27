#include "arrRND.h"

void randomizeArray(int *arr, int arrlen) {
    srand(time(NULL));
    for (int i = 0; i < arrlen; i++)
        arr[i] = rand() % RANGE - RANGE / 2;
}

int getCountRemaindersInArray(int *arr, int arrlen) {
    int count = 0;
    for (int i = 0; i < arrlen; i++)
        if (arr[i] % 5 == 1)
            count++;
    return count;
}
