#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TOKEN_MAX 10
#define MAX_NUMS_ON_LINE 30
#define BUFFERLINE_MAX MAX_NUMS_ON_LINE *(TOKEN_MAX + 3)

#define badSymbol(i) isspace(i) || (ispunct(i) && i != '-') || isalpha(i)

int isSimple(int);
void printFile(FILE *);

int main(int argc, char **argv)
{
    char fileName[FILENAME_MAX],
        *bufferLine = (char *)malloc(BUFFERLINE_MAX),
        *token = (char *)malloc(TOKEN_MAX);
    int outputArray[MAX_NUMS_ON_LINE + 1], arrIdx, temp, simpleCount, i;
    FILE *file,
        *tempFile;

    if (token == NULL || bufferLine == NULL)
    {
        fprintf(stderr, "Error while allocating memory.\n");
        free(bufferLine);
        free(token);
        exit(1);
    }

    if (argc > 1)
        strcpy(fileName, *++argv);
    else
    {
        printf("Enter file name: ");
        scanf("%s", fileName);
    }

    if ((file = fopen(fileName, "r")) == NULL ||
        (tempFile = fopen("temp.txt", "w+")) == NULL)
    {
        fprintf(stderr, "Error while opening files.\n");
        free(bufferLine);
        free(token);
        exit(1);
    }

    while (fgets(bufferLine, BUFFERLINE_MAX, file))
    {
        for (i = 0; bufferLine[i] != '\0'; i++)
            if (badSymbol(bufferLine[i]))
                bufferLine[i] = ' ';

        arrIdx = 1;
        simpleCount = 0;

        if ((token = strtok(bufferLine, " ")) != NULL)
        {
            temp = atoi(token);
            if (isSimple(temp))
                simpleCount++;
            outputArray[arrIdx++] = temp;
            while ((token = strtok(NULL, " ")) != NULL)
            {
                temp = atoi(token);
                if (isSimple(temp))
                    simpleCount++;
                outputArray[arrIdx++] = temp;
            }
            outputArray[0] = simpleCount;
        }

        if (arrIdx > 1)
        {
            fprintf(tempFile, "%d simple: ", outputArray[0]);
            for (i = 1; i < arrIdx; i++)
                if (isSimple(outputArray[i]))
                    fprintf(tempFile, "[%d] ", outputArray[i]);
                else
                    fprintf(tempFile, "%d ", outputArray[i]);
            fputc('\n', tempFile);
        }
    }

    remove(fileName);
    rename("temp.txt", fileName);
    printFile(tempFile);
    free(bufferLine);
    free(token);
    exit(0);
}

int isSimple(int num)
{
    num = num > 0 ? num : -num;
    for (int i = 2; i < num; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

void printFile(FILE *file)
{
    int ch;
    rewind(file);
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
}