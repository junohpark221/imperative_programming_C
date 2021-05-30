#include <stdbool.h>

typedef char name;
typedef char number;

struct node;
typedef struct node node;

struct hash;
typedef struct hash hash;

list *newList(item d);

void freeList(list *l);

void startF(list *l);
void startB(list *l);

bool endF(list *l);
bool endB(list *l);

bool nextF(list *l);
bool nextB(list *l);

void insertF(list *l, item x);
void insertB(list *l, item x);

item getF(list *l);
item getB(list *l);

bool setF(list *l, item x);
bool setB(list *l, item x);

bool deleteF(list *l);
bool deleteB(list *l);
