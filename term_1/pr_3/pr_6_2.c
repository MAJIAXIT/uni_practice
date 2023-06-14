#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *p, c;
    int *a, b;
    float *x, y = 3.5;
    double *m, n;

    a = &b;
    *a = 10;
    printf("a = &b;\n*a = 10;\n");
    // printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    // printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    // printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    // printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    // printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    // printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    // printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    // printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

    printf("c: related value %d\n", c);
    printf("b: related value %d\n", b);
    printf("y: related value %lf\n", y);
    printf("n: related value %lf\n", n);


    p = (char *)a;
    c = *p;
    *p = *(p + 3);
    *(p + 3) = c;

    printf("p = (char *)a;\nc = *p;\n*p = *(p + 3);\n*(p + 3) = c;\n");
    // printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    // printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    // printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    // printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    // printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    // printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    // printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    // printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

    printf("c: related value %d\n", c);
    printf("b: related value %d\n", b);
    printf("y: related value %lf\n", y);
    printf("n: related value %lf\n", n);

    printf("*a: related value %d\n", *a);

    x = &y;
    a = (int *)x;
    *a = *x;

    printf("x = &y;\na = (int *)x;\n*a = *x;\n");
    // printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    // printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    // printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    // printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    // printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    // printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    // printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    // printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

    printf("c: related value %d\n", c);
    printf("b: related value %d\n", b);
    printf("y: related value %lf\n", y);
    printf("n: related value %lf\n", n);

    printf("*p: related value %d\n", *p);
    printf("*a: related value %d\n", *a);
    printf("*x: related value %lf\n", *x);
    printf("*m: related value %lf\n", *m);

    a = &b;
    y = 12345.6789;
    p = (char *)x;
    c = *p;
    *p = *(p + 3);
    *(p + 3) = c;

    printf("a = &b;\ny = 12345.6789;\np = (char *)x;\nc = *p;\n*p = *(p + 3);\n*(p + 3) = c;\n");
    // printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    // printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    // printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    // printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    // printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    // printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    // printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    // printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

    printf("c: related value %d\n", c);
    printf("b: related value %d\n", b);
    printf("y: related value %lf\n", y);
    printf("n: related value %lf\n", n);

    printf("*p: related value %d\n", *p);
    printf("*a: related value %d\n", *a);
    printf("*x: related value %lf\n", *x);
    printf("*m: related value %lf\n", *m);

    m = &n;
    n = 5.5;
    b = n = y = 1.7;

    printf("m = &n;\nn = 5.5;\nb = n = y = 1.7;\n");
    // printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    // printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    // printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    // printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    // printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    // printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    // printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    // printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

    printf("c: related value %d\n", c);
    printf("b: related value %d\n", b);
    printf("y: related value %lf\n", y);
    printf("n: related value %lf\n", n);

    printf("*p: related value %d\n", *p);
    printf("*a: related value %d\n", *a);
    printf("*x: related value %lf\n", *x);
    printf("*m: related value %lf\n", *m);

    m += 2;
    *m = (float)*a - n + (int)*x;

    printf("m += 2;\n*m = (float)*a - n + (int)*x;\n");
    // printf("&c:     char: start address %p extent %lu\n", &c, sizeof(c));
    // printf("&b:      int: start address %p extent %lu\n", &b, sizeof(b));
    // printf("&y:    float: start address %p extent %lu\n", &y, sizeof(y));
    // printf("&n:   double: start address %p extent %lu\n", &n, sizeof(n));

    // printf("p:    char *: start address %p extent %lu\n", &p, sizeof(p));
    // printf("a:     int *: start address %p extent %lu\n", &a, sizeof(a));
    // printf("x:   float *: start address %p extent %lu\n", &x, sizeof(x));
    // printf("m:  double *: start address %p extent %lu\n", &m, sizeof(m));

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
