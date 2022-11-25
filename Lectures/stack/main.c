#include "stack.h"
#include <stdio.h>

void StrFree(void* elem) {
  free(*(char**)elem);
}

int main() {
  Stack s;
  StackInit(&s, sizeof(char*), StrFree);
  StackInit(&s, sizeof(int), NULL);
  StackInit(&s, sizeof(Fraction), NULL);
  StackInit(&s, sizeof(Student), StudentFree);
  for (int i = 0; i < 10; i++) {
    char tmp[5];
    sprintf(tmp, "%d", i);
    StackPush(&s, strdup(tmp));
  }
  for (int i = 0; i < 10; i++) {
    char tmp[5];
    StackPop(&s, tmp);
    printf("i: %d x: %s\n", i, tmp);
  }
  StackDestroy(&s);
  return 0;
}
