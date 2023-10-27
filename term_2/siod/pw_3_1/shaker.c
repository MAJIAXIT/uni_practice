#include "sorting.h"

void shaker(int *array, size_t size, 
            unsigned *mainOp, unsigned *helpOp, size_t *memory) {
    register int left = 1, right = size - 1, temp, idx, pmLast;
    *memory += sizeof(left) + sizeof(right) + sizeof(temp) + sizeof(idx) +
               sizeof(pmLast);
    do {
        for (idx = right; (*helpOp)++, idx >= left; idx--) {
            if ((*mainOp)++, array[idx - 1] > array[idx]) {
                temp = array[idx - 1];
                array[idx - 1] = array[idx];
                array[idx] = temp;
                pmLast = idx;
            }
        }
        left = pmLast;

        for (idx = left; (*helpOp)++, idx <= right; idx++) {
            if ((*mainOp)++, array[idx - 1] > array[idx]) {
                temp = array[idx - 1];
                array[idx - 1] = array[idx];
                array[idx] = temp;
                pmLast = idx;
            }
        }
        right = pmLast - 1;
    } while ((*helpOp)++, left < right);
}