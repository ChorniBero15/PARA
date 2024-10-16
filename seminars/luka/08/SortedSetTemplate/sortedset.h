#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int n;
} sortedset;

void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *), void (*freefn)(const void *));
bool SetAdd(sortedset *set, const void *elemPtr);
void *SetSearch(sortedset *set, const void *elemPtr);
