#define MODEL_MAX 200
#define MANUFACTORER_MAX 200

struct Car
{
    char model[MODEL_MAX];
    char manufacturer[MANUFACTORER_MAX];
    int year;
    double engineSize;
    double gasConsumption;
    double price;
    int numberOfCopies;
};

struct Node
{
    struct Car *data;
    struct Node *prev, *next;
};

void create(struct Car *);
void delete(struct Node *);
void update(struct Node *, struct Car *);
void fillFromFile(FILE *);
void saveInFile(FILE *, struct Node *);

struct list
{
    struct Node *head, *tail;
    void (*create)(struct Car *);
    void (*delete)(struct Node *);
    void (*update)(struct Node *, struct Car *);
    void (*fillFromFile)(FILE *);
    void (*saveInFile)(FILE *, struct Node *);
} g_list = {NULL, NULL, &create, &delete, &update, &fillFromFile, &saveInFile};

void fillFromFile(FILE *file)
{
    struct Car *newCar = (struct Car *)malloc(sizeof(struct Car));
    if (fread(newCar, sizeof(struct Car), 1, file) == 1)
    {
        g_list.create(newCar);
        fillFromFile(file);
    }
}

void saveInFile(FILE *file, struct Node *curr)
{
    if (curr != NULL && curr->data != NULL)
    {
        fwrite(curr->data, sizeof(struct Car), 1, file);
        saveInFile(file, curr->next);
    }
}

void create(struct Car *car)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->data = car;
    n->next = NULL;
    n->prev = NULL;
    if (g_list.head == NULL)
        g_list.head = n;
    if (g_list.tail != NULL)
    {
        n->prev = g_list.tail;
        g_list.tail->next = n;
    }
    g_list.tail = n;
}

void delete(struct Node *n)
{
    if (n->prev)
        n->prev->next = n->next;
    if (n->next)
        n->next->prev = n->prev;
    if (n == g_list.head)
        g_list.head = NULL;
    if (n == g_list.tail)
        g_list.tail = NULL;
    free(n->data);
    n->data = NULL;
    free(n);
    n = NULL;
}

void update(struct Node *n, struct Car *new)
{
    free(n->data);
    n->data = new;
}
