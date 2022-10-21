#include <stdbool.h>
#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include "hashset.h"
#include <stdio.h>


typedef struct {
  hashset mappings;
  int keySize;
  int valueSize;
} multitable;


/**
* Function: MultiTableNew
* -----------------------
* Initializes the raw space addressed by mt to be an empty
* multitable otherwise capable of storing keys and values of
* the specified sizes. The numBuckets, hash, and compare parameters
* are supplied with the understanding that they will simply be passed
* to HashSetNew, as the interface clearly advertises that a hashset
* is used. You should otherwise interact with the hashset (and any
* vectors) using only functions which have the authority to manipulate
* them.
*/

typedef int (*MultiTableHashFunction)(const void *keyAddr, int numBuckets);
typedef int (*MultiTableCompareFunction)(const void *keyAddr1, const void *keyAddr2);

void MultiTableNew(multitable *mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, MultiTableHashFunction hash, MultiTableCompareFunction compare);


/**
* Function: MultiTableEnter
* -------------------------
* Enters the specified key/value pair into the multitable.
* Duplicate values are permitted, so there's no need to search
* existing vectors for a match. You must handle the case where
* the key is being inserted for the very first time.
* Understand that the patterns for each key and value are replicated
* behind the scenes (using memcpy/memmove/VectorAppend as needed).
*/
void MultiTableEnter(multitable *mt, const void *keyAddr, const void *valueAddr);


/**
* Function: MultiTableMap
* -----------------------
* Applies the specified MultiTableMapFunction to each key/value pair
* stored inside the specified multitable. The auxData parameter
* is ultimately channeled in as the third parameter to every single
* invocation of the MultiTableMapFunction. Just to be clear, a
* multitable with seven keys, where each key is associated with
* three different values, would prompt MultiTableMap to invoke the
* specified MultiTableMapFunction twenty-one times.
*/

typedef void (*MultiTableMapFunction)(void *keyAddr, void *valueAddr, void *auxData);

void MultiTableMap(multitable *mt, MultiTableMapFunction map, void *auxData);
