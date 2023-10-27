#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *p, c;
    int *a, b;
    float *x, y = 3.5;
    double *m, n;

    a = &b;
    printf("  Enter b = ");
    scanf("%d", a);

    printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

    printf("a=%p\t*a=%d\tb=%d\n", a, *a, b);
    p = (char *)a;
    c = *p;
    *p = *(p + 3);
    *(p + 3) = c;
    printf("p=%p\tc=%d\ta=%p\tb=%d\n", p, c, a, b);

    x = &y;
    printf("x=%p\t*x=%f\ty=%f\n", x, *x, y);
    a = (int *)x;
    *a = *x;
    printf("a=%p\t*a=%d\tx=%p\t*x=%f\ty=%f\n", a, *a, x, *x, y);

    a = &b;
    y = 12345.6789;
    printf("x=%p\t*x=%f\ty=%f\n", x, *x, y);
    
    p = (char *)x;
    c = *p;
    *p = *(p + 3);
    *(p + 3) = c;
    printf("p=%p\tc=%d\tx=%p\ty=%f\n", p, c, x, y);

    m = &n;
    printf("m=%p\t*m=%lf\tn=%lf\n", m, *m, n);
    n = 5.5;
    printf("m=%p\t*m=%lf\tn=%lf\n", m, *m, n);
    b = n = y = 1.7;
    printf("b=%d\ty=%f\tn=%lf\n", b, y, n);
    printf("*a=%d\t*x=%f\t*m=%lf\n", *a, *x, *m);
    m += 2;
    printf("n=%lf\tn=%p\tm=%p\n", n, &n, m);
    *m = (float)*a - n + (int)*x;
    printf("m=%p\t*m=%lf\n", m, *m);

    printf("c: related value %d\n", c);
    printf("b: related value %d\n", b);
    printf("y: related value %lf\n", y);
    printf("n: related value %lf\n", n);

    printf("*p: related value %d\n", *p);
    printf("*a: related value %d\n", *a);
    printf("*x: related value %lf\n", *x);
    printf("*m: related value %lf\n", *m);
    return 0;
}