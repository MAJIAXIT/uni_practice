#include <stdlib.h>
#include <stdio.h>

#define COUNT_EXAMS 3  // Количество экзаменов
#define COUNT_MARKS 5  // Количество возможных оценок

int main()
{
    int N, student = 0, currExam; // Количество студентов, текущий студент для ввода, текущий ряд ввода(текущий экзамен)
    int tempMark; // Текущая оценка в ряду ввода
    int exams[COUNT_EXAMS][COUNT_MARKS] = {}; // Матрица вида экзамен : количество оценок из возможных
    printf("Enter N (count of students): ");
    scanf("%d", &N); // Ввод количества студентов
    printf("Enter matrix K %dx3 with values in range [1; 5]:\n", N);

    while (student < N) // Пока номер текущего студента меншьше количества студентов
    {
        currExam = 0; // Текущий экзамен первый
        while (currExam < COUNT_EXAMS) // Пока номер текущего экзамена меньше количества экзаменов
        {
            scanf("%d", &tempMark); // Ввод значения в текущую оценку
            exams[currExam][tempMark - 1]++; // Увеличение количества оценок для текущей оценки текущего экзамена
            currExam++; // Следующий экзамен
        }
        student++; // Следующий студент
    }

    printf("==============================\n");

    for (int _exam = 0; _exam < COUNT_EXAMS; _exam++) // Для каждого экзамена
    {
        printf("Exam: %d\nmarks: | 1 | | 2 | | 3 | | 4 | | 5 |\n       ", _exam + 1);
        for (int _mark = 0; _mark < COUNT_MARKS; _mark++) // Для каждой оценки
            printf("| %d | ", exams[_exam][_mark]); // Вывод количества оценок
        printf("\n");
    }
    
    return 0;
}
