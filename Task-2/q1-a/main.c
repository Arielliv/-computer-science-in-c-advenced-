//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mergeSort(int *array, int size);

int *mergeArrays(int *array1, int size1, int *array2, int size2);

void copyArray(int *des, int *src, int size);

int **pointerSort(int *arr, int size, int ascend_flag);

void printPointers(int **pointers, int size);

#define SIZE 100


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
    int *tmpArray = (int *) malloc(sizeof(int) * size);
    int **pointersArray = (int **) malloc(sizeof(int *) * size);
    copyArray(tmpArray, arr, size);
    mergeSort(tmpArray, size);

    for (int i = 0; i < size; i++) {
        if (ascend_flag == 1) {
            pointersArray[i] = &tmpArray[i];
        } else {
            pointersArray[i] = &tmpArray[size - 1 - i];
        }
    }

    return pointersArray;
}

void printPointers(int **pointers, int size){
    for (int i = 0; i < size; i++) {
            printf("%d ",*pointers[i]);
    }
}

void mergeSort(int *array, int size) {
    int *tmpArray = NULL;
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

int *mergeArrays(int *array1, int size1, int *array2, int size2) {
    int index1, index2, indexResult;
    int *tempArray = (int *) malloc(sizeof(int) * (size1 + size2));
    if (tempArray == NULL) {
        printf("error");
    } else {
        index1 = index2 = indexResult = 0;
        while ((index1 < size1) && (index2 < size2)) {
            if (array1[index1] <= array2[index2]) {
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
    }
    return tempArray;
}

void copyArray(int *des, int *src, int size) {
    int i;
    for (i = 0; i < size; i++) {
        des[i] = src[i];

    }
}