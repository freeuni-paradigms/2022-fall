#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void StackInit(Stack* s, int elem_size, FreeFn free_fn) {
  s->elem_size = elem_size;
  s->free_fn = free_fn;
  s->base = malloc(4 * s->elem_size);
  assert(s->base != NULL);
  s->alloc_len = 4;
  s->log_len = 0;
}

void StackDestroy(Stack* s) {
  if (s->free_fn != NULL) {
    for (int i = 0; i < s->log_len; i++) {
      void* elem = (char*)s->base + i * s->elem_size;
      s->free_fn(elem);
    }
  }
  free(s->base);
}

void StackPush(Stack* s, void* value) {
  if (s->log_len == s->alloc_len) {
    s->alloc_len *= 2;
    s->base = realloc(s->base, s->alloc_len * s->elem_size);
    assert(s->base != NULL);
  }
  void* elem = (char*)s->base + s->log_len * s->elem_size;
  memcpy(elem, value, s->elem_size);
  s->log_len++;
}

void StackPop(Stack* s, void* value) {
  assert(s->log_len > 0);
  s->log_len--;
  void* elem = (char*)s->base + s->log_len * s->elem_size;
  memcpy(value, elem, s->elem_size);
}
