#include <stdio.h>

int main()
{
    int fibonacci[3] = {0, 1, 1}, num; // Массив для последних 3 чисел последовательности фибоначчи, число для поиска ближайшего
    printf("num = ");
    scanf("%d", &num); // Ввод числа для поиска ближайшего
    while (fibonacci[2] < num) // Пока последнее число последовательности меньше заданного
    {
        fibonacci[0] = fibonacci[1]; // Первый элемент равен второму 
        fibonacci[1] = fibonacci[2]; // Второй равен третьему
        fibonacci[2] = fibonacci[0] + fibonacci[1]; // Третий равен сумме двух предыдущих
    }
    printf("\n%d\n", (num - fibonacci[1] < fibonacci[2] - num) ? fibonacci[1] : fibonacci[2]); // Вывод результата
    return 0; // Выход из функции 
}