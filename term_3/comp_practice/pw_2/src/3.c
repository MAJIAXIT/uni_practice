#include "str.h"

int main() {
    char *str = (char *)malloc(STRLEN);
    inputString(str, STRLEN);

    for (int i = 0; str[i] != '\0' && i < STRLEN; i++) {
        if (str[i] == '.')
            for (int j = i; str[j] != '\0' && j < STRLEN; j++)
                if (isalpha(str[j])) {
                    str[j] = toupper(str[j]);
                    break;
                }
    }

    outputString(str, STRLEN);

    free(str);
    exit(EXIT_SUCCESS);
}