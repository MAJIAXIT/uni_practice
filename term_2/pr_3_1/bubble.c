#include "sorting.h"

void bubble(int *array, size_t size, 
            unsigned *mainOp, unsigned *helpOp, size_t *memory) {
    register int left, right, temp;
    *memory += sizeof(left) + sizeof(right) + sizeof(temp);
    
    for (left = 1; ++(*helpOp), left < size; left++) {
        for (right = size - 1; ++(*helpOp), right >= left; right--) {
            if (++(*mainOp), array[right - 1] > array[right]) {
                temp = array[right];
                array[right] = array[right - 1];
                array[right - 1] = temp;
            }
        }
    }
}