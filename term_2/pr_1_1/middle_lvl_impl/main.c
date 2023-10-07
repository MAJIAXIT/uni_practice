#include "head.h"

int main(int argc, char **argv)
{
    struct Car *_car;
    struct Node *n;
    char fileName[FILENAME_MAX];
    FILE *binFile;
    int ans;
    struct List *g_list = (struct List *)malloc(sizeof(struct List));

    if (g_list == NULL)
    {
        perror("Error while allocating memory.\n");
        exit(1);
    }

    // Если имя файла есть в аргументах main, скопировать из в fileName
    // Иначе задать константой
    if (argc > 1)
        strcpy(fileName, *++argv);
    else
        strcpy(fileName, "bindb.bin");

    // Открыть файл в режиме чтения, если файла нет, вывести сообщение
    // о пустом списке, иначе заполнить список данными из файла
    if ((binFile = fopen(fileName, "rb")) == NULL)
    {
        printf("File not exitst, continue with free list.\n");
        getchar();
    }
    else
    {
        fillFromFile(binFile, g_list);
        fclose(binFile);
    }

    do
    {
        system("clear");
        printf("1: Создать запись.\n");
        printf("2: Вывести все записи.\n");
        printf("3: Удалить последнюю запись.\n");
        printf("4: Изменить цену авто по номеру записи.\n");
        printf("5: Найти модель по объему двигателя.\n");
        printf("6: Выйти.\n");
        scanf("%d%*c", &ans);
        switch (ans)
        {
        case 1:
            _car = _inputCar();
            create(_car, g_list);
            break;
        case 2:
            _retrieveAll(g_list);
            break;
        case 3:
            _deleteLast(g_list);
            break;
        case 4:
            _updatePrice(g_list);
            break;
        case 5:
            _retrieveByEngineSize(g_list);
            break;
        }
    } while (ans < 6);

    // Открыть файл на записть
    if ((binFile = fopen(fileName, "wb")) == NULL)
    {
        fprintf(stderr, "Ошибка открытия файла: %s\n", fileName);
        exit(1);
    }
    // Сохранить записи в файл
    saveInFile(binFile, g_list->head);
    fclose(binFile);

    // Освободить память всех узлов и списка
    for (n = g_list->head; n != NULL; n = n->next)
    {
        free(n->data);
        free(n);
    }
    free(g_list);
    return 0;
}

struct Car *_inputCar(void)
{
    struct Car *newCar = (struct Car *)malloc(sizeof(struct Car));
    if (newCar == NULL)
    {
        perror("Ошибка выделения памяти.");
        exit(1);
    }

    fflush(stdin);
    printf("Введите модель машины:\n");
    scanf("%[^\n]%*c", newCar->model);
    printf("Введите производителя:\n");
    scanf("%[^\n]%*c", newCar->manufacturer);

    do
    {
        fflush(stdin);
        printf("Введите год выпуска: ");
        scanf("%d", &(newCar->year));
    } while (newCar->year < 1800 || newCar->year > 2023);

    do
    {
        fflush(stdin);
        printf("Введите объем двигателя: ");
        scanf("%lf", &(newCar->engineSize));
    } while (newCar->engineSize <= 0 || newCar->engineSize > 100);

    do
    {
        fflush(stdin);
        printf("Введите расход бензина на 100км: ");
        scanf("%lf", &(newCar->gasConsumption));
    } while (newCar->gasConsumption <= 0 || newCar->gasConsumption > 200);

    do
    {
        fflush(stdin);
        printf("Введите цену авто: ");
        scanf("%lf", &(newCar->price));
    } while (newCar->price <= 0 || newCar->price > 10000000);

    do
    {
        fflush(stdin);
        printf("Введите количество выпущенных экземпляров: ");
        scanf("%d", &(newCar->numberOfCopies));
    } while (newCar->numberOfCopies <= 0 || newCar->numberOfCopies > 10000000);

    fflush(stdin);
    printf("Введите категорию машины:\n");
    scanf("%[^\n]%*c", newCar->cat.name);

    do
    {
        fflush(stdin);
        printf("Рейтинг категории (1 - 10): ");
        scanf("%d", &(newCar->cat.categoryRating));
    } while (newCar->cat.categoryRating <= 0 || newCar->cat.categoryRating > 10);

    return newCar;
}

void _deleteLast(struct List *g_list)
{
    // Елси первый элемент пуст, список пуст,
    // выход из программы, удалять нечего
    if (g_list->head == NULL)
    {
        printf("Список пуст.\n");
        getchar();
        return;
    }
    deleteLast(g_list);
    printf("Запись удалена.\n");
    getchar();
}

void _printCar(struct Car *car, int num)
{
    printf("|%3d | %16s | %19s | %4d | %11.3lf | %13.3lf | %10.1lf | %12d | %14s | %6d |\n",
           num,
           car->model,
           car->manufacturer,
           car->year,
           car->engineSize,
           car->gasConsumption,
           car->price,
           car->numberOfCopies,
           car->cat.name,
           car->cat.categoryRating);
}

void _printTableHeader(void)
{
    printf("| N  |      Модель      |    Производитель    | Год  | Объем двиг. | Расх. топлива |    Цена    | Кол-во копий |    Категория   | rating |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void _retrieveAll(struct List *g_list)
{
    struct Node *n;
    int num;
    fflush(stdin);
    _printTableHeader();
    for (n = g_list->head, num = 1; n != NULL; n = n->next, num++)
        _printCar(n->data, num);
    printf("Enter any charecter to exit.\n");
    getchar();
}

void _updatePrice(struct List *g_list)
{
    struct Car *car;
    struct Node *n;
    int nToUpd, currNode, ans;

    do
    {
        fflush(stdin);
        printf("Введите номер записи для обновления: ");
        scanf("%d", &nToUpd);
    } while (nToUpd <= 0 || nToUpd > 10000000);

    for (n = g_list->head, currNode = 1; n != NULL; n = n->next, currNode++)
        if (currNode == nToUpd)
        {
            _printTableHeader();
            _printCar(n->data, currNode);
            printf("Изменить? (y/n): ");
            do
            {
                fflush(stdin);
                ans = getchar();
            } while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');
            if (ans == 'y' || ans == 'Y')
            {
                do
                {
                    fflush(stdin);
                    printf("Введите цену авто: ");
                    scanf("%lf", &(n->data->price));
                } while (n->data->price <= 0 || n->data->price > 10000000);
                printf("Запись успешно обновлена.\n");
                getchar();
                getchar();
                return;
            }
            else
                return;
        }
    printf("Записи с таким номером не существует.\n");
    getchar();
    getchar();
}

void _retrieveByEngineSize(struct List *g_list)
{
    struct Node *n, *nMinGasCons = NULL;
    double engineSize, currEnSize, minGasCons = 100000;
    int curr, ansNum;

    do
    {
        fflush(stdin);
        printf("Введите объем двигателя: ");
        scanf("%lf", &engineSize);
    } while (engineSize <= 0 || engineSize > 100);

    // Для каждого узла списка
    for (n = g_list->head, curr = 1; n != NULL; n = n->next, curr++)
    {
        // Объем двигателя текущей записи
        currEnSize = n->data->engineSize;
        // Если объем двигателя текущей записи равен искомой
        // И расход топлива наименьший
        if (abs(currEnSize - engineSize) <= 0.01 &&
            n->data->gasConsumption < minGasCons)
        {
            nMinGasCons = n;                      // Узел с наименьшим расходом топлива
            minGasCons = n->data->gasConsumption; // Минимальный расход топлива
            ansNum = curr;                        // Номер узла с наименьшим расходом топлива
        }
    }
    if (nMinGasCons == NULL)
    {
        printf("Машины с заданным объемом двигателя не найдено.\n");
        getchar();
        getchar();
        return;
    }
    _printTableHeader();
    _printCar(nMinGasCons->data, ansNum);
    getchar();
    getchar();
}