#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODEL_MAX 200
#define MANUFACTORER_MAX 200
#define CATEGORY_NAME_MAX 200

#define abs(a) (a >= 0 ? a : -(a))

struct Car *_inputCar(void);
void _printCar(struct Car *, int);
void _retrieveAll(struct List *);
void _deleteLast(struct List *);
void _updatePrice(struct List *);
void _retrieveByEngineSize(struct List *);
void _printTableHeader(void);
