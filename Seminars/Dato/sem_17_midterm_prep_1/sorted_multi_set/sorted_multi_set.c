#include "sorted_multi_set.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void SortedMultiSetInit(SortedMultiSet* s, int elem_size, CmpFn cmp_fn, FreeFn free_fn) {
  // IMPLEMENT
}

void SortedMultiSetDestroy(SortedMultiSet* s) {
  // IMPLEMENT
}

int SortedMultiSetInsert(SortedMultiSet* s, void* elem) {
  // IMPLEMENT
}

void* SortedMultiSetGet(SortedMultiSet* s, int index) {
  // IMPLEMENT
  return NULL;
}


int SortedMultiSetGetCount(SortedMultiSet* s, void* elem) {
  // IMPLEMENT
  return -1;
}
