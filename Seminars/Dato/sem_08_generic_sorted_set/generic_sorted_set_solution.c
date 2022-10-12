#include "generic_sorted_set.h"

#define NodeSize(elemSize) ((elemSize) + 2 * sizeof(int))


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
void SetNew(sortedset* set, int elemSize, int (*cmpfn)(const void*, const void*)) {
    assert(cmpfn != NULL);
    assert(elemSize > 0);

    set->allocLen = kInitialCapacity;
    set->base = malloc(sizeof(int) + NodeSize(elemSize) * set->allocLen);
    set->cmpfn = cmpfn;
    set->elemSize = elemSize;
    set->logLen = 0;
    *(int*)set->base = -1;
}

static int* FindNode(sortedset* set, const void* elemPtr) {
    int* nextIndexPtr = (int*)set->base;

    while (*nextIndexPtr != -1) {
        void* elem = (char*)set->base + sizeof(int) + NodeSize(set->elemSize) * (*nextIndexPtr);
        int cmpRes = set->cmpfn(elem, elemPtr);
        if (cmpRes == 0) {
            return nextIndexPtr;
        }
        else if (cmpRes > 0) {
            elem = (char*)elem + set->elemSize;
        }
        else {
            elem = (char*)elem + set->elemSize + sizeof(int);
        }
        nextIndexPtr = (int*)elem;
    }

    return nextIndexPtr;
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
void* SetSearch(sortedset* set, const void* elemPtr) {
    int* indexPtr = FindNode(set, elemPtr);
    int index = *indexPtr;
    if (index == -1) return NULL;
    return (char*)set->base + sizeof(int) + NodeSize(set->elemSize) * index;

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
bool SetAdd(sortedset* set, const void* elemPtr) {
    int* indexPtr = FindNode(set, elemPtr);

    if (*indexPtr != -1) {
        return false;
    }

    if (set->logLen == set->allocLen) {
        set->allocLen *= 2;
        set->base = realloc(set->base, sizeof(int) + set->allocLen * NodeSize(set->elemSize));
        assert(set->base != NULL);
    }


    *indexPtr = set->logLen;
    void* elem = (char*)set->base + sizeof(int) + NodeSize(set->elemSize) * set->logLen;
    memcpy(elem, elemPtr, set->elemSize);

    int* childrenPtr = (int*)((char*)elem + set->elemSize);
    childrenPtr[0] = -1;
    childrenPtr[1] = -1;

    set->logLen++;
    
    return true;
}

