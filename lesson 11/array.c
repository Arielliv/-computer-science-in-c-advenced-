//
// Created by Ariel Livshits on 24/12/2021.
//

#include "array.h"

void initArray(Array *arr, int sizeType, int physicalSize,
               void(*print)(const void *), void(*save)(FILE *, const void *),
               void *(*load)(FILE *)) {
    arr->logicalSize = 0;
    arr->typeSize = sizeType;
    arr->physicalSize = physicalSize;
    arr->arr = (void **) malloc(arr->physicalSize * (arr->typeSize));

    arr->print = print;
    arr->load = load;
    arr->save = save;
}

void freeArray(Array *arr) {
    free(arr->arr);
}

void addToEnd(Array *arr, void *newValue) {
    if (arr->logicalSize == arr->physicalSize) {
        printf("double arr size...\n");
        arr->physicalSize *= 2;
        arr->arr = (void **) realloc(arr->arr,
                                     arr->physicalSize * (arr->typeSize));
    }
    arr->arr[arr->logicalSize++] = newValue;
}

void saveArrToFile(const char *fileName, const Array *arr) {
    int i;
    FILE *f = fopen(fileName, "wb");
    fwrite(&arr->logicalSize, sizeof(int), 1, f);
    for (i = 0; i < arr->logicalSize; i++)
        arr->save(f, arr->arr[i]);
    fclose(f);
}

void loadArrFromFile(const char *fileName, Array *arr) {
    int i;
    FILE *f = fopen(fileName, "rb");
    fread(&arr->logicalSize, sizeof(int), 1, f);
    if (arr->logicalSize > arr->physicalSize) {
        arr->arr = (void **) realloc(arr->arr, arr->logicalSize * (arr->typeSize));
        arr->physicalSize = arr->logicalSize;
    }
    for (i = 0; i < arr->logicalSize; i++) {
        arr->arr[i] = arr->load(f);
    }
    //addToEnd(arr, arr->load(f,arr->logicalSize));
    fclose(f);
}

void printArr(const Array *arr) {
    int i;
    printf("There are %d values (%d spaces):\n",
           arr->logicalSize, arr->physicalSize);
    for (i = 0; i < arr->logicalSize; i++)
        arr->print(arr->arr[i]);
    printf("\n");
}