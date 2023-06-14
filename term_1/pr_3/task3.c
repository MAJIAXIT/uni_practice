#include <stdio.h>

#define CONST_INT 0xABCDEF35

int main()
{
    char c1, c2, *cp;
    int i1, i2;
    double d1, d2;
    printf("c1:      char: start address %p extent %lu\n", &c1, sizeof(c1));
    printf("c2:      char: start address %p extent %lu\n", &c2, sizeof(c2));
    printf("i1:       int: start address %p extent %lu\n", &i1, sizeof(i1));
    printf("i2:       int: start address %p extent %lu\n", &i2, sizeof(i2));
    printf("d1:    double: start address %p extent %lu\n", &d1, sizeof(d1));
    printf("d2:    double: start address %p extent %lu\n", &d2, sizeof(d2));
    printf("cp:   pointer: start address %p extent %lu\n", &cp, sizeof(cp));

    i1 = CONST_INT;
    cp = (char *)&i1;
    printf("Bytes:\n");
    for (int i = 0; i < 4; i++)
        printf("%x\n", *cp++);
}
