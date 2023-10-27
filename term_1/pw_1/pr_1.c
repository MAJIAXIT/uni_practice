#include <stdlib.h>
#include <stdio.h>
#include <limits.h> /* Подключение библиотеки, включающей в себя размеры типов */
int main()
{
    char c;
    unsigned char uc;
    printf("sizeof(c)=%d\tsizeof(uc)=%d\n\n", sizeof(c),sizeof(uc)); /* Вывод объема памяти, отводимый для переменных */
    uc = c = CHAR_MAX;	/* Присвоение переменным максимального значения для типа char */
    printf("CHAR_MAX : c=%d uc=%d\n", c, uc);	/* Вывод максимальных значений. Значения совпадают */
    c = c + 1; uc = uc + 1;	/* Добавление единицы к максимальному значению char. Переменная типа char превышает своё допустимое значение и возвращается к минимальному, unsigned char увеличивается на единицу  */
    printf("CHAR_MAX+1 : c=%d uc=%d\n", c, uc);
    uc = c = CHAR_MIN;	/* Присвоение перменным минимального значения для типа char. Для char -128 для unsigned char 128*/
    printf("CHAR_MIN : c=%d uc=%d\n", c, uc);
    c = uc = UCHAR_MAX;	/* Присвоение переменным максимальное значение для типа unsigned char. Для char -1 для unsigned char 255  */
    printf("UCHAR_MAX : c=%d uc=%d\n", c, uc);
    c = c + 1; uc = uc + 1;	/* Добавление единицы к максимальному значению unsigned char. Для char 0 для unsigned char 0 */
    printf("UCHAR_MAX+1 : c=%d uc=%d\n", c, uc);
    uc = c = -5;	/* Присвоение переменной типа unsigned char значение -5 типа char. Для char -5 для unsigned char 251 */
    printf("-5 : c=%d uc=%d\n", c, uc);
    c = -5; uc = 5;	/* Присвоение переменным значение -5. */
    printf("char and unsigned char -5>5 : %d\n\n", c>uc);	/* При сравнении переменные разных типов приводятся компилятором к одному (в данном случае int). При сравнение получаем, что char меньше, чем unsigned char */
    return 0;
}
