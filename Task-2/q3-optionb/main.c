//315363366
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **setPtrToCharsArray(char **str_array);

char **getStrArrayInput(unsigned int *str_array_size);

void printArray(char **str_array, int str_array_size);

unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array);

void freeArray(char **str_array, int str_array_size);


char *getStringInput();

void checkMemoryAllocation(void *ptr);

void removeEmptyArrayCellByIndex(char **array, int index, int array_length);

void removeCharFromStrByIndex(char *array, int index, int array_length);

void signStrArrayWithTmpSign(char **ptr_to_chars_array);

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
    checkMemoryAllocation(str_array);
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
    int j, k;
    int isEmptyCell;
    int counter = 0;

    signStrArrayWithTmpSign(ptr_to_chars_array);

    for (j = 0; j < str_array_size; j++) {
        isEmptyCell = strcmp(strArray[j], "\0");
        if (isEmptyCell == 0) {
            removeEmptyArrayCellByIndex(strArray, j, (int) str_array_size);
            str_array_size--;
            counter++;
        }

        sizeOfCurrentStr = strlen(strArray[j]);
        for (k = 0; k < sizeOfCurrentStr; k++) {
            if (strArray[j][k] == '\n') {
                removeCharFromStrByIndex(strArray[j], k, sizeOfCurrentStr);
                sizeOfCurrentStr--;
            }
        }
    }

    *str_array = strArray;
    return counter;
}

void signStrArrayWithTmpSign(char **ptr_to_chars_array) {
    int currentPtr = 0;
    while (ptr_to_chars_array[currentPtr] != NULL) {
        *ptr_to_chars_array[currentPtr] = '\n';
        currentPtr++;
    }
}

void removeCharFromStrByIndex(char *array, int index, int array_length) {
    int i;
    for (i = index; i < array_length - 1; i++) {
        array[i] = array[i + 1];
    }
    array[i] = '\0';
}

void removeEmptyArrayCellByIndex(char **array, int index, int array_length) {
    int i;
    for (i = index; i < array_length - 1; i++) {
        array[i] = array[i + 1];
    }
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