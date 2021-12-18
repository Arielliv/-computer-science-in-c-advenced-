#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

BYTE *createButsArray(int arr[], int size, int *bitArrSize);

int getMax(int arr[], int size);

int countSetBits(BYTE *bitsArr, int size);

BYTE setBit(BYTE ch, int i);

int main() {
    int arr[] = {7, 2, 9, 4, 13};
    BYTE *bitsArr;
    int size;
    int count;

    bitsArr = createButsArray(arr, sizeof(arr) / sizeof(arr[0]), &size);
    count = countSetBits(bitsArr, size);
    printf("The counter is %d\n", count);
    free(bitsArr);
}

BYTE *createButsArray(int arr[], int size, int *bitArrSize) {
    int i, max = getMax(arr, size);
    BYTE *bitsArr;
    int bitsSize = (max / 8) + 1;
    bitsArr = (BYTE *) calloc(sizeof(BYTE), bitsSize);
    // *bitArrSize = bitsSize;
//    bitsArr = (BYTE *) malloc(sizeof(BYTE) * bitsSize);
    for (i = 0; i < bitsSize; i++) { // sets all bits to 0
        bitsArr[i] = 0;
    }
    for (i = 0; i < size; ++i) {
        bitsArr[arr[i] / 8] = setBit(bitsArr[arr[i] / 8], 7 - arr[i] % 8);
    }
}

// 00000001
// 00001000
BYTE setBit(BYTE ch, int i) {
    BYTE mask = 1 << i;
    return ch | mask;
}

int getMax(int arr[], int size) {

    int i, max = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// check how many 1 in byte ( example 0110110 - 4 are on)
int countSetBits(BYTE *bitsArr, int size) {
    int i, j;
    int count = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; i < 8; i++) {
            count += bitsArr[i] >> j && 0x01;
        }
    }
}