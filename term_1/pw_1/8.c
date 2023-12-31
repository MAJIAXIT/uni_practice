#include <stdlib.h>
#include <stdio.h>
#include <float.h> /* Подключение библиотеки с характеристиками для типов float и double */
int main()
{
    float f;
    double d;
    printf("sizeof(f)=%d\tsizeof(d)=%d\n\n", sizeof(f), sizeof(d)); /* Вывод размера типов в байтах. */
    d = f = FLT_MAX; /* Максимальное значение для float записывается корректно в обе переменные */
    printf("FLT_MAX : f=%g d=%g\n", f, d);
    d = f = FLT_MIN; /* Минимальное значение для float также записывается корректно в обе переменные */
    printf("FLT_MIN : f=%g d=%g\n", f, d);
    d = f = FLT_EPSILON; /* Машинный эпсилон (число, все числа меньше которого не отличимы для компилятора от нуля) для float: точность 7 десятичных знаков */
    printf("FLT_EPSILON : f=%g d=%g\n", f, d);
    f = 12345678; /* Значение записывается корректно. Мантиссы типа float достаточно */
    printf("12345678 : f=%f\n", f);
    f = 123456789; /* Значение записывается некорректно. Размера мантиссы не хватает для записи числа. Часть значения записывается некорректно */
    printf("123456789 : f=%f\n", f);
    f = 1234567890; /* Значение записывается некорректно. Размера мантиссы не хватает для записи числа. Часть значения записывается некорректно */
    printf("1234567890 : f=%f\n", f);
    d = DBL_MAX; /* Максимальное значение для типа double */
    printf("DBL_MAX : d=%g\n", d);
    d = DBL_MIN; /* Минимальное значение для типа double */
    printf("DBL_MIN : d=%g\n", d);
    d = DBL_EPSILON; /* Машинный эпсилон (число, все числа меньше которого не отличимы для компилятора от нуля) для типа double: точность 15 десятичных знаков */
    printf("DBL_EPSILON : d=%g\n", d);
    d = 1e15 + 1; /* При вычислениях с 15-ти значным числом, получаем корректное значение */
    printf("1e15+1 : d=%lf\n", d);
    d = 1e16 + 1; /* Точности double не хватает для вычисления 16-ти значного числа */
    printf("1e16+1 : d=%lf\n", d);
    d = 10000 * 100000 + 1 - 4 * 250000000; /* Точности double хватает для вычисления 10-ти значных чисел */
    printf("1 : d=%lf\n", d);
    d = 1e20 * 1e20 + 1000 - 1e22 * 1e18; /* При вычислении левой части выражения, точности double не хватает для вычисления. Результат не корректен */
    printf("1000 : d=%lf\n", d);
    d = 1e20 * 1e20 - 1e22 * 1e18 + 1000; /* Точности double хватает для вычисления. Результат корректен*/
    printf("1000 : d=%lf\n", d);
    f = d = 0.3; /* Значение не может быть записано с идеальной точностью для типов чисел с плавающей запятой, следовательно значения различаются */
    printf("0.3 : f=%.8f  d=%.17f\n", f, d);
    f = 0;
    while (f < 10) /* Из за погрешности в вычислении с типом float, цикл повторяется на 1 раз больше, чем ожидаемо */
        f += 0.2;
    printf("10 : f=%f\n", f);
    return 0;
}