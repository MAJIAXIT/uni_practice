#include "sorting.h"
#include <string.h>

#define SIZES 4
#define SORTINGS 4
#define REP_FILES 4
#define SORT_CASE_LEN 50

void reverseArray(int *arr, size_t size);
int *fillFromFile(size_t size, FILE *file);
float benchmark(int          *arr, 
                size_t       size, 
                unsigned int *mainOp,
                unsigned int *helpOp, 
                size_t       *memory, 
                void (*func)(int *arr, size_t size, 
                             unsigned *mainOp, unsigned *helpOp, 
                             size_t *memory));
void showResult(const char   *sortingName, 
                size_t       size, 
                const char   *sortCase, 
                float        timeElapsed, 
                unsigned int mainOp, 
                unsigned int helpOp, 
                size_t       memory);

int main(int argc, char **argv) {
    const size_t sizes[SIZES] = {10000, 18000, 30000, 60000};
    struct {
        void (*func)(int *arr, size_t size, 
                     unsigned *mainOp, unsigned *helpOp,
                     size_t *memory);
        const char *name;
    } funcArray[SORTINGS] = {
        {bubble,      "bubble"},
        {bubbleFixed, "bubbleFixed"},
        {shaker,      "shaker"},
        {quicksort,   "quicksort"},
    };
    struct {
        FILE *file;
        const char *name;
    } repFiles[REP_FILES] = {
        {fopen("files/repeated_10.txt",   "r"), "R10"},
        {fopen("files/repeated_100.txt",  "r"), "R100"},
        {fopen("files/repeated_500.txt",  "r"), "R500"},
        {fopen("files/repeated_1000.txt", "r"), "R1000"},
    };

    register int *arr = NULL;
    // float startTime, endTime, timeElapsed;
    float timeElapsed;
    char sortCase[SORT_CASE_LEN];
    int i;
    unsigned mainOp, helpOp;
    size_t memory;
    FILE *numsFile;

    if ((numsFile = fopen("files/test_numbers.txt", "r")) == NULL ||
        repFiles[0].file == NULL || repFiles[1].file == NULL ||
        repFiles[2].file == NULL || repFiles[3].file == NULL) {
        perror("Error while opening files. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    printf("|  Algorithm  | Elements |      Order      |   Time   |    mainOp    "
           "|    helpOp    |   memory   |\n");
    printf("------------------------------------------------------------------"
           "--------------------------------\n");

    // Get sorting number from args 
    // or go through them all if arguments are empty
    for (int sortingsIdx = argc > 1 ? atoi(*++argv) : 0;
             sortingsIdx < (argc > 1 ? atoi(*argv) + 1 : SORTINGS);
             sortingsIdx++) {
        for (int sizesIdx = 0; sizesIdx < SIZES; sizesIdx++) {

            arr = fillFromFile(sizes[sizesIdx], numsFile);

            // Benchmarks start
            // Unsorted array benchmark
            timeElapsed = benchmark(arr, sizes[sizesIdx], &mainOp, &helpOp,
                                    &memory, funcArray[sortingsIdx].func);

            showResult(funcArray[sortingsIdx].name, sizes[sizesIdx],
                       "unordered", timeElapsed, mainOp, helpOp, memory);

            // Ascending ordered array benchmark
            timeElapsed = benchmark(arr, sizes[sizesIdx], &mainOp, &helpOp,
                                    &memory, funcArray[sortingsIdx].func);

            showResult(funcArray[sortingsIdx].name, sizes[sizesIdx],
                       "ordered", timeElapsed, mainOp, helpOp, memory);

            reverseArray(arr, sizes[sizesIdx]);

            // Descending ordered array benchmark
            timeElapsed = benchmark(arr, sizes[sizesIdx], &mainOp, &helpOp,
                                    &memory, funcArray[sortingsIdx].func);

            showResult(funcArray[sortingsIdx].name, sizes[sizesIdx],
                       "reversed", timeElapsed, mainOp, helpOp, memory);
            printf("-----------------------------------------------------------"
                   "---------------------------------------\n");

            free(arr);
        }

        // Files with 10, 100, 500 and 1000 repeated numbers benchmarks
        for (i = 0; i < REP_FILES; i++) {

            arr = fillFromFile(sizes[SIZES - 1], repFiles[i].file);

            // Benchmark for unordered file with repetitions
            timeElapsed = benchmark(arr, sizes[SIZES - 1], &mainOp, &helpOp,
                                    &memory, funcArray[sortingsIdx].func);

            strcpy(sortCase, "unordered ");
            showResult(funcArray[sortingsIdx].name, sizes[SIZES - 1],
                       strcat(sortCase, repFiles[i].name), timeElapsed,
                       mainOp, helpOp, memory);

            // Benchmark for ordered file with repetitions
            timeElapsed = benchmark(arr, sizes[SIZES - 1], &mainOp, &helpOp,
                                    &memory, funcArray[sortingsIdx].func);

            strcpy(sortCase, "ordered ");
            showResult(funcArray[sortingsIdx].name, sizes[SIZES - 1],
                       strcat(sortCase, repFiles[i].name), timeElapsed,
                       mainOp, helpOp, memory);

            reverseArray(arr, sizes[SIZES - 1]);

            // Benchmark for reverse ordered file with repetitions
            timeElapsed = benchmark(arr, sizes[SIZES - 1], &mainOp, &helpOp,
                                    &memory, funcArray[sortingsIdx].func);

            strcpy(sortCase, "reversed ");
            showResult(funcArray[sortingsIdx].name, sizes[SIZES - 1],
                       strcat(sortCase, repFiles[i].name), timeElapsed,
                       mainOp, helpOp, memory);

            printf("-----------------------------------------------------------"
                   "---------------------------------------\n");
            free(arr);
        }
    }

    fclose(numsFile);
    for (int i = 0; i < REP_FILES; i++)
        fclose(repFiles[i].file);

    exit(EXIT_SUCCESS);
}

void reverseArray(int *arr, size_t size) {
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

float benchmark(int          *arr, 
                size_t       size, 
                unsigned int *mainOp,
                unsigned int *helpOp, 
                size_t       *memory, 
                void (*func)(int *arr, size_t size, 
                             unsigned *mainOp, unsigned *helpOp, 
                             size_t *memory)) {
    float startTime, endTime, timeElapsed;

    *memory = *mainOp = *helpOp = 0;
    startTime = (float)clock() / CLOCKS_PER_SEC;
    func(arr, size, mainOp, helpOp, memory);
    endTime = (float)clock() / CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;

    return timeElapsed;
}

int *fillFromFile(size_t size, FILE *file) {
    int *arr, idx = 0;

    arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocationg error. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    rewind(file);
    idx = 0;
    while (fscanf(file, "%d", &arr[idx++]) && idx < size)
        ;
    return arr;
}

void showResult(const char   *sortingName, 
                size_t       size, 
                const char   *sortCase, 
                float        timeElapsed, 
                unsigned int mainOp, 
                unsigned int helpOp, 
                size_t       memory) {

    printf("| %11s | %8d | %15s | %lf | %12d | %12d | %10d |\n",
           sortingName, size, sortCase, timeElapsed, mainOp, helpOp, memory);
}
