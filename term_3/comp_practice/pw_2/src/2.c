#include <stdio.h>
#include <stdlib.h>

#define STRLEN 400

void inputString(char *str, int strlen) {
    int ch, idx = 0;
    printf("\nEnter string: ");
    while ((ch = getchar()) != '\n' && idx < strlen)
        str[idx++] = ch;
}

int main() {
    char *str = (char *)malloc(STRLEN);
    char parCount = 0;

    inputString(str, STRLEN);
    for (int i = 0; str[i] != '\0' && parCount >= 0; i++) {
        if (str[i] == '(')
            parCount++;
        if (str[i] == ')')
            parCount--;
    }

    if (parCount == 0)
        printf("\nString is correct parenthesis expression.\n");
    else
        printf("\nString is uncorrect parenthesis expression.\n");

    free(str);

    return 0;
}