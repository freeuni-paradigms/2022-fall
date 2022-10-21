#include "multitable.h"

void MultiTableNew(multitable* mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, MultiTableHashFunction hash, MultiTableCompareFunction compare) {
    mt->keySize = keySizeInBytes;
    mt->valueSize = valueSizeInBytes;
    HashSetNew(&mt->mappings, keySizeInBytes + sizeof(vector), numBuckets, hash, compare, NULL);
}


void MultiTableEnter(multitable* mt, const void* keyAddr, const void* valueAddr) {
    void* elem = HashSetLookup(&mt->mappings, keyAddr);

    if (elem == NULL) {
        elem = malloc(mt->keySize + sizeof(vector));
        memcpy(elem, keyAddr, mt->keySize);
        VectorNew((vector*)((char*)elem + mt->keySize), mt->valueSize, NULL, 1);
        VectorAppend((vector*)((char*)elem + mt->keySize), valueAddr);
        HashSetEnter(&mt->mappings, elem);
        // free(elem);
    }
    else {
        VectorAppend((vector*)((char*)elem + mt->keySize), valueAddr);
    }
}


typedef struct {
    int keySize;
    MultiTableMapFunction mapFn;
    void* auxData;
} mtAuxData;

static void HashSetMapFunc(void* elemAddr, void* auxData) {
    mtAuxData mtAux = *(mtAuxData*)auxData;
    vector* values = (vector*)((char*)elemAddr + mtAux.keySize);

    for (int i = 0; i < VectorLength(values); i++) {
        mtAux.mapFn(elemAddr, VectorNth(values, i), mtAux.auxData);
    }
}

void MultiTableMap(multitable* mt, MultiTableMapFunction map, void* auxData) {
    mtAuxData mtAux = { mt->keySize, map, auxData };
    HashSetMap(&mt->mappings, HashSetMapFunc, &mtAux);
}
