#include <stdio.h>

main()
{
    double a, b, delValue;
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    delValue = a / b;
    printf("%lf / %lf = %lf\n", a, b, delValue);
}
