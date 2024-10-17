#include "sortedset.h"

/*
* Function: SetNew
* Usage: SetNew(&stringSet, sizeof(char *), StringPtrCompare);
*
SetNew(&constellations, sizeof(pointT), DistanceCompare);
* ----------------
* SetNew allocates the requisite space needed to manage what
* will initially be an empty sorted set. More specifically, the
* routine allocates space to hold up to 'kInitialCapacity' (currently 4)
* client elements.
*/


static const int kInitialCapacity = 4;
void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *), void (*freefn)(const void *))
{
    set->base = malloc(kInitialCapacity * (elemSize + 2*sizeof(int)) + sizeof(int));
    assert(set->base);

    set->elemSize = elemSize;
    set->allLength = kInitialCapacity;
    set->logLength = 0;
    set->cmpfn = cmpfn;
    set->freefn = freefn;

    *(int*)set->base = -1;
} 

/*
* Function: SetSearch
* Usage: if (SetSearch(&staffSet, &lecturer) == NULL)
*
printf("musta been fired");
* -------------------
* SetSearch searches for the specified client element according
* the whatever comparison function was provided at the time the
* set was created. A pointer to the matching element is returned
* for successful searches, and NULL is returned to denote failure.
*/
void *SetSearch(sortedset *set, const void *elemPtr)
{
    int* indx = find(set, elemPtr);

    if(*indx == -1) return NULL;

    void* ans = (char*)set->base + sizeof(int) + ((*indx) * (set->elemSize + 2*sizeof(int)));

    return ans;
}
/*
* Function: SetAdd
* Usage: if (!SetAdd(&friendsSet, &name)) free(name);
* ----------------
* Adds the specified element to the set if not already present.
* present, the client element is not copied into the set. true
* is returned if and only if the element at address elemPtr
* was copied into the set.
*/
bool SetAdd(sortedset *set, const void *elemPtr)
{
    int* indx = find(set, elemPtr);

    if(*indx != -1) return false;

    *indx = set->logLength;

    if(set->logLength == set->allLength) {
        set->allLength *= 2;

        set->base = realloc(set->base, (sizeof(int) + set->allLength * (set->elemSize + 2*sizeof(int))));

        assert(set->base);
    }

    void* newNode = (char*)set->base + sizeof(int) + set->logLength * (set->elemSize + 2*sizeof(int));

    memcpy(newNode, elemPtr, set->elemSize);

    newNode = (char*)newNode + set->elemSize;
    *(int*)newNode = -1;
    newNode = (int*)newNode + 1;
    *(int*)newNode = -1;

    set->logLength++;

    return true;
}

static int* find(sortedset* set, const void* elemPtr) {
    int* curr = set->base;

    while(true) {
        if(*curr == -1) return curr;

        void* currNode = (char*)set->base + sizeof(int) + ((*curr) * (set->elemSize + 2*sizeof(int)));

        int res = set->cmpfn(elemPtr, currNode); // marcxniv mcire

        if(res == 0) return curr;
    
        if(res < 0) {
            curr = (char*)currNode + set->elemSize;
            continue;
        } 

        curr = (char*)currNode + set->elemSize + sizeof(int);
    }

    assert(0);
    return NULL;
}

