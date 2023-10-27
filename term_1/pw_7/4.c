#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MODEL_MAX 200
#define MANUFACTORER_MAX 200
#define err(code, fileName)                                  \
    fprintf(stderr, "Не могу открыть файл: %s\n", fileName); \
    exit(code);
#define _abs(i) ((i) > 0 ? (i) : -(i))

struct car
{
    char model[MODEL_MAX];
    char manufacturer[MANUFACTORER_MAX];
    int year;
    double engineSize;
    double gasConsumption;
    double price;
    int numberOfCopies;
};

struct car inputCar(void);
void printCar(struct car);

void _create(char *);
void _retrieveAll(char *);
void _retrieveOne(char *);
void _update(char *);
void _delete(char *);
void _updatePrice(char *);

FILE *checkFile(char *, char *);

int main(int argc, char **argv)
{
    char fileName[FILENAME_MAX];
    int ans;
    FILE *file;

    if (argc > 1)
        strcpy(fileName, *++argv);
    else
    {
        printf("Enter file name:\n");
        scanf("%s", fileName);
    }

    file = checkFile(fileName, "ab");
    fclose(file);
    do
    {
        system("clear");
        printf("1: Создать запись.\n");
        printf("2: Изменить запись по номеру.\n");
        printf("3: Вывести все записи.\n");
        printf("4: Найти модель по объему двигателя.\n");
        printf("5: Удалить запись по номеру.\n");
        printf("6: Изменить цену авто по номеру записи.\n");
        printf("7: Выйти.\n");
        scanf("%d%*c", &ans);
        switch (ans)
        {
        case 1:
            _create(fileName);
            break;
        case 2:
            _update(fileName);
            break;
        case 3:
            _retrieveAll(fileName);
            break;
        case 4:
            _retrieveOne(fileName);
            break;
        case 5:
            _delete(fileName);
            break;
        case 6:
            _updatePrice(fileName);
            break;
        default:
            getchar();
            break;
        }
    } while (ans < 7);
    return 0;
}

FILE *checkFile(char *fileName, char *mode)
{
    FILE *file = fopen(fileName, mode);
    if (file == NULL)
    {
        fprintf(stderr, "Не могу открыть файл: %s\n", fileName);
        exit(4);
    }
    return file;
}

struct car inputCar(void)
{
    struct car newCar = {};
    fflush(stdin);
    printf("Введите модель машины:\n");
    scanf("%[^\n]%*c", newCar.model);
    printf("Введите производителя:\n");
    scanf("%[^\n]%*c", newCar.manufacturer);

    do
    {
        fflush(stdin);
        printf("Введите год выпуска: ");
        scanf("%d", &(newCar.year));
    } while (newCar.year < 1800 || newCar.year > 2023);

    do
    {
        fflush(stdin);
        printf("Введите объем двигателя: ");
        scanf("%lf", &(newCar.engineSize));
    } while (newCar.engineSize <= 0 || newCar.engineSize > 100);

    do
    {
        fflush(stdin);
        printf("Введите расход бензина на 100км: ");
        scanf("%lf", &(newCar.gasConsumption));
    } while (newCar.gasConsumption <= 0 || newCar.gasConsumption > 200);

    do
    {
        fflush(stdin);
        printf("Введите цену авто: ");
        scanf("%lf", &(newCar.price));
    } while (newCar.price <= 0 || newCar.price > 10000000);

    do
    {
        fflush(stdin);
        printf("Введите количество выпущенных экземпляров: ");
        scanf("%d", &(newCar.numberOfCopies));
    } while (newCar.numberOfCopies <= 0 || newCar.numberOfCopies > 10000000);

    fflush(stdin);
    return newCar;
}

void printCar(struct car _car)
{
    printf("Модель: %s\nПроизводитель: %s\nГод выпуска: %d\nОбъем двигателя: %.3lf\nРасход бензина на 100км: %.3lf\nЦена: %.3lf\nКоличество выпущенных копий: %d\n", _car.model, _car.manufacturer, _car.year, _car.engineSize, _car.gasConsumption, _car.price, _car.numberOfCopies);
}

void _create(char *fileName)
{
    struct car newCar = inputCar();
    FILE *file;
    file = checkFile(fileName, "ab+");
    fseek(file, 0, SEEK_END);
    fwrite(&newCar, sizeof(newCar), 1, file);
    fclose(file);
}

void _update(char *fileName)
{
    struct car _car;
    char yes;
    int number, recordsCount, count = 0;
    FILE *file;
    file = checkFile(fileName, "rb+");

    do
    {
        fflush(stdin);
        printf("Введите номер модели:\n");
        scanf("%d", &number);
    } while (number <= 0 || number > 1000000);

    fseek(file, 0, SEEK_END);
    recordsCount = ftell(file) / sizeof(struct car);
    rewind(file);

    if (number > recordsCount)
    {
        fflush(stdin);
        printf("Модели с таким номером не найдено.\n");
        getchar();
        return;
    }

    while (fread(&_car, sizeof(_car), 1, file))
    {
        if (++count == number)
        {
            printCar(_car);
            printf("Изменить? (y/n): ");
            do
            {
                fflush(stdin);
                yes = getchar();
            } while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
            if (yes == 'y' || yes == 'Y')
            {
                _car = inputCar();
                fseek(file, -sizeof(_car), SEEK_CUR);
                fwrite(&_car, sizeof(_car), 1, file);
            }
        }
    }
    fclose(file);
}

#define PAGES 100

void _retrieveAll(char *fileName)
{
    fpos_t pages[PAGES] = {};
    struct car _car;
    int curr = 0, ch, pagesIdx = 0, currPage, n, recOnScr;
    FILE *file;
    file = checkFile(fileName, "rb");

    do
    {
        fflush(stdin);
        printf("Сколько записей на странице? ");
        scanf("%d", &recOnScr);
    } while (recOnScr <= 0 || recOnScr > PAGES);

    rewind(file);
    fgetpos(file, &pages[pagesIdx++]);

    while (fread(&_car, sizeof(_car), 1, file) && pagesIdx < PAGES)
        if (++curr % recOnScr == 0)
            fgetpos(file, &pages[pagesIdx++]);
    if (curr % recOnScr == 0)
        pagesIdx--;

    currPage = 0;
    for (;;)
    {
        system("clear");
        printf("Используйте символы < > для перемещени между страницами. Для выхода введите латинскую x\n\n");
        printf("| N  |      Модель      |    Производитель    | Год  | Объем двиг. | Расх. топлива |    Цена    | Кол-во копий |\n");
        printf("----------------------------------------------------------------------------------------------------------------\n");
        curr = 0;
        n = recOnScr * currPage + 1;
        fsetpos(file, &pages[currPage]);
        while (curr++ < recOnScr && fread(&_car, sizeof(_car), 1, file))
            printf("|%3d | %16s | %19s | %4d | %11.3lf | %13.3lf | %10.1lf | %12d |\n", n++, _car.model, _car.manufacturer, _car.year, _car.engineSize, _car.gasConsumption, _car.price, _car.numberOfCopies);

        switch (ch = getchar())
        {
        case '>':
            if (currPage == pagesIdx - 1)
                break;
            else
                currPage++;
            break;
        case '<':
            if (currPage == 0)
                break;
            else
                currPage--;
            break;
        case 'x':
            fclose(file);
            return;
            break;
        default:
            break;
        }
    }
}

void _retrieveOne(char *fileName)
{
    struct car _car, requiredCar;
    double _engineSize, min_gasCons = 1000000;
    FILE *file;
    file = checkFile(fileName, "rb");

    do
    {
        fflush(stdin);
        printf("Введите объем двигателя:\n");
        scanf("%lf", &_engineSize);
    } while (_engineSize <= 0 || _engineSize > 100);

    rewind(file);
    while (fread(&_car, sizeof(_car), 1, file))
    {
        if (_abs(_car.engineSize - _engineSize) < 0.001 && _car.gasConsumption < min_gasCons)
        {
            requiredCar = _car;
            min_gasCons = _car.gasConsumption;
        }
    }
    if (min_gasCons == 1000000)
        printf("Машины с таким объемом двигателя не найдено.\n");
    else
        printCar(requiredCar);
    fflush(stdin);
    getchar();
    fclose(file);
}

void _delete(char *fileName)
{
    struct car _car;
    long recordsCount;
    int recToDelete, count = 0;
    FILE *tempFile, *file;
    file = checkFile(fileName, "rb");

    fseek(file, 0, SEEK_END);
    recordsCount = ftell(file) / sizeof(struct car);
    rewind(file);
 
    do
    {
        fflush(stdin);
        printf("Введите номер модели для удаления:\n");
        scanf("%d", &recToDelete);
    } while (recToDelete <= 0 || recToDelete > 100000);

    if (recToDelete > recordsCount)
    {
        printf("Модели с таким номером не существует.\n");
        fclose(file);
        fflush(stdin);
        getchar();
        return;
    }
    tempFile = checkFile("tempFile.bin", "ab+");

    while (fread(&_car, sizeof(_car), 1, file))
    {
        count++;
        if (count != recToDelete)
            fwrite(&_car, sizeof(_car), 1, tempFile);
    }
    fclose(file);
    remove(fileName);
    rename("tempFile.bin", fileName);
    fclose(tempFile);
    printf("Запись удалена.\n");
    fflush(stdin);
    getchar();
}

void _updatePrice(char *fileName)
{
    FILE *file;
    struct car _car;
    char yes;
    int recordsCount, recToUpdate, count = 0;

    file = checkFile(fileName, "rb+");
    fseek(file, 0, SEEK_END);
    recordsCount = ftell(file) / sizeof(struct car);
    rewind(file);

    do
    {
        fflush(stdin);
        printf("Введите номер модели для обновления цены: ");
        scanf("%d", &recToUpdate);
    } while (recToUpdate <= 0 || recToUpdate > 100000);

    if (recToUpdate > recordsCount)
    {
        printf("Модели с таким номером не существует.\n");
        fclose(file);
        fflush(stdin);
        getchar();
        return;
    }

    while (fread(&_car, sizeof(_car), 1, file))
    {
        if (++count == recToUpdate)
        {
            printCar(_car);
            printf("Изменить? (y/n): ");
            do
            {
                fflush(stdin);
                yes = getchar();
            } while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
            if (yes == 'y' || yes == 'Y')
            {
                do
                {
                    fflush(stdin);
                    printf("Введите цену авто: ");
                    scanf("%lf", &(_car.price));
                } while (_car.price <= 0 || _car.price > 10000000);

                fseek(file, -sizeof(_car), SEEK_CUR);
                fwrite(&_car, sizeof(_car), 1, file);
            }
        }
    }
    fclose(file);
}