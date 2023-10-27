#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100 // Максимальное количество элементов исходного массива
#define NEW_ARR_MAXLEN 125 // Максимальное количество элементов нового массива
#define fiveElement(arr, arrIdx) arr[arrIdx - 3] + arr[arrIdx - 2] + arr[arrIdx - 1] // Макрос для нахождения суммы последних 3 элементов массива

int main()
{
    int *oldArr = malloc(sizeof(int) * MAXLEN), *newArr = malloc(sizeof(int) * (MAXLEN + MAXLEN / 5)); // Исходный массив, новый массив
    int idx = 0, oldArrIdx = 0, newArrIdx = 0, countEl = 0; // Индекс для записи в исходный массив, индекс для исходного массива, индекс для нового массива, счетчик количества элементов

    if (oldArr == NULL || newArr == NULL) // Если память не выдилилась
    {
        printf("Error while allocating memory");
        return 1; // Ошибка, выход из программы
    }
    
    printf("Enter array elements:\n");
    while (scanf("%d", &oldArr[idx++]) != EOF && idx < MAXLEN)
        ; //Ввод массива с клавиатуры

    while (oldArrIdx < idx) // Пока индекс исходного массива меньше последнего элемента исходного массива
    {
        newArr[newArrIdx++] = oldArr[oldArrIdx++]; // Копирование числа из старого в новый массив
        countEl++; // Инкремент счетчика элементов
        if (countEl == 5) // Если пятый элемент
        {
            newArr[newArrIdx] = fiveElement(newArr, newArrIdx); // Следующий элемент нового массива равен сумме трех предыдущих
            newArrIdx++; // Инкремент индекса нового массива
            countEl = 0; // Обнуление счетчика элементов
        }
    }

    printf("\n"); // Вывод новой строки
    for (int i = 0; i < newArrIdx - 1; i++) // Для всех элементов нового массива
        printf("%d ", newArr[i]); // Вывод элемента нового массива
        
    free(newArr); // Освободить память, выделенную под новый массив
    free(oldArr); // Освободить память, выделенную под старый массив
    
    return 0;
}