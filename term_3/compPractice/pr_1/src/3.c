#include "head.h"

int main() {
    int *arr = (int *)malloc(sizeof(int) * ARR_LEN_2);

    inputArray(arr, ARR_LEN_2);
    insertZero(arr, ARR_LEN_2);
    outputArray(arr, ARR_LEN_2 + 1);

    free(arr);

    return 0;
}