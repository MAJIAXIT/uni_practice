#include "head.h"

void inputArray(int *arr, int len) {
    printf("Enter array of lenght %d:\n", len);
    for (int i = 0; i < len; i++)
        scanf("%d", arr + i);
}

void outputArray(int *arr, int len) {
    putchar('\n');
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
}
