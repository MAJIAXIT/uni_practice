#include "head.h"

int main() {
    int *arr = (int *)malloc(sizeof(int) * ARR_LEN_1);

    inputArray(arr, ARR_LEN_1);
    swapMaxNegAndFirstPos(arr, ARR_LEN_1);
    outputArray(arr, ARR_LEN_1);

    free(arr);

    return 0;
}