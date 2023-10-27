#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int main()
{
    char c;
    unsigned char uc;
    int i;
    unsigned u;
    short s;
    long l;
    printf("sizeof(i)=%d\tsizeof(u)=%d\tsizeof(s)=%d\tsizeof(l)=%d\n\n",
          sizeof(i), sizeof(u), sizeof(s), sizeof(l));	/* Вывод объема памяти, выделяемого под перменные разных типов */
    c = s = SHRT_MAX;	/* Присвоение переменной типа char и short максимальное допустимое значение для типа short */
    uc = s;		/* Присвоение переменной uc типа unsigned char максимальное допустимое значение для типа short. Для char -1, unsigned 255, short 32767 */
    printf("SHRT_MAX : c=%d uc=%d s=%d\n", c, uc, s);
    s = s + 1;	/* Добавление единицы к максимальному значению для short переменной типа short. Тип переполняется и принимает минимальное значение -32768 */
    printf("SHRT_MAX+1 : s=%d\n", s);
    c = s; uc = s;	/* Присвоение переменным типа char и unsigned char переполненное на единицу значение для типа short. Для char 0, unsigned char 0 */
    printf("%d : c=%d uc=%d\n", SHRT_MIN, c, uc);
    s = 0; c = s; uc = s;	/* Присвоение перменным типа short, char, unsigned char нуля. Все переменные принимают значение 0 */
    printf("0 : c=%d uc=%d s=%d\n", c, uc, s);
    i = INT_MAX;	/* Присвоение перменной типа int максимального значения для типа 2147483647*/
    l = i; u = i;	/* Присвоение перменным типа long, unsigned int максимального значения для типа int. Для long и unsigned int 2147483647 */
    printf("INT_MAX : i=%d u=%u l=%ld\n", i, u, l);	/* Int: 2147483647, long: 2147483647, unsigned int: 2147483647 */
    i = i + 1; l = l + 1; u = u + 1;	/* Добавление единицы к переменным типов int, long, unsigned int с максимальным значением типа int. Для int -2147483648, unsigned int 2147483648, long 2147483648 */
    printf("INT_MAX+1 : i=%d u=%u l=%ld\n", i, u, l);
    i = INT_MIN;	/* Присвоение переменной типа int минимального значения для типа. Для int -2147483648 */
    l = i; u = i;	/* Присвоение переменным типа long и unsigned int минимального значения для типа int. Для long -2147483648, unsigned int 2147483648*/
    printf("INT_MIN : i=%d u=%u l=%ld\n", i, u, l);
    u = UINT_MAX;	/* Присвениение переменной типа unsigned int максимального значения для типа. Для unsigned int 4294967295 */
    i = u; l = u;	/* Присвоение перменным типов int и long максимального значения для типа unsigned int. Для int -1, long 4294967295*/
    printf("UINT_MAX : i=%d u=%u l=%ld\n", i, u, l);
    u = i = -5;	/* Присвоение переменным типа unsigned int и int -5. Для unsigned int 429496721, int -5 */
    printf("-5 : i=%d u=%u\n", i, u);
    i = -5; u = 5;	/* Присвоение переменным типа unsigned int 5 и int -5. При сравнении переменных после приведения типов компилятором получаем, что -5 > 5 */
    printf("int and unsigned int -5>5 : %d\n", i > u);
    c = -5; u = 5;	/* Присвоение переменным типа char -5, unsigned int 5. При сравнении переменных после приведения типов компилятором получаем, что -5 > 5  */
    printf("char and unsigned int -5>5 : %d\n\n", c > u);
    i = 5.1;	/* Присвоение переменной типа int отрицательное значение. Компилятор округлил значение int вниз до целой части 5 */
    printf("i=5.1 : i=%d\n", i);
    i = 5.9;	/* Присвоение переменной типа int отрицательное значение. Компилятор округлил значение int вниз до целой части 5 */
    printf("i=5.9 : i=%d\n", i);
    return 0;
}
