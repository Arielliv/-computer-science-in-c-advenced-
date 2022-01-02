// 315363366
#define _CRT_SECURE_NO_WARNINGS

#include "array.h"

void *scramble(void *arr, int ElemSize, int n, int *indArr) {
    int i;
    void *newArr = malloc(ElemSize * n);
    for (i = 0; i < n; i++) {
        memcpy((BYTE *) newArr + (i * ElemSize), (BYTE *) arr + (indArr[i] * ElemSize), ElemSize);
    }
    return newArr;
}
