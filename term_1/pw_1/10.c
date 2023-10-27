#include <stdio.h>
int main()
{
    int c, d;
    double a, b;
    a = c = 5;
    printf("double b = ");
    scanf("%lf", &b);
    printf("int d = ");
    scanf("%d", &d);
    a += b - 2;
    printf("a = %lf b = %lf c = %d d = %d\n", a, b, c, d);
    d = ++c - a + d;
    printf("a = %lf b = %lf c = %d d = %d\n", a, b, c, d);
    a *= c--;
    printf("a = %lf b = %lf c = %d d = %d\n", a, b, c, d);
    d *= (c /= 2) + --b + (a /= 10);
    printf("a = %lf b = %lf c = %d d = %d\n", a, b, c, d);
    return 0;
}
