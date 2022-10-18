#include "serializeList.h"


int* serializeListSolution(const void* list) {
  int count = 0;
  int totalLen = sizeof(int);
  int* base = malloc(totalLen);

  while (list != NULL) {
    char* currStr = (char*)list + sizeof(void*);
    int currLen = strlen(currStr) + 1;

    base = realloc(base, totalLen + currLen);
    strcpy((char*)base + totalLen, currStr);

    list = *(void**)list;
    totalLen += currLen;
    count++;
  }

  *base = count;
  return base;
}