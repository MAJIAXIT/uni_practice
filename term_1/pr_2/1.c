#include <stdio.h>

int main()
{
    double a, b;
    printf("a = ");
    scanf("%lf", &a); // Ввод a
    printf("b = ");
    scanf("%lf", &b); // Ввод b
    printf("\n%lf\n", a > 10 ? a - b : 0 < a && b > 0 ? (a - b) / (a + b) : b); // Вывод результата
    return 0; // Выход из функции
}