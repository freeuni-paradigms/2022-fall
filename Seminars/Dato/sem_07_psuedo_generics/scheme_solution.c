#include "scheme.h"

char* ConcatStrings(const char* first, const char* second) {
    char* result = malloc(strlen(first) + strlen(second) + 1);
    strcpy(result, first);
    strcat(result, second);
    return result;
}

char* ConcatAll(nodeType* list) {
    nodeType type = *list;

    switch (type) {
    case Nil:
    case Integer:
        return strdup("");
    case String:
        return strdup((char*)(list + 1));
    case List: {
        nodeType* first = *((nodeType**)(list + 1));
        nodeType* second = *(nodeType**)((char*)list + sizeof(nodeType) + sizeof(nodeType*));
        char* firstAns = ConcatAll(first);
        char* secondAns = ConcatAll(second);
        char* ans = ConcatStrings(firstAns, secondAns);
        free(firstAns);
        free(secondAns);
        return ans;
    }
    }
}
