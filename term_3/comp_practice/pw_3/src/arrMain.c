#include "arrRND.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRLEN 38

int main() {
    int *arr = (int *)malloc(sizeof(int) * ARRLEN);
    int count = 0;

    randomizeArray(arr, ARRLEN);
    count = getCountRemaindersInArray(arr, ARRLEN);
    printf("Count x in array: x %% 5 = 1: %d\n", count);

    free(arr);
    
    return 0;
}