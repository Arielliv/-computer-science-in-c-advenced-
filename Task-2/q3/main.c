//315363366
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point {
    int locationOfStr;
    int locationOfChar;
} Point;

char **setPtrToCharsArray(char **str_array);

char **getStrArrayInput(unsigned int *str_array_size);

void printArray(char **str_array, int str_array_size);

unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array);

void freeArray(char **str_array, int str_array_size);

void freePoints(Point *array, int size);

char *getStringInput();

void checkMemoryAllocation(void *ptr);

void removeEmptyArrayCellByIndex(char **array, int index, int array_length);

void copyArray(Point *des, Point *src, int size);

Point *mergeArrays(Point *array1, int size1, Point *array2, int size2);

void mergeSort(Point *array, int size);

void removeCharFromArrayOfStrByIndex(char **str_array, int str_array_size, int row, int col);

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
    int pointsLogSize = 0;
    int pointsPyhSize = 1;
    Point *points = (Point *) malloc(sizeof(Point *) * pointsPyhSize);
    char **strArray = *str_array;
    int sizeOfCurrentStr;
    int currentPtr = 0, j, k, i;
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
                    Point *newPoint = (Point *) malloc((sizeof(currentPtr)));
                    newPoint->locationOfStr = j;
                    newPoint->locationOfChar = k;
                    points[pointsLogSize] = *newPoint;
                    pointsLogSize++;
                    if (pointsLogSize == pointsPyhSize) {
                        pointsPyhSize *= 2;
                        points = (Point *) realloc(points, sizeof(Point *) * pointsPyhSize);
                        checkMemoryAllocation(points);
                    }
                }
            }
        }
        currentPtr++;
    }
    if (pointsLogSize < pointsPyhSize) {
        points = (Point *) realloc(points, sizeof(Point *) * pointsLogSize);
        checkMemoryAllocation(points);
    }
    mergeSort(points, pointsLogSize);
    for (i = 0; i < pointsLogSize; i++) {
        printf("%d-%d\n", points[i].locationOfStr, points[i].locationOfChar);
    }

    for (i = 0; i < pointsLogSize; i++) {
        removeCharFromArrayOfStrByIndex(strArray, (int) str_array_size, points[i].locationOfStr,
                                        points[i].locationOfChar);
    }
    freePoints(points, pointsLogSize);

    for (j = 0; j < str_array_size; j++) {
        isEmptyCell = strcmp(strArray[j], "\0");
        if (isEmptyCell == 0) {
            removeEmptyArrayCellByIndex(strArray, j, (int) str_array_size);
            str_array_size--;
            counter++;
        }
    }

    *str_array = strArray;
    return counter;
}

void removeCharFromArrayOfStrByIndex(char **str_array, int str_array_size, int row, int col) {
    int i, j;

    char *newStr;
    int newIndex;
    for (i = 0; i < str_array_size; i++) {
        int strSize = strlen(str_array[i]);
        newIndex = 0;
        newStr = (char *) malloc(sizeof(char) * (strSize));
        for (j = 0; j < strSize; j++) {
            if (i != row || j != col) {
                newStr[newIndex] = str_array[i][j];
                newIndex++;
            }
        }
        newStr[newIndex] = '\0';
        str_array[i] = newStr;
    }
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

void freePoints(Point *array, int size) {
    int i;
    free(array);
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}

void mergeSort(Point *array, int size) {
    Point *tmpArray = NULL;
    if (size <= 1) {
        return;
    }
    mergeSort(array, size / 2);
    mergeSort(array + size / 2, size - size / 2);
    tmpArray = mergeArrays(array, size / 2, array + size / 2, size - size / 2);
    if (tmpArray) {
        copyArray(array, tmpArray, size);
        free(tmpArray);
    } else {
        printf("error");
    }
}

Point *mergeArrays(Point *array1, int size1, Point *array2, int size2) {
    int index1, index2, indexResult;
    Point *tempArray = (Point *) malloc(sizeof(Point) * (size1 + size2));
    checkMemoryAllocation(tempArray);
    if (tempArray == NULL) {
        printf("error");
    } else {
        index1 = index2 = indexResult = 0;

        while ((index1 < size1) && (index2 < size2)) {
            if ((array1[index1]).locationOfStr > (array2[index2]).locationOfStr) {
                tempArray[indexResult] = array1[index1];
                index1++;
            } else if ((array1[index1]).locationOfStr == (array2[index2]).locationOfStr) {
                if ((array1[index1]).locationOfChar > (array2[index2]).locationOfChar) {
                    tempArray[indexResult] = array1[index1];
                    index1++;
                } else {
                    tempArray[indexResult] = array2[index2];
                    index2++;
                }
            } else {
                tempArray[indexResult] = array2[index2];
                index2++;

            }
            indexResult++;
        }

        while (index2 < size2) {
            tempArray[indexResult] = array2[index2];
            index2++;
            indexResult++;
        }

        while (index1 < size1) {
            tempArray[indexResult] = array1[index1];
            index1++;
            indexResult++;
        }
    }


    return tempArray;
}

void copyArray(Point *des, Point *src, int size) {
    int i;
    for (i = 0; i < size; i++) {
        des[i] = src[i];
    }
}