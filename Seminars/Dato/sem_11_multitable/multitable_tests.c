#include "multitable.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define ASSERT(expr) {							\
  if (!(expr)) {								\
    printf("%s:%d: Assertion failed: %s\n", __FILE__, __LINE__, #expr);	\
    return false;							\
  }									\
}


void Test(char* name, bool(*test_fn)()) {
  printf("++ RUNNING TEST: %s\n", name);
  if (test_fn()) {
    printf("-- TEST %s: SUCCEEDED\n", name);
  } else {
    printf("-- TEST %s: FAILED\n", name);
  }
  printf("\n");
}


static int intHashFunction(const void *elem, int numBuckets)
{
  int number = *(int *)elem;
  return (number % numBuckets);
}

static int stringHashFunction(const void *elem, int numBuckets)
{
  char *  str = *(char **)elem;
  return (strlen(str) % numBuckets);
}


static int intCompare(const void * elem1 , const void * elem2){
  int a = *(int *)elem1;
  int b = *(int *)elem2;
  return a - b;
}


static int stringCompare(const void * elem1 , const void * elem2){
  char * a = *(char **)elem1;
  char * b = *(char **)elem2;
  return strcmp(a , b);
}


static void increase(hashset * h , void * elem, void * auxdata){
  int * number = auxdata;
  (*number)++;
}


bool testConstructor1() {
        multitable mt;
	MultiTableNew(&mt, sizeof(int), sizeof(int), 4, intHashFunction, intCompare);
	return true;
}


bool testConstructor2() {
        multitable mt;
	MultiTableNew(&mt, sizeof(float), sizeof(float), 4, intHashFunction, intCompare);
	return true;
}

bool testConstructor3() {
        multitable mt;
	MultiTableNew(&mt, sizeof(short), sizeof(short), 4, intHashFunction, intCompare);
	return true;
}

bool testConstructor4(){
   multitable mt;
   MultiTableNew(&mt, sizeof(int), sizeof(float), 4, intHashFunction, intCompare);

   MultiTableNew(&mt, sizeof(short), sizeof(float), 4, intHashFunction, intCompare);

   MultiTableNew(&mt, sizeof(float), sizeof(int), 4, intHashFunction, intCompare);
   return true;
}


bool testConstructor5(){
   multitable mt;
   MultiTableNew(&mt, sizeof(char *), sizeof(char *), 4, stringHashFunction, stringCompare);
   return true;
}


bool testEnter1(){
   multitable mt;
   MultiTableNew(&mt, sizeof(int), sizeof(int), 4, intHashFunction, intCompare);
   for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &i, &i);
     hashset h = mt.mappings;
     if(HashSetCount(&h) != (i+1) && (HashSetLookup(&h, &i) == NULL)) return false;
   }
   return true; 
}


bool testEnter2(){
   multitable mt;
   MultiTableNew(&mt, sizeof(int), sizeof(int), 4, intHashFunction, intCompare);
   for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &i, &i);
     hashset h = mt.mappings;
     if(HashSetCount(&h) != (i+1) && (HashSetLookup(&h, &i) == NULL)) return false;
   }
   for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &i, &i);
     hashset h = mt.mappings;
     if(HashSetCount(&h) != 100 && (HashSetLookup(&h, &i) == NULL)) return false;
   }
   return true; 
}


bool testEnter3(){
   multitable mt;
   MultiTableNew(&mt, sizeof(char *), sizeof(int), 4, intHashFunction, intCompare);
   char * str = strdup("multitable");
   for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &str, &i);
     hashset h = mt.mappings;
     if(HashSetCount(&h) != 1 && (HashSetLookup(&h, &str) == NULL)) return false;
   }
   return true; 
}


bool testEnter4(){
   multitable mt;
   MultiTableNew(&mt, sizeof(int), sizeof(int), 4, intHashFunction, intCompare);
   int n = 1;
   for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &n, &i);
     hashset h = mt.mappings;
     if(HashSetCount(&h) != 1 && (HashSetLookup(&h, &n) == NULL)) return false;
   }
   vector * v = (int *)HashSetLookup(&mt.mappings, &n) + 1;
   if (VectorLength(v) != 100) return false;
   for (int i = 0 ; i < 100; i++){
     if(VectorSearch(v, &i, intCompare, 0, false) == -1) return false;
   }
   return true; 
}

bool testEnter5(){
   multitable mt;
   MultiTableNew(&mt, sizeof(char *), sizeof(char *), 4, intHashFunction, intCompare);
   char * str = strdup("");
   for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &str, &str);
     hashset h = mt.mappings;
     if(HashSetCount(&h) != 1 && (HashSetLookup(&h, &str) == NULL)) return false;
   }
   vector * v= (char **)HashSetLookup(&mt.mappings, &str) + 1;
   if (VectorLength(v) != 100) return false;
   return true; 
}


bool testMap(){
  multitable mt;
  MultiTableNew(&mt, sizeof(int), sizeof(int), 4, intHashFunction, intCompare);
  for(int i = 0 ; i < 100; i++){
     MultiTableEnter(&mt, &i, &i);
  }
  int number = 0;
  MultiTableMap(&mt, increase, &number);
  if (number == 100) return true;
  return false;
}



int main(){
  // Test("Constructor for integers.", testConstructor1);
  // Test("Constructor for floats.", testConstructor2);
  // Test("Constructor for shorts.", testConstructor3);
  // Test("Constructor for different types.", testConstructor4);
  // Test("Constructor for strings.", testConstructor5);
  Test("Enter different elements.", testEnter1);
  Test("Enter same elements.", testEnter2);
  Test("Enter strings.", testEnter3);
  Test("Enter key with multiple values." , testEnter4);
  Test("Enter empty strings." , testEnter5);
  Test("Count keys with map.", testMap);
  return 0;
}
