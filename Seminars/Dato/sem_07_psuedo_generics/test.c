#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "scheme.h"

//DO NOT WRITE CODE LIKE THIS XD

void test1() {
    // create nodeType list (2 3 5 7)
    nodeType* onlyInts = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyInts = List;
    nodeType** onlyIntsPtr = (nodeType**)(onlyInts + 1);
    onlyIntsPtr[0] = malloc(sizeof(nodeType) + sizeof(int));
    onlyIntsPtr[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyIntsPtr[0] = Integer;
    *(int*)(onlyIntsPtr[0] + 1) = 2;
    *onlyIntsPtr[1] = List;
    nodeType** onlyIntsPtr2 = (nodeType**)(onlyIntsPtr[1] + 1);
    onlyIntsPtr2[0] = malloc(sizeof(nodeType) + sizeof(int));
    onlyIntsPtr2[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyIntsPtr2[0] = Integer;
    *(int*)(onlyIntsPtr2[0] + 1) = 3;
    *onlyIntsPtr2[1] = List;
    nodeType** onlyIntsPtr3 = (nodeType**)(onlyIntsPtr2[1] + 1);
    onlyIntsPtr3[0] = malloc(sizeof(nodeType) + sizeof(int));
    onlyIntsPtr3[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyIntsPtr3[0] = Integer;
    *(int*)(onlyIntsPtr3[0] + 1) = 5;
    *onlyIntsPtr3[1] = List;
    nodeType** onlyIntsPtr4 = (nodeType**)(onlyIntsPtr3[1] + 1);
    onlyIntsPtr4[0] = malloc(sizeof(nodeType) + sizeof(int));
    onlyIntsPtr4[1] = malloc(sizeof(nodeType));
    *onlyIntsPtr4[0] = Integer;
    *(int*)(onlyIntsPtr4[0] + 1) = 7;

    *onlyIntsPtr4[1] = Nil;

    // test concatall
    char* result = ConcatAll(onlyInts);
    printf("-----------TEST 1-----------\n\n");
    printf("Testing on list: (2 3 5 7)...\n");
    if (strcmp(result, "") != 0) {
        printf("TEST 1 FAILED: expected \"\", got \"%s\"\n\n", result);
    }
    else {
        printf("TEST 1 PASSED\n\n");
    }


    // free memory
    free(result);
    free(onlyIntsPtr4[0]);
    free(onlyIntsPtr4[1]);
    free(onlyIntsPtr3[1]);
    free(onlyIntsPtr3[0]);
    free(onlyIntsPtr2[1]);
    free(onlyIntsPtr2[0]);
    free(onlyIntsPtr[1]);
    free(onlyIntsPtr[0]);
    free(onlyInts);
}

void test2() {
    // create nodeType list ("House" "at" "Pooh" "Corner")
    nodeType* onlyStrings = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyStrings = List;
    nodeType** onlyStringsPtr = (nodeType**)(onlyStrings + 1);
    onlyStringsPtr[0] = malloc(sizeof(nodeType) + sizeof(char) * 6);
    onlyStringsPtr[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyStringsPtr[0] = String;
    strcpy((char*)(onlyStringsPtr[0] + 1), "House");
    *onlyStringsPtr[1] = List;
    nodeType** onlyStringsPtr2 = (nodeType**)(onlyStringsPtr[1] + 1);
    onlyStringsPtr2[0] = malloc(sizeof(nodeType) + sizeof(char) * 3);
    onlyStringsPtr2[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyStringsPtr2[0] = String;
    strcpy((char*)(onlyStringsPtr2[0] + 1), "at");
    *onlyStringsPtr2[1] = List;
    nodeType** onlyStringsPtr3 = (nodeType**)(onlyStringsPtr2[1] + 1);
    onlyStringsPtr3[0] = malloc(sizeof(nodeType) + sizeof(char) * 5);
    onlyStringsPtr3[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *onlyStringsPtr3[0] = String;
    strcpy((char*)(onlyStringsPtr3[0] + 1), "Pooh");
    *onlyStringsPtr3[1] = List;
    nodeType** onlyStringsPtr4 = (nodeType**)(onlyStringsPtr3[1] + 1);
    onlyStringsPtr4[0] = malloc(sizeof(nodeType) + sizeof(char) * 7);
    onlyStringsPtr4[1] = malloc(sizeof(nodeType));
    *onlyStringsPtr4[0] = String;
    strcpy((char*)(onlyStringsPtr4[0] + 1), "Corner");

    *onlyStringsPtr4[1] = Nil;

    // test concatall
    char* result = ConcatAll(onlyStrings);
    printf("-----------TEST 2-----------\n\n");
    printf("Testing on list: (House at Pooh Corner)...\n");
    if (strcmp(result, "HouseatPoohCorner") != 0) {
        printf("TEST 2 FAILED: expected \"HouseatPoohCorner\", got \"%s\"\n\n", result);
    }
    else {
        printf("TEST 2 PASSED\n\n");
    }


    // free memory
    free(result);
    free(onlyStringsPtr4[0]);
    free(onlyStringsPtr4[1]);
    free(onlyStringsPtr3[1]);
    free(onlyStringsPtr3[0]);
    free(onlyStringsPtr2[1]);
    free(onlyStringsPtr2[0]);
    free(onlyStringsPtr[1]);
    free(onlyStringsPtr[0]);
    free(onlyStrings);
}

void test3() {
    // create nodeType list ("Yankees" 2 "Diamondbacks" 1)

    nodeType* mixed = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *mixed = List;
    //mixedPtr -> str*(Yankees) , ls1*
    nodeType** mixedPtr = (nodeType**)(mixed + 1);
    mixedPtr[0] = malloc(sizeof(nodeType) + sizeof(char) * 8);
    mixedPtr[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *mixedPtr[0] = String;
    strcpy((char*)(mixedPtr[0] + 1), "Yankees");
    *mixedPtr[1] = List;
    //mixedPtr2 -> int*(2) , ls1*
    nodeType** mixedPtr2 = (nodeType**)(mixedPtr[1] + 1);
    mixedPtr2[0] = malloc(sizeof(nodeType) + sizeof(int));
    mixedPtr2[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *mixedPtr2[0] = Integer;
    *(int*)(mixedPtr2[0] + 1) = 2;
    *mixedPtr2[1] = List;
    //mixedPtr3 -> str*(Diamondbacks) , ls1*
    nodeType** mixedPtr3 = (nodeType**)(mixedPtr2[1] + 1);
    mixedPtr3[0] = malloc(sizeof(nodeType) + sizeof(char) * 12);
    mixedPtr3[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *mixedPtr3[0] = String;
    strcpy((char*)(mixedPtr3[0] + 1), "Diamondbacks");
    *mixedPtr3[1] = List;
    //mixedPtr4 -> int*(1) , nil*
    nodeType** mixedPtr4 = (nodeType**)(mixedPtr3[1] + 1);
    mixedPtr4[0] = malloc(sizeof(nodeType) + sizeof(int));
    mixedPtr4[1] = malloc(sizeof(nodeType));
    *mixedPtr4[0] = Integer;
    *(int*)(mixedPtr4[0] + 1) = 1;
    *mixedPtr4[1] = Nil;


    // test concatall
    char* result = ConcatAll(mixed);
    printf("-----------TEST 3-----------\n\n");
    printf("Testing on list: (Yankees 2 Diamondbacks 1)...\n");
    if (strcmp(result, "YankeesDiamondbacks") != 0) {
        printf("TEST 3 FAILED: expected \"YankeesDiamondbacks\", got \"%s\"\n\n", result);
    }
    else {
        printf("TEST 3 PASSED\n\n");
    }

    // free memory
    free(result);
    free(mixedPtr4[0]);
    free(mixedPtr4[1]);
    free(mixedPtr3[0]);
    free(mixedPtr3[1]);
    free(mixedPtr2[0]);
    free(mixedPtr2[1]);
    free(mixedPtr[0]);
    free(mixedPtr[1]);
    free(mixed);
}



void test4() {
    // create nodeType list ("one" (2 ("three" 4)) 5 "six")

    nodeType* nested = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *nested = List;
    //nestedPtr -> str*(one) , ls1*
    nodeType** nestedPtr = (nodeType**)(nested + 1);
    nestedPtr[0] = malloc(sizeof(nodeType) + sizeof(char) * 4);
    nestedPtr[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *nestedPtr[0] = String;
    strcpy((char*)(nestedPtr[0] + 1), "one");
    *nestedPtr[1] = List;
    //nestedPtr2 -> ls2* , ls1*
    nodeType** nestedPtr2 = (nodeType**)(nestedPtr[1] + 1);
    nestedPtr2[0] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    nestedPtr2[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *nestedPtr2[0] = List;
    *nestedPtr2[1] = List;
    //nestedPtr3 -> int*(2) , ls2*
    nodeType** nestedPtr3 = (nodeType**)(nestedPtr2[0] + 1);
    nestedPtr3[0] = malloc(sizeof(nodeType) + sizeof(int));
    nestedPtr3[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *nestedPtr3[0] = Integer;
    *(int*)(nestedPtr3[0] + 1) = 2;
    *nestedPtr3[1] = List;
    //nestedPtr4 -> ls3* , nil*
    nodeType** nestedPtr4 = (nodeType**)(nestedPtr3[1] + 1);
    nestedPtr4[0] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    nestedPtr4[1] = malloc(sizeof(nodeType));
    *nestedPtr4[0] = List;
    *nestedPtr4[1] = Nil;
    //nestedPtr5 -> str*(three) , ls3*
    nodeType** nestedPtr5 = (nodeType**)(nestedPtr4[0] + 1);
    nestedPtr5[0] = malloc(sizeof(nodeType) + sizeof(char) * 6);
    nestedPtr5[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *nestedPtr5[0] = String;
    strcpy((char*)(nestedPtr5[0] + 1), "three");
    *nestedPtr5[1] = List;
    //nestedPtr6 -> int*(4) , nil*
    nodeType** nestedPtr6 = (nodeType**)(nestedPtr5[1] + 1);
    nestedPtr6[0] = malloc(sizeof(nodeType) + sizeof(int));
    nestedPtr6[1] = malloc(sizeof(nodeType));
    *nestedPtr6[0] = Integer;
    *(int*)(nestedPtr6[0] + 1) = 4;
    *nestedPtr6[1] = Nil;
    //nestedPtr7 -> int*(5) , ls1*
    nodeType** nestedPtr7 = (nodeType**)(nestedPtr2[1] + 1);
    nestedPtr7[0] = malloc(sizeof(nodeType) + sizeof(int));
    nestedPtr7[1] = malloc(sizeof(nodeType) + sizeof(nodeType*) * 2);
    *nestedPtr7[0] = Integer;
    *(int*)(nestedPtr7[0] + 1) = 5;
    *nestedPtr7[1] = List;
    //nestedPtr8 -> str*(six) , nil*
    nodeType** nestedPtr8 = (nodeType**)(nestedPtr7[1] + 1);
    nestedPtr8[0] = malloc(sizeof(nodeType) + sizeof(char) * 4);
    nestedPtr8[1] = malloc(sizeof(nodeType));
    *nestedPtr8[0] = String;
    strcpy((char*)(nestedPtr8[0] + 1), "six");
    *nestedPtr8[1] = Nil;


    // test concatall
    char* result = ConcatAll(nested);
    printf("-----------TEST 4-----------\n\n");
    printf("Testing on list: (one (2 (three 4)) 5 six)...\n");
    if (strcmp(result, "onethreesix") != 0) {
        printf("TEST 4 FAILED: expected \"onethreesix\", got \"%s\"\n\n", result);
    }
    else {
        printf("TEST 4 PASSED\n\n");
    }


    // free memory
    free(result);
    free(nestedPtr8[0]);
    free(nestedPtr8[1]);
    free(nestedPtr7[0]);
    free(nestedPtr7[1]);
    free(nestedPtr6[0]);
    free(nestedPtr6[1]);
    free(nestedPtr5[0]);
    free(nestedPtr5[1]);
    free(nestedPtr4[0]);
    free(nestedPtr4[1]);
    free(nestedPtr3[0]);
    free(nestedPtr3[1]);
    free(nestedPtr2[0]);
    free(nestedPtr2[1]);
    free(nestedPtr[0]);
    free(nestedPtr[1]);
    free(nested);
}

int main(int argc, char* argv[]) {
    test1();
    test2();
    test3();
    test4();
    return 0;
}
