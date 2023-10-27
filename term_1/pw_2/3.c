#include <stdio.h>

int main()
{
    int a, b, c, negativeCount; // a, b, c, количество отрицательных
    printf("a = ");
    scanf("%d", &a); // Ввод a
    printf("b = ");
    scanf("%d", &b); // Ввод b
    printf("c = ");
    scanf("%d", &c); // Ввод c
    negativeCount = (a < 0) + (b < 0) + (c < 0); // Подсчет количества отрицательных
    if (!a || !b || !c) // Если хотя бы одно равно нулю
    {
        a = b = c = 0; // Обнулить все переменные
    }
    else if (negativeCount == 1) // Иначе, если одно отрицательное
    {
        // Возвести в квадрат если отрицательное
        a = a < 0 ? a * a : a;
        b = b < 0 ? b * b : b;
        c = c < 0 ? c * c : c;
    }
    else if (negativeCount == 2) // Иначе, если два отрицательных
    {
        // Изменить знак переменных
        a = -a;
        b = -b;
        c = -c;
    }
    printf("\na = %d b = %d c = %d\n", a, b, c); // Вывод переменных
    return 0; // Выход из функции
}