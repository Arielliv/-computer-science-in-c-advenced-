//315363366
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char **setPtrToCharsArray(char **str_array);

char **getStrArrayInput(unsigned int *str_array_size);

void printArray(char **str_array, int str_array_size);

unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array);

void freeArray(char **str_array, int str_array_size);

char *removeCharFromStr(char *str, char *c);

char *getStringInput();

void checkMemoryAllocation(void *ptr);

void removeEmptyArrayCell(char **str_array, unsigned int str_array_size, int indexOfEmptyCell);

int main() {

    char **str_array;

    unsigned int str_array_size;

    char **ptr_to_chars_array;

    unsigned int res;


    str_array = getStrArrayInput(
            &str_array_size); // Get the size and strings from user (can't assume max size for each string)

    ptr_to_chars_array = setPtrToCharsArray(str_array);

    res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);

    printArray(str_array, str_array_size - res);

    // Free memory

    freeArray(str_array, str_array_size - res);

    free(ptr_to_chars_array);

}

char **setPtrToCharsArray(char **str_array) {

    char **res;

    int size, i;

    int str_array_row, str_array_col;


    scanf("%d", &size); // Get number of ptrs

    res = (char **) malloc(sizeof(char *) * (size + 1)); // Add 1 for NULL at the end



    for (i = 0; i < size; i++) {

        scanf("%d", &str_array_row);

        scanf("%d", &str_array_col);

        res[i] = str_array[str_array_row] + str_array_col;

    }


    res[size] = NULL; // Set the last one to NULL



    return res;

}

char **getStrArrayInput(unsigned int *str_array_size) {
    int size;
    char **str_array;
    int i;

    printf("Please enter size of array:\n");
    scanf("%d", &size);

    str_array = (char **) malloc(sizeof(char *) * size);
    getchar();
    for (i = 0; i < size; i++) {
        printf("%d - Please enter str:\n", i + 1);
        str_array[i] = getStringInput();
    }


    *str_array_size = size;
    return str_array;
}

char *getStringInput() {
    char *str;
    int logSize = 0, phySize = 1;
    char c;
    str = (char *) malloc(sizeof(char) * phySize);
    checkMemoryAllocation(str);

    c = getchar();
    while (c != '\n') {
        if (logSize == phySize) {
            phySize *= 2;
            str = (char *) realloc(str, sizeof(char) * phySize);
            checkMemoryAllocation(str);
        }
        str[logSize] = c;
        logSize++;
        c = getchar();
    }
    if (logSize < phySize) {
        str = (char *) realloc(str, sizeof(char) * (logSize + 1));
        checkMemoryAllocation(str);
    }
    str[logSize] = '\0';
    return str;
}

unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array) {
    char **strArray = *str_array;
    int sizeOfCurrentStr;
    int currentPtr = 0, j, k;
    int isEmptyCell;
    int counter = 0;
    char *ptrToCharInStr;
    char *ptrCurrentStr;
    while (ptr_to_chars_array[currentPtr] != NULL) {
        ptrToCharInStr = ptr_to_chars_array[currentPtr];
        for (j = 0; j < str_array_size; j++) {
            ptrCurrentStr = strArray[j];
            sizeOfCurrentStr = strlen(ptrCurrentStr);
            for (k = 0; k < sizeOfCurrentStr; k++) {
                if (&ptrCurrentStr[k] == ptrToCharInStr) {
                    strArray[j] = removeCharFromStr(strArray[j], ptrToCharInStr);
                    sizeOfCurrentStr--;
                }
            }
        }
        currentPtr++;
    }

    for (j = 0; j < str_array_size; j++) {
        isEmptyCell = strcmp(strArray[j], "\0");
        if (isEmptyCell == 0) {
            removeEmptyArrayCell(strArray, str_array_size, j);
            str_array_size--;
            counter++;
        }
    }


    *str_array = strArray;
    return counter;
}

char *removeCharFromStr(char *str, char *c) {
    int size = strlen(str);
    if (size == 0) {
        return "\0";
    }
    // size without \0
    char *newStr = (char *) malloc(sizeof(char) * size);
    int newIndex = 0;
    for (int i = 0; i < size; i++) {
        if (&(str[i]) != c) {
            newStr[newIndex] = str[i];
            newIndex++;
        }
    }
    newStr[size] = '\0';
    return newStr;
}

void removeEmptyArrayCell(char **str_array, unsigned int str_array_size, int indexOfEmptyCell) {
    int i;

    char **newStr_array = (char **) malloc(sizeof(char *) * str_array_size - 1);
    int newIndex = 0;
    for (i = 0; i < str_array_size; i++) {
        if (i != indexOfEmptyCell) {
            newStr_array[newIndex] = str_array[i];
            newIndex++;
        }
    }
    str_array = newStr_array;
}

void printArray(char **str_array, int str_array_size) {
    int i;
    for (i = 0; i < str_array_size; ++i) {
        printf("%s\n", str_array[i]);
    }
}

void freeArray(char **str_array, int str_array_size) {
    int i;
    for (i = 0; i < str_array_size; ++i) {
        free(str_array[i]);
    }
    free(str_array);
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}