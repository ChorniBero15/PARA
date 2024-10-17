#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    void* base;
    int logLength;
    int allLength;
    int elemSize;
    int (*cmpfn)(const void *, const void *);
    void (*freefn)(const void *);
} sortedset;

void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *), void (*freefn)(const void *));
bool SetAdd(sortedset *set, const void *elemPtr);
void *SetSearch(sortedset *set, const void *elemPtr);
static int* find(sortedset* set, const void* elemPtr);
