#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *filename = (char *)malloc(FILENAME_MAX);
    int n, min, max, tmp, rnd;
    FILE *file;
    if (argc > 1)
    {
        strcpy(filename, *++argv);
        if (argc > 2)
        {
            sscanf(*++argv, "%d", &n);
            if (argc == 5)
            {
                sscanf(*++argv, "%d", &min);
                sscanf(*++argv, "%d", &max);
            }
        }
    }
    else
    {
        printf("Enter file name:\n");
        scanf("%s", filename);
        printf("How many numbers?\n");
        scanf("%d", &n);
        printf("min?\n");
        scanf("%d", &min);
        printf("max?\n");
        scanf("%d", &max);
    }
    if ((file = fopen(filename, "wb+")) == NULL)
    {
        perror("Error while opening file.\n");
        exit(1);
    }
    srand(time(NULL));
    while (--n >= 0)
    {
        rnd = min + rand() % (max - min + 1);
        fwrite(&rnd, sizeof(int), 1, file);
    }
    rewind(file);
    while (fread(&tmp, sizeof(int), 1, file))
        printf("%d ", tmp);

    fclose(file);
    free(filename);
}