#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_MAX 1000
#define TOKEN_MAX 100
#define freeAll     \
    free(fileName); \
    free(buffer);   \
    free(token);    \
    free(lastEl);
#define closeAll        \
    fclose(matrixFile); \
    fclose(tempFile);

// Вывод содержимого файла
void printFile(FILE *);

int main(int argc, char **argv)
{
    FILE *matrixFile, *tempFile;                     // Основной, вспомогательный файл
    char *fileName = (char *)malloc(FILENAME_MAX),   // Имя файла
        *buffer = (char *)malloc(BUFFER_MAX),        // Буффер
            *token = (char *)malloc(TOKEN_MAX),      // Токен
                *lastEl = (char *)malloc(TOKEN_MAX); // Последний элемент
    int ch, line = 0, row = 0, column = 0, lastCol = 0;
    // Если память не выделена
    if (fileName == NULL || buffer == NULL || token == NULL || lastEl == NULL)
    {
        // Освободить память, выйти с ошибкой
        perror("Error while allocating memory!\n");
        freeAll;
        exit(1);
    }
    // Если есть аргументы
    if (argc > 1)
        // Взять имя файла из аргументов
        strcpy(fileName, *++argv);
    else
    {
        // Иначе, ввести имя файла
        printf("Enter file name:\n");
        scanf("%s", fileName);
    }
    // Открыть файлы; Если файл не открылся
    if ((matrixFile = fopen(fileName, "r")) == NULL || (tempFile = fopen("tempFile.txt", "w+")) == NULL)
    {
        // Закрыть все файлы, освободить память, выйти с ошибкой
        perror("Error, while opening files.\n");
        freeAll;
        closeAll;
        exit(2);
    }
    // Пока в файле есть строки
    while (fgets(buffer, BUFFER_MAX, matrixFile) != NULL)
    {
        // Заменить разделители в строке на пробелы
        for (int i = 0; buffer[i] != '\0'; i++)
            if (isspace(buffer[i]))
                buffer[i] = ' ';
        row++; // следующая строка
        // Пока есть токены, увеличивать колонку
        if ((token = strtok(buffer, " ")) != NULL)
            column++;
        while ((token = strtok(NULL, " ")) != NULL)
        {
            // Запоминать элемент как последний
            lastEl = strcpy(lastEl, token);
            column++;
        }
        // Если в текущей строке меньше токенов, чем в предыдущей
        if (column != lastCol && lastCol != 0)
        {
            // Матрица не квардратная, освободить память, закрыть файлы, выйти с ошибкой
            perror("Matrix is not square by columns.");
            freeAll;
            closeAll;
            exit(3);
        }
        lastCol = column;
        column = 0;
    }
    // Если строки не равны колонкам
    if (row != lastCol)
    {
        // Матрица не квардратная, освободить память, закрыть файлы, выйти с ошибкой
        perror("Matrix is not square by rows.");
        freeAll;
        closeAll;
        exit(3);
    }

    row = 0;
    rewind(matrixFile); // Возврать курсора в начало файла
    // Пока в файле есть строки
    while (fgets(buffer, BUFFER_MAX, matrixFile) != NULL)
    {
        // Заменить символы разделители в строке на пробелы
        for (int i = 0; buffer[i] != '\0'; i++)
            if (isspace(buffer[i]))
                buffer[i] = ' ';
        // Если не первая строка, записать символ новой строки
        if (line != 0)
            fputc('\n', tempFile);
        // Пока в строке есть токены
        token = strtok(buffer, " ");
        while (token != NULL)
        {
            // Если номера ряда и строки равны
            if (line == row)
                fputs(lastEl, tempFile); // Записать последний элемент
            else
                fputs(token, tempFile); // Иначе записать старое значение
            fputc(' ', tempFile);       // Записать пробел
            row++;                      // Следующий ряд
            token = strtok(NULL, " ");  // Следующий токен
        }
        row = 0; // Первый ряд
        line++;  // следующая строка
    }
    printf("File contains:\n");
    printFile(matrixFile); // Вывод исходного файла
    printf("\n\nUpdated file:\n");
    printFile(tempFile);              // Вывод нового файла
    closeAll;                         // Зкарыть все файлы
    remove(fileName);                 // Удалить исходный файл
    rename("tempFile.txt", fileName); // Переименовать новый файл в имя исходного
    freeAll;                          // Освободить память
    return 0;                         // Выход без ошибки
}

void printFile(FILE *file)
{
    int ch;
    rewind(file); // Вернуть курсор в начало файла
    // Пока есть символы в файле
    while ((ch = fgetc(file)) != EOF)
        putchar(ch); // Записать символ
}