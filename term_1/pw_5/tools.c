// Ввод массива arr длиной len
void inputArray(int *arr, int len)
{
    int arrIdx = 0;
    printf("Enter array, %d elements:\n", len);
    while (scanf("%d", &arr[arrIdx++]) != EOF && arrIdx < len)
        ;
}

// Вывод массива arr, длиной arrLen
void printArray(int *arr, int arrLen)
{
    printf("Array elements:\n");
    for (int i = 0; i < arrLen; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}

// Ввод матрицы matrix размером rowCount x colCount
void inputMatrix(int **matrix, int rowCount, int colCount)
{
    int row = 0, column = 0;
    printf("Enter matrix %dx%d:\n", rowCount, colCount);
    while (row < rowCount)
    {
        column = 0;
        while (column < colCount)
        {
            scanf("%d", &matrix[row][column]);
            column++;
        }
        row++;
    }
}
// Вывод матрицы matrix размером rowCount x colCount
void printMatrix(int **matrix, int rowCount, int colCount)
{
    printf("Matrix elements:\n");
    for (int row = 0; row < rowCount; row++)
    {
        for (int column = 0; column < colCount; column++)
            printf("%d\t ", matrix[row][column]);
        printf("\n");
    }
}

// Освобождение памяти, занимаемой матрицой
void freeMatrixMemory(int **matrix, int rowCount)
{
    for (int i = 0; i < rowCount; i++)
        free(matrix[i]);
    free(matrix);
}

// Выделение памяти для матрицы
int allocMatrixMemory(int **matrix, int rowCount, int colCount)
{
    if (matrix == NULL)
    {
        printf("Error while allocating memory");
        return 1;
    }

    for (int i = 0; i < rowCount; i++)
    {
        matrix[i] = (int *)malloc(colCount * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Error while allocating memory");
            while (i > 0)
                free(matrix[--i]);
            free(matrix);
            return 1;
        }
    }
    return 0;
}

