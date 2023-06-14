#define MODEL_MAX 200
#define MANUFACTORER_MAX 200
#define CATEGORY_NAME_MAX 200

struct Car
{
    char model[MODEL_MAX];               // Модель
    char manufacturer[MANUFACTORER_MAX]; // Производитель
    int year;                            // Год выпуска
    double engineSize;                   // Объем двигателя
    double gasConsumption;               // Расход топлива на 100 км
    double price;                        // Цена
    int numberOfCopies;                  // Количество экземпляров
    struct Category
    {
        char name[CATEGORY_NAME_MAX]; // Наименование категории
        int categoryRating;           // Рейтинг категории
    } cat;                            // Категоря авто
};

struct Node // Узел списка
{
    struct Car *data;  // Данные узла
    struct Node *next; // Следующий элемент
};

struct List // Объект списка
{
    struct Node *head, *tail; // Первый, последний элемент списка
};

// Функция создания следующего элемента списка
void create(struct Car *car, struct List *g_list)
{
    // Выделение памяти под узел
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->data = car;              // Данные узла заполнить из аргументов
    n->next = NULL;             // Следующий узел пуст
    if (g_list->head == NULL)   // Если в списке нет первого элемента
        g_list->head = n;       // Текущий узел первый в списке
    if (g_list->tail != NULL)   // Если есть последний элемент в списке
        g_list->tail->next = n; // Созданный элемент - следующий для текущего последнего
    g_list->tail = n;           // Созданный элемент - последний в списке
}

// Функция удаления последнего элемента списка
void deleteLast(struct List *g_list)
{
    // Текущий узел
    struct Node *n;
    if (g_list->head == NULL) // Если первый элемент списка пуст
        return;               // Выход из функции, список пуст
    // Находим предпоследний элемент или останавливамся на первом и последнем
    for (n = g_list->head; n->next != NULL && n->next != g_list->tail; n = n->next)
        ;
    if (n->next) // Елси есть следующий элемент
    {
        free(g_list->tail); // Освободить память последнего элемента
        n->next = NULL;     // Удалить следующий узел для предпоследнего
        g_list->tail = n;   // Пердпоследний узел теперь последний
    }
    else
    {
        free(g_list->head);  // Освободить память первого и последнего элемента
        g_list->head = NULL; // Удалить первый узел
        g_list->tail = NULL; // Удалить последний узел
    }
}
// Функция заполнения списка из файла
void fillFromFile(FILE *file, struct List *g_list)
{
    // Выделение памяти под данные узла
    struct Car *newCar = (struct Car *)malloc(sizeof(struct Car));
    // Пока из файла считано значение
    if (fread(newCar, sizeof(struct Car), 1, file) == 1)
    {
        create(newCar, g_list);     // Создать узел
        fillFromFile(file, g_list); // Рекурсивный вызов
    }
}

// Функция сохранения списка в файле
void saveInFile(FILE *file, struct Node *curr)
{
    // Если узел и его данные не пусты
    if (curr != NULL && curr->data != NULL)
    {
        // Записать данные узла в файл
        if (fwrite(curr->data, sizeof(struct Car), 1, file) == 0)
        {
            // Если данные не записаны, выйти с ошибкой
            perror("Error while saving list to file.\n");
            exit(1);
        }
        // Рекурсивный вызов
        saveInFile(file, curr->next);
    }
}
