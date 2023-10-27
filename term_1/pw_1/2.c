#include <stdio.h>

main()
{
    int a, b, delValue;
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    delValue = a / b;
    printf("%d / %d = %d\n", a, b, delValue);
}
