#include "sorted_multi_set.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void SortedMultiSetInit(SortedMultiSet* s, int elem_size, CmpFn cmp_fn, FreeFn free_fn) {
  VectorInit(&s->v, elem_size, free_fn);
  VectorInit(&s->counts, sizeof(int), NULL);
  s->cmp_fn = cmp_fn;
  s->elem_size = elem_size;
  s->free_fn = free_fn;
}

void SortedMultiSetDestroy(SortedMultiSet* s) {
  VectorDestroy(&s->v);
  VectorDestroy(&s->counts);
}

typedef struct {
  void* elem;
  int index;
  CmpFn cmp_fn;
  bool contains;
} InsertAux;

static void InsertMapFn(int index, void* elem, void* aux) {
  InsertAux* auxData = (InsertAux*)aux;
  if (auxData->index != -1) return;
  int cmp_res = auxData->cmp_fn(auxData->elem, elem);

  if (cmp_res == 0) {
    auxData->contains = true;
    auxData->index = index;
  }
  else if (cmp_res < 0) {
    auxData->index = index;
  }
}

static void IncrementCountMapFn(int index, void* elem, void* aux) {
  int update_index = *(int*)aux;
  if (index == update_index) {
    int curr_count = *(int*)elem;
    *(int*)elem = curr_count + 1;
  }
}

int SortedMultiSetInsert(SortedMultiSet* s, void* elem) {
  InsertAux auxData;
  auxData.cmp_fn = s->cmp_fn;
  auxData.elem = elem;
  auxData.index = -1;
  auxData.contains = false;
  VectorMap(&s->v, InsertMapFn, &auxData);
  if (!auxData.contains) {
    if (auxData.index == -1) auxData.index = VectorSize(&s->v);
    VectorInsert(&s->v, auxData.index, elem);
    int tmp = 1;
    VectorInsert(&s->counts, auxData.index, &tmp);
  }
  else {
    if (s->free_fn != NULL) s->free_fn(elem);
    VectorMap(&s->counts, IncrementCountMapFn, &auxData.index);
  }
  return auxData.index;
}

typedef struct {
  int index;
  void* elem;
} GetAux;

static void GetElemMapFn(int index, void* elem, void* aux) {
  GetAux* auxData = (GetAux*)aux;
  if (auxData->index == index) {
    auxData->elem = elem;
  }
}

void* SortedMultiSetGet(SortedMultiSet* s, int index) {
  GetAux auxData;
  auxData.index = index;
  VectorMap(&s->v, GetElemMapFn, &auxData);
  return auxData.elem;
}

typedef struct {
  void* elem;
  int index;
  CmpFn cmp_fn;
} GetCountAux;

static void GetCountMapFn(int index, void* elem, void* aux) {
  GetCountAux* auxData = (GetCountAux*)aux;
  if (auxData->index != -1) return;
  int cmp_res = auxData->cmp_fn(auxData->elem, elem);

  if (cmp_res == 0) {
    auxData->index = index;
  }
}

typedef struct {
  int index;
  int count;
} GetCountVecAux;

static void GetCountVecMapFn(int index, void* elem, void* aux) {
  GetCountVecAux* auxData = (GetCountVecAux*)aux;
  if (index == auxData->index) {
    auxData->count = *(int*)elem;
  }
}

int SortedMultiSetGetCount(SortedMultiSet* s, void* elem) {
  GetCountAux auxData;
  auxData.cmp_fn = s->cmp_fn;
  auxData.elem = elem;
  auxData.index = -1;
  VectorMap(&s->v, GetCountMapFn, &auxData);
  GetCountVecAux vecAuxData;
  vecAuxData.index = auxData.index;
  vecAuxData.count = 0;
  VectorMap(&s->counts, GetCountVecMapFn, &vecAuxData);
  return vecAuxData.count;
}
