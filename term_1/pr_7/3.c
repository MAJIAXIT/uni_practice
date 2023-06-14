#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE sizeof(int)
#define closeAll     \
    fclose(binFile); \
    fclose(tempBinFile);

// Вывод содержимого бинарного файла
void printBinFile(FILE *);

int main(int argc, char **argv)
{
    FILE *binFile, *tempBinFile; // Исходный и вспомогательный файлы
    char *fileName = (char *)malloc(FILENAME_MAX); // Имя файла
    //  Конец файла, отступ, минимальное, максимальное, текущее
    int endFile, offset = 0, min = 1000000, max = -1000000, curr;
    // Если память не выделилась
    if (fileName == NULL)
    {
        // выход с ошибкой
        fprintf(stderr, "Error while allocating memory.\n");
        exit(1);
    }
 // если есть аргументы 
    if (argc > 1)
    // Взять имя файла из аргументов
        strcpy(fileName, *++argv);
    else
    {
        // Ввод имени файла 
        printf("Enter file name:\n");
        scanf("%s", fileName);
    }
    // Открыть файлы. Если файл не открылся 
    if ((binFile = fopen(fileName, "rb")) == NULL || (tempBinFile = fopen("tempBinFile.bin", "wb+")) == NULL)
    {
        // закрыть все файлы, освободить память, выйти с ошибкой
        perror("Error while opening files.\n");
        closeAll;
        free(fileName);
        exit(1);
    }
    // напечатать содержимое исходного файла
    printf("File contains:\n");
    printBinFile(binFile);
    endFile = ftell(binFile); // запомнить конец файла
    // пока отступ от начала меньше конца файла
    while (offset < endFile)
    {
        fseek(binFile, offset, SEEK_SET); // сместиться на отступ
        fread(&curr, SIZE, 1, binFile); // считать число
        // Запомнить если максимальное/минимальное
        max = curr > max ? curr : max;
        min = curr < min ? curr : min;
        offset += SIZE; // Увеличить отступ
    }

    offset = 0; // Обнулить отступ
    while (offset < endFile) // пока отступ меньше конца файла
    {
        fseek(binFile, offset, SEEK_SET); // сместиться на отступ
        fread(&curr, SIZE, 1, binFile); // считать значение
        if (curr != min && curr != max) // Если значение не максимальное и не минимальное
            fwrite(&curr, SIZE, 1, tempBinFile); // Записать значение в файл
        offset += SIZE; // Увеличить отступ
    }
    // Вывод вспомогательного файла
    printf("\nUpdated file:\n");
    printBinFile(tempBinFile);
    // закрыть все файлы
    closeAll;
    remove(fileName); // Удалить исходный файл
    rename("tempBinFile.bin", fileName); // переименовать вспомогательный в имя исходного файла
    free(fileName); // освободить память имени файла
    return 0; // выход с успехом
}

void printBinFile(FILE *file)
{
    int tmp;
    rewind(file); // вернуть курсор в начало файла
    while (fread(&tmp, SIZE, 1, file)) // Пока считано число
        printf("%d ", tmp); // вывод числа
}