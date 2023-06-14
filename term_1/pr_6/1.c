#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define MONTHS 12
#define leap_year(year) ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)

int main()
{
    const int month_days[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *line = (char *)malloc(MAXLINE);
    unsigned int day, month, year;
    // Если память под строку не выделилась
    if (line == NULL)
    {
        printf("Error while allocating memory\n");
        return 1; // Выход из программы с ошибкой
    }
    printf("Enter string:\n");
    fgets(line, MAXLINE, stdin);                           // Взять строку из входного потока
    if (sscanf(line, "%d.%d.%d", &day, &month, &year) < 3) // Если не все значения записались при форматированном вводе со строки
    {
        printf("Invalid format: enter date in dd.mm.yyyy: %s\n", line);
        return 2; // Выходи из программы с ошибкой
    }
    // Если введен неверный день
    if ((day > month_days[month - 1] && !(leap_year(year) && month == 2 && day == 29)) || month > 12)
    {
        printf("Incorrect date\n");
        return 3;
    }

    day++; // Прибавить день
    if (day > month_days[month - 1]) // Если день больше количества дней в месяце
    {
        // Если високосный год, месяц февраль и 29 день
        if (leap_year(year) && month == 2 && day == 29)
            month = 2;
        else // иначе
        {
            day = 1;
            if (month == 12)
            {
                year++;
                month = 1;
            }
            else
                month++;
        }
    }
    // Вывод следующей даты
    printf("Next date: %02d.%02d.%d\n", day, month, year);
    free(line); // Освобождение памяти строки
    return 0;   // Выход из программы
}
