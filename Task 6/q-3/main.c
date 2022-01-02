// 315363366
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "array.h"
#include "utils.h"

#define SIZE 100

void *getIntArr(int *intSize);

void printIntArr(int *scrambleIntArr, int intSize);

void *getStringArr(int *stringSize);

void printStringArr(char **scrambleStringArr, int stringSize);

int *scrambleInt(int *intArr, int intSize, int *indArr);

char **scrambleString(char **stringArr, int stringSize, int *indArr);

void
freeMemory(int *intArr, int *scrambleIntArr, int intSize, char **stringArr, char **scrambleStringArr, int stringSize);

void main() {

    int *intArr, *scrambleIntArr;

    int intSize;

    char **stringArr, **scrambleStringArr;

    int stringSize, i;

    int indArr[SIZE];



    // The user will enter the number of integers followed by the integers.

    intArr = getIntArr(&intSize);



    // The user will enter the indices

    for (i = 0; i < intSize; i++)

        scanf("%d", &indArr[i]);



    //The function scrambles the array using scramble()

    scrambleIntArr = scrambleInt(intArr, intSize, indArr);


    printIntArr(scrambleIntArr, intSize);



    // The user will enter the number of strings (lines) followed by the strings.

    // You may assume that each line contains up to 99 characters.

    stringArr = getStringArr(&stringSize);



    // The user will enter the indices

    for (i = 0; i < stringSize; i++)

        scanf("%d", &indArr[i]);



    //The function scrambles the array using scramble()

    scrambleStringArr = scrambleString(stringArr, stringSize, indArr);


    printStringArr(scrambleStringArr, stringSize);

    freeMemory(intArr, scrambleIntArr, intSize, stringArr, scrambleStringArr, stringSize);

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

int *scrambleInt(int *intArr, int intSize, int *indArr) {
    return (int *) scramble(intArr, sizeof(int), intSize, indArr);
}

char **scrambleString(char **stringArr, int stringSize, int *indArr) {
    return (char **) scramble(stringArr, sizeof(char *), stringSize, indArr);
}

void printIntArr(int *scrambleIntArr, int intSize) {
    int i;
    for (i = 0; i < intSize; i++) {
        printf("%d ", scrambleIntArr[i]);
    }
    printf("\n");
}

void printStringArr(char **scrambleStringArr, int stringSize) {
    for (int i = 0; i < stringSize; i++) {
        printf("%s \n", scrambleStringArr[i]);
    }
}

void
freeMemory(int *intArr, int *scrambleIntArr, int intSize, char **stringArr, char **scrambleStringArr, int stringSize) {
    int i;
    for (i = 0; i < stringSize; i++) {
        free(stringArr[i]);
    }
    free(intArr);
    free(scrambleIntArr);
    free(stringArr);
    free(scrambleStringArr);
}