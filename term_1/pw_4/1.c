#include <stdio.h>

#define MAXLEN 10 // Максимальное количество элементов массива

int main()
{
    int arr[MAXLEN], idx = 0; // Объявление массива и индекса
    printf("Enter array elements:\n");
    while (scanf("%d", &arr[idx++]) != EOF && idx < MAXLEN)
        ; //Ввод массива с клавиатуры
    printf("%d", idx);
    
    for (int i = 1; i < idx - 1; i++) // Цикл по элементам массива
    {
        if (arr[i] > 0) // Если положительное
            arr[i] -= arr[0]; // Вычесть первый элемент
        else if (arr[i] < 0) // Если отрицательное
            arr[i] += arr[idx - 1]; // Прибавить последний элемент
    }

    printf("\n");
    for (int i = 0; i < idx; i++)
        printf("%d\t", arr[i]); // Вывод элементов массива
        
    return 0;
}