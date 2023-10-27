#include "head.h"

void swapMaxNegAndFirstPos(int *arr, int len) {
    int maxNegIdx = 0, firstPosIdx = -1, temp;
    for (int i = 0; i < len; i++) {
        if (arr[i] < 0 && arr[i] > arr[maxNegIdx])
            maxNegIdx = i;
        if (arr[i] > 0 && firstPosIdx == -1)
            firstPosIdx = i;
    }
    temp = arr[maxNegIdx];
    arr[maxNegIdx] = arr[firstPosIdx];
    arr[firstPosIdx] = temp;
}

void insertZero(int *arr, int len) {
    arr = (int *)realloc(arr, sizeof(int) * (len + 1));
    for (int i = len; i > len / 2; i--)
        arr[i] = arr[i - 1];
    arr[len / 2] = 0;
}