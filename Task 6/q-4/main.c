// 315363366
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "utils.h"
#include "string.h"

#define SIZE 100

void *getIntArr(int *intSize);

void *getStringArr(int *stringSize);

int intBinSearch(int *intArr, int intSize, int intToFind);

int stringBinSearch(char **stringArr, int stringSize, char *stringToFind);

void
freeMemory(int *intArr, int intSize, char **stringArr, int stringSize);

int binSearch(void *Arr, int Size, int ElemSize, void *Item, int (*compare)(void *, void *));

int intCheckIfIntEq(void *a, void *b);

int intCheckIfStrEq(void *a, void *b);

#define SIZE 100

void main() {

    int *intArr;

    int intSize, intToFind;

    char **stringArr, stringToFind[SIZE];

    int stringSize;

    int res;



    // The user will enter the number of integers followed by the integers.

    intArr = getIntArr(&intSize);



    // The user will enter the integer to find

    scanf("%d", &intToFind);



    //The function searches the array using binSearch()

    res = intBinSearch(intArr, intSize, intToFind);


    if (res == 1)

        printf("The number %d was found\n", intToFind);

    else

        printf("The number %d was not found\n", intToFind);



    // The user will enter the number of strings (lines) followed by the strings.

    // You may assume that each line contains up to 99 characters.

    stringArr = getStringArr(&stringSize);



    // The user will enter the string to find
    gets(stringToFind);



    //The function searches the array using binSearch()

    res = stringBinSearch(stringArr, stringSize, stringToFind);


    if (res == 1)

        printf("The string %s was found\n", stringToFind);

    else

        printf("The string %s was not found\n", stringToFind);

    freeMemory(intArr, intSize, stringArr, stringSize);

}

void *getIntArr(int *intSize) {
    int size, i, tempVal;
    int *intArr;

//    printf("please enter size for the array: \n");
    scanf("%d", &size);
    intArr = (int *) malloc(sizeof(int) * size);
    checkMemoryAllocation(intArr);

    for (i = 0; i < size; i++) {
//        printf("please enter int val to array: \n");
        scanf("%d", &tempVal);
        intArr[i] = tempVal;
    }
    *intSize = size;
    return intArr;
}

void *getStringArr(int *stringSize) {
    int size, i;

    char **stringArr;
//    printf("please enter size for the array: \n");
    scanf("%d", &size);
    getchar();
    stringArr = (char **) malloc(sizeof(char *) * size);
    checkMemoryAllocation(stringArr);

    for (i = 0; i < size; i++) {
        char *tempVal = (char *) malloc(sizeof(char) * 99);
        checkMemoryAllocation(tempVal);

//        printf("please enter string val to array: \n");
        gets(tempVal);
        stringArr[i] = tempVal;
    }
    *stringSize = size;
    return stringArr;
}

int intCheckIfIntEq(void *a, void *b) {
    int n1 = *((int *) a);
    int n2 = *((int *) b);

    return n1 - n2;
}

int intCheckIfStrEq(void *a, void *b) {
    char *str1 = *((char **) a);
    char *str2 = *((char **) b);
    return strcmp(str1, str2);
}

int intBinSearch(int *intArr, int intSize, int intToFind) {
    int (*compare)(void *, void *) = intCheckIfIntEq;
    return binSearch(intArr, intSize, sizeof(int), &intToFind, compare);
}

int stringBinSearch(char **stringArr, int stringSize, char *stringToFind) {
    int (*compare)(void *, void *) = intCheckIfStrEq;
    return binSearch(stringArr, stringSize, sizeof(char *), &stringToFind, compare);
}

void freeMemory(int *intArr, int intSize, char **stringArr, int stringSize) {
    int i;
    for (i = 0; i < stringSize; i++) {
        free(stringArr[i]);
    }
    free(intArr);

    free(stringArr);

}

int binSearch(void *Arr, int Size, int ElemSize, void *Item, int (*compare)(void *, void *)) {
    int found = 0;
    int left = 0, right = Size - 1;
    while (left <= right && found != 1) {
        int place = (left + right) / 2;
        if (compare((unsigned char *) Arr + (place * ElemSize), Item) == 0) {
            found = 1;
        } else if (compare((unsigned char *) Arr + (place * ElemSize), Item) < 1) {
            left = place + 1;
        } else {
            right = place - 1;
        }
    }
    return found;
}

