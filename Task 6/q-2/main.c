#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned char BYTE;

int *filter(int *Numbers, int size, BYTE *pred, int *new_size);

int countSetBits(BYTE *bitsArr, int size);

bool isBitOn(BYTE byte, int location);

int countFormTwoPred(BYTE *pred1, BYTE *pred2, int size);

int *xorFilter(int *Numbers, int size, BYTE *pred1, BYTE *pred2, int *new_size);

void main() {

    int i, pr, new_size, size;

    int *numbers;

    BYTE *pred1, *pred2;

    int *some_numbers1;

    int *some_numbers2;


    printf("Please enter the number of numbers:\n");


    scanf("%d", &size);


    numbers = (int *) malloc(size * sizeof(int));

    if (numbers == NULL)

        exit(1);


    pred1 = (char *) malloc(size / 8 * sizeof(char));

    if (pred1 == NULL)

        exit(1);


    pred2 = (char *) malloc(size / 8 * sizeof(char));

    if (pred2 == NULL)

        exit(1);


    printf("Please enter the numbers:\n");


    for (i = 0; i < size; i++)


        scanf("%d", &numbers[i]);


    printf("Please enter the first filter bits in hexa:\n");


    for (i = 0; i < size / 8; i++) {

        scanf("%x", &pr);

        pred1[i] = (char) pr;

    }


    some_numbers1 = filter(numbers, size, pred1, &new_size);


    printf("The numbers selected are:\n");


    for (i = 0; i < new_size; i++)


        printf("%d ", some_numbers1[i]);


    printf("Please enter the second filter bits in hexa:\n");


    for (i = 0; i < size / 8; i++) {


        scanf("%x", &pr);


        pred2[i] = (char) pr;


    }


    some_numbers2 = xorFilter(numbers, size, pred1, pred2, &new_size);


    printf("The numbers selected are:\n");


    for (i = 0; i < new_size; i++)


        printf("%d ", some_numbers2[i]);


    free(numbers);

    free(some_numbers1);

    free(pred1);

    free(some_numbers2);

    free(pred2);

}

int *filter(int *Numbers, int size, BYTE *pred, int *new_size) {
    int i, j;
    int count = countSetBits(pred, size / 8);
    int counter = count - 1;
    int *newNumbers = (int *) malloc(sizeof(int) * count);

    for (j = (size / 8) - 1; j >= 0; j--) {
        for (i = 7; i >= 0; i--) {
            bool checkPred1 = isBitOn(pred[j], i);
            if (checkPred1) {
                newNumbers[counter] = Numbers[(j + 1) * 8 - (8 - i)];
                counter--;
            }
        }
    }

    *new_size = count;
    return newNumbers;
}

bool isBitOn(BYTE byte, int location) {
    BYTE mask = 1 << location;
    return byte & mask;
}

int countSetBits(BYTE *bitsArr, int size) {
    int i;
    BYTE currByte;
    BYTE mask = 0x01;
    int counter = 0;
    for (i = 0; i < size; i++) {
        currByte = bitsArr[i];
        while (currByte != 0) {
            if ((mask & currByte) == 0x01)
                counter++;
            currByte = currByte >> 0x01;
        }
    }
    return counter;
}

int countFormTwoPred(BYTE *pred1, BYTE *pred2, int size) {
    int counter = 0;
    int i, j;
    for (j = size / 8; j >= 0; j--) {
        for (i = size; i >= 0; i--) {
            bool checkPred1 = isBitOn(pred1[j], i);
            bool checkPred2 = isBitOn(pred2[j], i);
            if ((checkPred1 || checkPred2) && !(checkPred1 && checkPred2)) {
                counter++;
            }

        }
    }
    return counter;
}


int *xorFilter(int *Numbers, int size, BYTE *pred1, BYTE *pred2, int *new_size) {
    int i, j;
    int count = countFormTwoPred(pred1, pred2, size);
    int counter = count - 1;
    int *newNumbers = (int *) malloc(sizeof(int) * count);

    for (j = size / 8; j >= 0; j--) {
        for (i = size; i >= 0; i--) {

            bool checkPred1 = isBitOn(pred1[j], i);
            bool checkPred2 = isBitOn(pred2[j], i);
            if ((checkPred1 || checkPred2) && !(checkPred1 && checkPred2)) {
                newNumbers[counter] = Numbers[(j + 1) * 8 - (8 - i)];
                counter--;
            }

        }
    }

    *new_size = count;
    return newNumbers;
}
