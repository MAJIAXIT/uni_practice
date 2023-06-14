#include <stdio.h>
#include <math.h>

int main()
{
    double m, n, tgOdz, znamOdz; // m, n, ОДЗ для тангенса, ОДЗ для знаменателя
    printf("m = ");
    scanf("%lf", &m); // Ввод m
    printf("n = ");
    scanf("%lf", &n); // Ввод n
    if (n && cos(m / n) && (tgOdz = tan(m / n)) > 0 && (znamOdz = log(tgOdz) + exp(m * m))) // Проверка ОДЗ
    {

        printf("\n%lf\n", (sqrt(fabs(m - n)) - sin(m) * cos(n)) / znamOdz); // Вывод результата
    }
    else
        printf("\nНе подходит под область определения\n"); // Вывод ошибки нарушения ОДЗ
    return 0; // Выход из функции
}