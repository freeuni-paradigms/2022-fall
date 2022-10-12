#include "generic_sorted_set.h"
#include <stdio.h>

int cmpfn(const void* aPtr, const void* bPtr)
{
    int a = *(int*)aPtr;
    int b = *(int*)bPtr;

    // if (a == b)
    //     return 0;
    // if (a < b)
    //     return -1;
    // return 1;
    return a - b;
}

int main()
{
    // sortedset set;
    sortedset* set = malloc(sizeof(sortedset));

    SetNew(set, sizeof(int), &cmpfn);
    int a = 21;
    int b = 0;
    printf("Adding 21\n");
    SetAdd(set, &a);
    printf("Length: %d\n", set->logLen);
    printf("Searching 0 --- ");
    void* result = SetSearch(set, &b);
    if (result == NULL)
        printf("Element not found \n");

    printf("Searching 21 --- ");
    int* newResult = (int*)SetSearch(set, &a);
    printf("Element: %d\n", *newResult);
}