#ifndef SORTING
#define SORTING
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble(int *array, size_t size, 
            unsigned *mainOp, unsigned *helpOp, size_t *memory);
void bubbleFixed(int *array, size_t size, 
                 unsigned *mainOp, unsigned *helpOp, size_t *memory);
void shaker(int *array, size_t size, 
            unsigned *mainOp, unsigned *helpOp, size_t *memory);
void quicksort(int *array, size_t size, 
               unsigned *mainOp, unsigned *helpOp, size_t *memory);

#endif