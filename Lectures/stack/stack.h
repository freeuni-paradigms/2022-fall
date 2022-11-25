#ifndef STACK_H_
#define STACK_H_

typedef void(FreeFn)(void*);

typedef struct {
  void* base;
  int alloc_len;
  int log_len;
  int elem_size;
  FreeFn free_fn;
} Stack;

void StackInit(Stack* s, int elem_size, FreeFn free_fn);
void StackDestroy(Stack* s);
void StackPush(Stack* s, void* value);
void StackPop(Stack* s, void* value);

#endif // STACK_H_
