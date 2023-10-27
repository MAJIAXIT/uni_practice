#include "sorting.h"

void bubbleFixed(int *array, size_t size, 
                 unsigned *mainOp, unsigned *helpOp, size_t *memory) {
    register int left = 1, right, temp, pmLast;
    *memory += sizeof(left) + sizeof(right) + sizeof(temp) + sizeof(pmLast);
    do {
        pmLast = 0;
        for (right = size - 1; (*helpOp)++, right >= left; right--) {
            if ((*mainOp)++, array[right - 1] > array[right]) {
                temp = array[right];
                array[right] = array[right - 1];
                array[right - 1] = temp;
                pmLast = right;
            }
        }
        left = pmLast;
    } while ((*helpOp)++, pmLast);
}
