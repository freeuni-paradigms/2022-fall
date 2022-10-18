#include "sparsestringarray.h"


static void StringFree(void* elem) {
	free(*(char**)elem);
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
	int groupNum = index / ssa->groupSize;
	int indexInGroup = index % ssa->groupSize;
	group* curr_group = &ssa->groups[groupNum];
	char* elem = strdup(str);

	int indexInVector = 0;
	for (int i = 0; i < indexInGroup; i++) {
		if (curr_group->bitmap[i])
			indexInVector++;
	}

	if (curr_group->bitmap[indexInGroup]) {
		VectorReplace(&ssa->groups[groupNum].strings, &elem, indexInVector);
		return false;
	}

	VectorInsert(&curr_group->strings, &elem, VectorLength(&curr_group->strings));
	curr_group->bitmap[indexInGroup] = true;
	return true;
}

/**
* Function: SSAMap
* ----------------
* Applies the specified mapping routine to every single index/string pair
* (along with the specified auxiliary data). Note that the mapping routine
* is called on behalf of all strings, both empty and nonempty.
*/
void SSAMap(sparsestringarray* ssa, SSAMapFunction mapfn, void* auxData) {
	int index = 0;
	for (int i = 0; i < ssa->numGroups; i++) {
		int indexInVector = 0;
		for (int j = 0; j < ssa->groupSize; j++) {
			const char* str = "";
			if (ssa->groups[i].bitmap[j]) {
				str = *(char**)VectorNth(&ssa->groups[i].strings, indexInVector);
				indexInVector++;
			}
			mapfn(index, str, auxData);
			index++;
		}
	}
}


