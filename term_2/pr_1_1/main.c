#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obj.c"

#define abs(a) (a >= 0 ? a : -(a))

struct Car *_inputCar(void);
void _printCar(struct Car *, int);
void _retrieveAll(void);
void _delete(void);
void _update(void);
void _retrieveByEngineSize(void);
void _printTableHeader(void);

struct Car *testInputCar(void);

int main(int argc, char **argv)
{
    struct Car *_car;
    char fileName[FILENAME_MAX];
    FILE *binFile;
    int ans;

    if (argc > 1)
        strcpy(fileName, *++argv);
    else
        strcpy(fileName, "bindb.bin");

    if ((binFile = fopen(fileName, "ab+")) == NULL)
    {
        fprintf(stderr, "Ошибка открытия файла: %s\n", fileName);
        exit(1);
    }
    rewind(binFile);
    g_list.fillFromFile(binFile);
    fclose(binFile);

    do
    {
        system("clear");
        printf("1: Создать запись.\n");
        printf("2: Вывести все записи.\n");
        printf("3: Удалить запись по номеру.\n");
        printf("4: Изменить авто по номеру записи.\n");
        printf("5: Найти модель по объему двигателя.\n");
        printf("6: Выйти.\n");
        scanf("%d%*c", &ans);
        switch (ans)
        {
        case 1:
            _car = _inputCar();
            g_list.create(_car);
            break;
        case 2:
            _retrieveAll();
            break;
        case 3:
            _delete();
            break;
        case 4:
            _update();
            break;
        case 5:
            _retrieveByEngineSize();
            break;
        }
    } while (ans < 6);

    if ((binFile = fopen(fileName, "wb")) == NULL)
    {
        fprintf(stderr, "Ошибка открытия файла: %s\n", fileName);
        exit(1);
    }
    g_list.saveInFile(binFile, g_list.head);
    fclose(binFile);
    return 0;
}

struct Car *_inputCar(void)
{
    struct Car *newCar = (struct Car *)malloc(sizeof(struct Car));
    int ch;
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
    return newCar;
}

void _delete(void)
{
    int nToDel, nNum;
    struct Node *n;
    printf("Введите номер записи для удаления: ");
    scanf("%d", &nToDel);
    for (n = g_list.head, nNum = 1; n != NULL; n = n->next, nNum++)
        if (nNum == nToDel)
        {
            g_list.delete(n);
            fflush(stdin);
            printf("Запись с номером %d удалена.\n", nToDel);
            getchar();
            return;
        }
    fflush(stdin);
    printf("Записи с таким номером не существует.\n");
    getchar();
}

void _printCar(struct Car *car, int num)
{
    printf("|%3d | %16s | %19s | %4d | %11.3lf | %13.3lf | %10.1lf | %12d |\n",
           num,
           car->model,
           car->manufacturer,
           car->year,
           car->engineSize,
           car->gasConsumption,
           car->price,
           car->numberOfCopies);
}

void _printTableHeader(void)
{
    printf("| N  |      Модель      |    Производитель    | Год  | Объем двиг. | Расх. топлива |    Цена    | Кол-во копий |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
}

void _retrieveAll(void)
{
    struct Node *n;
    int num;
    fflush(stdin);
    _printTableHeader();
    for (n = g_list.head, num = 1; n != NULL; n = n->next, num++)
        _printCar(n->data, num);
    getchar();
}

void _update(void)
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

    for (n = g_list.head, currNode = 1; n != NULL; n = n->next, currNode++)
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
                car = _inputCar();
                g_list.update(n, car);
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

void _retrieveByEngineSize(void)
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

    for (n = g_list.head, curr = 1; n != NULL; n = n->next, curr++)
    {
        currEnSize = n->data->engineSize;
        if (abs(currEnSize - engineSize) <= 0.01 &&
                n->data->gasConsumption < minGasCons)
        {
            nMinGasCons = n;
            minGasCons = n->data->gasConsumption;
            ansNum = curr;
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