#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLINE 200

int main()
{
    char *buffer = (char *)malloc(MAXWORD), *line = (char *)malloc(MAXLINE);
    int ch, lineIdx = 0, bufIdx = 0;
    // Если память не выделилась
    if (buffer == NULL)
    {
        printf("Error while allocating memory!\n");
        return 1; // Выход из программы с ошибкой
    }

    printf("Enter string:\n");
    // Считывать символ, пока не встретим конец файла
    while ((ch = getchar()) != EOF)
    {
        buffer[bufIdx++] = ch; // Записать символ в слово
        if (isspace(ch) || bufIdx > MAXWORD || ch == ',' || ch == '.') // Если встретили разделитель
        {
            buffer[bufIdx] = '\0';    // Закрываем слово
            if (strstr(buffer, "М"))  // Ищем вхождение в слово символа
                strcat(line, buffer); // Если символ есть добавляем слово в конец строки
            lineIdx += bufIdx - 1;    // Увеличить количество записанных в строку символов
            bufIdx = 0;               // Обнуляем индекс слова
        }
        // Если встречена точка, символ новой строки или длина линии превысила максимальную
        if (ch == '.' || ch == '\n' || lineIdx + bufIdx > MAXLINE)
            break; // Выйти из цикла 
    }
    printf("\n%s\n", line);
    free(buffer);
    free(line);
    return 0;
}
