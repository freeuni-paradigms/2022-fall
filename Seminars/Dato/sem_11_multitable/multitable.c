#include "multitable.h"

void MultiTableNew(multitable* mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, MultiTableHashFunction hash, MultiTableCompareFunction compare) {
}

void MultiTableEnter(multitable* mt, const void* keyAddr, const void* valueAddr) {
}

void MultiTableMap(multitable* mt, MultiTableMapFunction map, void* auxData) {
}
