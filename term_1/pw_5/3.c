#include <stdio.h>
#include <math.h>

#define N 20

double expression_1(double x);
double expression_2(double x);
double integral(int a, int b, double (*expression)(double x));

int main()
{
    printf("a = -1, b = 4, y = 2 * x * (x * x + 1)\nValue:\n%lf\n", integral(-1, 4, expression_1));
    printf("\na = -1, b = 2, y = sin(x) / (1 + sin(x))\nValue:\n%lf\n", integral(-1, 2, expression_2));
    return 0;
}

double integral(int a, int b, double (*expression)(double x))
{
    // Расстояние между x0, x1...xn, сумма площадей, текущая абсцисса
    double delta = (double)(b - a) / N, sum = 0, x;
    int factor, i = 1; // Множитель, счетчик слагаемых
    // Для x от a + delta до b с шагом delta
    for (x = a + delta; x < b; x += delta, i++)
    {
        // Вычисление множителя
        factor = i % 2 == 0 ? 2 : 4;
        // Суммирование со следующим элементом
        sum += factor * expression(x);
    }
    // Суммирование с первым и последним элементом
    sum = (delta / 3) * (sum + expression(a) + expression(b));
    return sum; // Суммарная площадь
}

double expression_1(double x)
{
    return 2 * x * x * x + 2 * x;
}

double expression_2(double x)
{
    return sin(x) / (1 + sin(x));
}