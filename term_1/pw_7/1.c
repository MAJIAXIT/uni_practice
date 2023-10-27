#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define _bad_symbol(c) (isdigit(c) || ispunct(c) || isspace(c))
#define BUFFER_MAX 2000
#define TOKEN_MAX 200

// Взять сторку до точки из файла
int _getline(FILE *, char *, int);
// Вывод содержимого файла
void printFile(FILE *);

int main(int argc, char **argv)
{
    FILE *file,                                    // Исходный файл
        *tempFile;                                 // Вспомогательный файл
    char *fileName = (char *)malloc(FILENAME_MAX), // Имя файла
        *buffer = (char *)malloc(BUFFER_MAX);      // Буфферная строка
    int wordCount = 0;                             // Количество слов во фразе

    // Если память не выделилась
    if (fileName == NULL || buffer == NULL)
    {
        // Освободить все выйти из программы с ошибкой
        perror("Error while allocating memory!\n");
        free(fileName);
        free(buffer);
        exit(1);
    }

    // Если есть параметры
    if (argc > 1)
        // Взять имя файла из параметров
        strcpy(fileName, *++argv);
    else
    {
        // Ввод имени файла с клавиатуры
        printf("Enter file name:\n");
        scanf("%s", fileName);
    }
    // Открыть файлы. Если файлы не открылись
    if ((file = fopen(fileName, "r")) == NULL || ((tempFile = fopen("tempFile.txt", "w+"))) == NULL)
    {
        // Освободить все строки, закрыть файлы, выйти с ошибкой
        perror("Error while opening file.\n");
        fclose(file);
        fclose(tempFile);
        free(buffer);
        free(fileName);
        exit(2);
    }

    // Пока в файле есть строки
    while (_getline(file, buffer, BUFFER_MAX) > 0)
    {
        // Перенос строки в вспомогательный файл
        fputs(buffer, tempFile);
        // Удаление пунктуации, разделителей из строки, замена на пробелы
        for (int i = 0; buffer[i] != '\0'; i++)
            if (_bad_symbol(buffer[i]))
                buffer[i] = ' ';
        // Пока есть токены увеличивать количество слов во фразе
        if (strtok(buffer, " ") != NULL)
            wordCount++;
        while (strtok(NULL, " ") != NULL)
            wordCount++;
        // Если есть слова
        if (wordCount > 0)
        {
            // Записать в конец фразы в файл (количество слов)
            fprintf(tempFile, "(%d) ", wordCount);
            wordCount = 0;
        }
    }
    fclose(file);                     // Закрыть файл
    remove(fileName);                 // Удалить исходный файл
    rename("tempFile.txt", fileName); // Переименовать вспомогательный файл
    printFile(tempFile);              // Вывести содержимое вспомогательного файла
    fclose(tempFile);                 // Закрыть вспомогательный файл
    free(buffer);                     // Освободить память буфферной строки
    free(fileName);                   // Освободить память имени файла
    return 0;                         // Выход из программы без ошибок
}

// Записать строку до точки из потока file в массив string, длины max
int _getline(FILE *file, char *string, int max)
{
    int ch, idx = 0;
    // Пока в файле есть символы
    while ((ch = fgetc(file)) != EOF && idx < max)
    {
        string[idx++] = ch; // Записать символ в строку
        if (ch == '.')      // Если символ точка
            break;          // Выход из цикла
    }
    string[idx] = '\0'; // Нуль-терминатор в конец строки
    return idx;         // Длина строки
}

// Печать файла в выходной поток
void printFile(FILE *file)
{
    int ch;
    rewind(file);                     // Возврат курсора в начало файла
    while ((ch = fgetc(file)) != EOF) // Пока есть символ
        putchar(ch);                  // Печать символа
}
