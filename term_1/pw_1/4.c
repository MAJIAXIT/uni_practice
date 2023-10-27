#include <stdio.h>

main()
{
    int a, b;
    double delValue;
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    delValue = (double)a / b;
    printf("%d / %d = %lf\n", a, b, delValue);
}