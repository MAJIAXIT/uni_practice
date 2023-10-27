#include "str.h"

void inputString(char *str, int strlen) {
    int ch, idx = 0;
    printf("\nEnter string: ");
    while ((ch = getchar()) != '\n' && idx < strlen)
        str[idx++] = ch;
}

void outputString(char *str, int strlen) {
    putchar('\n');
    for (int i = 0; i < strlen && str[i] != '\0'; i++)
        putchar(str[i]);
    putchar('\n');
}