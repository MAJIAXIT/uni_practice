#include <stdio.h>
#include <math.h>

int main()
{
    int m, k, crf = 4; // m, степень 4ки, текущее 4^k
    printf("m = ");
    scanf("%d", &m); // Ввод m
    for (k = 0; crf < m; ++k, crf *= 4)
        // Для k от нуля, пока текущее 4^k меньше m, с шагом 1 дл степени 4ки, *4 для текущего 4^k
        ;
    printf("\nk = %d\n", k); // Вывод степени четверки
    return 0; // Выход из функции
}