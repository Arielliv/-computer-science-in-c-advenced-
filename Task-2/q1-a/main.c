// 315363366
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// merge sort main function
void mergeSort(int **array, int size, int ascend_flag);

// merge to pointers arrays into one
int **mergeArrays(int **array1, int size1, int **array2, int size2, int ascend_flag);

// copy pointers array
void copyArray(int **des, int **src, int size);

// sort pointers array
int **pointerSort(int *arr, int size, int ascend_flag);

// print pointers array values
void printPointers(int **pointers, int size);

// check memory allocation
void checkMemoryAllocation(void *ptr);

#define SIZE 100

// main function
void main() {
    unsigned int size, i;
    int arr[SIZE];
    int **pointers;
    int ascend_flag;
    printf("Please enter the number of items:\n");
    scanf("%u", &size);
    for (i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &ascend_flag);
    pointers = pointerSort(arr, size, ascend_flag);
    printf("The sorted array:\n"); //Print the sorted array
    printPointers(pointers, size);
    free(pointers);
    exit(0);
}

int **pointerSort(int *arr, int size, int ascend_flag) {
    int **pointersArray = (int **) malloc(sizeof(int *) * size);
    checkMemoryAllocation(pointersArray);
    for (int i = 0; i < size; i++) {
        pointersArray[i] = &arr[i];
    }
    mergeSort(pointersArray, size, ascend_flag);

    return pointersArray;
}

void printPointers(int **pointers, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *pointers[i]);
    }
}

void mergeSort(int **array, int size, int ascend_flag) {
    int **tmpArray = NULL;
    if (size <= 1) {
        return;
    }
    mergeSort(array, size / 2, ascend_flag);
    mergeSort(array + size / 2, size - size / 2, ascend_flag);
    tmpArray = mergeArrays(array, size / 2, array + size / 2, size - size / 2, ascend_flag);
    if (tmpArray) {
        copyArray(array, tmpArray, size);
        free(tmpArray);
    } else {
        printf("error");
    }
}

int **mergeArrays(int **array1, int size1, int **array2, int size2, int ascend_flag) {
    int index1, index2, indexResult;
    int **tempArray = (int **) malloc(sizeof(int *) * (size1 + size2));
    checkMemoryAllocation(tempArray);
    if (tempArray == NULL) {
        printf("error");
    } else {
        index1 = index2 = indexResult = 0;
        if (ascend_flag == 1) {
            while ((index1 < size1) && (index2 < size2)) {
                if (*array1[index1] <= *array2[index2]) {
                    tempArray[indexResult] = array1[index1];
                    index1++;
                } else {
                    tempArray[indexResult] = array2[index2];
                    index2++;
                }
                indexResult++;
            }

            while (index1 < size1) {
                tempArray[indexResult] = array1[index1];
                index1++;
                indexResult++;
            }
            while (index2 < size2) {
                tempArray[indexResult] = array2[index2];
                index2++;
                indexResult++;
            }
        } else {
            while ((index1 < size1) && (index2 < size2)) {
                if (*array1[index1] >= *array2[index2]) {
                    tempArray[indexResult] = array1[index1];
                    index1++;
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

    }
    return tempArray;
}

void copyArray(int **des, int **src, int size) {
    int i;
    for (i = 0; i < size; i++) {
        des[i] = src[i];

    }
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}