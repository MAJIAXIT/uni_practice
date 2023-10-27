#include "sorting.h"

void quicksort(int *array, size_t size, 
               unsigned *mainOp, unsigned *helpOp, size_t *memory) {
    register int left = 0, right = size - 1, support = array[size / 2], temp;
    static size_t curMem = 0;

    curMem += sizeof(left) + sizeof(right) + sizeof(support) + sizeof(temp);
    if (curMem > *memory)
        *memory = curMem;

    do {
        while ((*mainOp)++, array[left] < support) {
            left++;
        }
        while ((*mainOp)++, array[right] > support) {
            right--;
        }
        if ((*helpOp)++, left <= right) {
            temp = array[right];
            array[right] = array[left];
            array[left] = temp;
            left++;
            right--;
        }
    }
    while ((*helpOp)++, left < right)
        ;

    if ((*helpOp)++, right > 0)
        quicksort(array, right + 1, mainOp, helpOp, memory);

    if ((*helpOp)++, left < size - 1)
        quicksort(array + left, size - left, mainOp, helpOp, memory);

    curMem -= curMem;
}