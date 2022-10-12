#include "sparsestringarray.h"


void StringFree(void* elemAddr){
    free(*(char**)elemAddr);
}
/**
* Function: SSANew
* ----------------
* Constructs the sparsestringarray addressed by the first argument to
* be of the specified length, using the specified group size to decide
* how many groups should be used to back the implementation. You can
* assume that arrayLength is greater than groupSize, and for simplicity you
* can also assume that groupSize divides evenly into arrayLength.
*/
void SSANew(sparsestringarray* ssa, int arrayLength, int groupSize) {
 	ssa->arrayLength = arrayLength;
	ssa->groupSize = groupSize;
	ssa->numGroups = arrayLength / groupSize;
	ssa->groups = malloc(ssa->numGroups * sizeof(group));
	assert(ssa->groups != NULL);


	for (int i = 0; i < ssa->numGroups; i++) {
		ssa->groups[i].bitmap = malloc(groupSize * sizeof(bool));
		memset(ssa->groups[i].bitmap, 0, groupSize * sizeof(bool));
		VectorNew(&ssa->groups[i].strings, sizeof(char*), StringFree, 1);
	}
}

/**
* Function: SSADispose
* --------------------
* Disposes of all the resources embedded within the addressed
* sparsestringarray that have built up over the course of its
* lifetime.
*/
void SSADispose(sparsestringarray* ssa) {
	for (int i = 0; i < ssa->numGroups; i++) {
		free(ssa->groups[i].bitmap);
		VectorDispose(&ssa->groups[i].strings);
	}
	free(ssa->groups);
}

/**
* Function: SSAInsert
* -------------------
* Inserts the C string addressed by str into the sparsestringarray addressed
* by ssa at the specified index. If some nonempty string already resides
* at the specified index, then it is replaced with the new one. Note that
* SSAInsert makes a deep copy of the string address by str.
*/
bool SSAInsert(sparsestringarray* ssa, int index, const char* str) {
}

/**
* Function: SSAMap
* ----------------
* Applies the specified mapping routine to every single index/string pair
* (along with the specified auxiliary data). Note that the mapping routine
* is called on behalf of all strings, both empty and nonempty.
*/
void SSAMap(sparsestringarray* ssa, SSAMapFunction mapfn, void* auxData) {
}


