#include "load.h"
#include <stdio.h>

int main(void) {
    int a = 0, b = 1;

    while (b) {
        printf("Choose library:\n");
        printf("1. Array\n");
        printf("2. Matrix\n");
        printf("3. Exit\n");
        scanf("%d", &a);
        if (a == 1)
            LoadRun("obj/libarr.so");
        if (a == 2)
            LoadRun("obj/libmatrix.so");
        if (a == 3)
            b = 0;
    }

    return 0;
}