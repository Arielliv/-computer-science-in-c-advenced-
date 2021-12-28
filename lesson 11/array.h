//
// Created by Ariel Livshits on 24/12/2021.
//

#ifndef LESSON_11_ARRAY_H
#define LESSON_11_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)
typedef struct {
    void **arr;
    int typeSize;
    int logicalSize;
    int physicalSize;

    void (*print)(const void *);

    void (*save)(FILE *, const void *);

    void *(*load)(FILE *);
} Array;

void initArray(Array *arr, int sizeType, int physicalSize,
               void(*print)(const void *), void(*save)(FILE *, const void *), void *(*load)(FILE *));

void freeArray(Array *arr);

void addToEnd(Array *arr, void *newValue);

void saveArrToFile(const char *fileName, const Array *arr);

void loadArrFromFile(const char *fileName, Array *arr);

void printArr(const Array *arr);


#endif //LESSON_11_ARRAY_H
