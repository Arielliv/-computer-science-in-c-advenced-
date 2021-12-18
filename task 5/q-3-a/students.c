//
// Created by 315363366 on 11/12/2021.
//
#define _CRT_SECURE_NO_WARNINGS
#include "students.h"
#include "utils.h"


void mergeSortStudentWithIndex(StudentWithIndex **array, short int size) {
    StudentWithIndex **tmpArray = NULL;
    if (size <= 1) {
        return;
    }
    mergeSortStudentWithIndex(array, size / 2);
    mergeSortStudentWithIndex(array + size / 2, size - size / 2);
    tmpArray = mergeArrays(array, size / 2, array + size / 2, size - size / 2);
    if (tmpArray) {
        copyArray(array, tmpArray, size);
        free(tmpArray);
    } else {
        printf("error");
    }
}

void copyArray(StudentWithIndex **des, StudentWithIndex **src, short int size) {
    int i;
    for (i = 0; i < size; i++) {
        des[i] = src[i];
    }
}

StudentWithIndex **mergeArrays(StudentWithIndex **array1, short int size1, StudentWithIndex **array2, short int size2) {
    int index1, index2, indexResult;
    StudentWithIndex **tempArray = (StudentWithIndex **) malloc(sizeof(StudentWithIndex **) * (size1 + size2));
    checkMemoryAllocation(tempArray);
    if (tempArray == NULL) {
        printf("error");
    } else {
        index1 = index2 = indexResult = 0;

        while ((index1 < size1) && (index2 < size2)) {
            if (array1[index1]->student->average >= array2[index2]->student->average) {
                tempArray[indexResult] = array2[index2];
                index2++;
            } else {
                tempArray[indexResult] = array1[index1];
                index1++;
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

        return tempArray;
    }
}

