// 315363366
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 1

typedef struct monom {
    int coefficient;
    int power;
};
typedef struct monom Monom;

Monom *getPolynom(unsigned int *polynomSize);

void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);

void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);

char *inputString();

// create and return array of numbers from string of numbers
int *convertStrToNumArray(char *strNums, int *size);

// check memory allocation
void checkMemoryAllocation(void *ptr);

void swapMonoms(Monom *value1, Monom *value2);

void printMonom(Monom c);

void cleanPolynom(Monom *polynom, int *size);

Monom *createPolynom(int *size, int *polynomNumbers, int polynomNumbersSize);

void sortPolynom(Monom *polynom, int size);

void printPolynom(Monom *polynom, int size);

void main() {
    Monom *polynom1, *polynom2;             // The input polynoms
    unsigned int polynom1Size, polynom2Size; // The size of each polynom

    printf("Please enter the first polynom:\n");
    polynom1 = getPolynom(&polynom1Size);   // get polynom 1

    printf("Please enter the second polynom:\n");
    polynom2 = getPolynom(&polynom2Size);   // get polynom 2

    printf("The multiplication of the polynoms is:\n"); // print the multiplication
    printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    printf("The sum of the polynoms is:\n"); // print the sum
    printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    free(polynom1); // releasing all memory allocations
    free(polynom2);
}


Monom *getPolynom(unsigned int *polynomSize) {
    char *str = inputString();
    int *intNumbers;
    int size = 0;
    Monom *polynom;
    intNumbers = convertStrToNumArray(str, &size);
    polynom = createPolynom(&size, intNumbers, size);
    cleanPolynom(polynom, &size);
    sortPolynom(polynom, size);
    *polynomSize = size;
    return polynom;
}

void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size) {
    int maxSize = polynom1Size * polynom2Size;
    Monom *newPolynom = (Monom *) malloc(sizeof(Monom) * maxSize);
    int counter = 0;
    for (int index1 = 0; index1 < polynom1Size; index1++) {
        for (int index2 = 0; index2 < polynom2Size; index2++) {
            newPolynom[counter].coefficient = polynom1[index1].coefficient * polynom2[index2].coefficient;
            newPolynom[counter].power = polynom1[index1].power + polynom2[index2].power;
            counter++;
        }
    }
    cleanPolynom(newPolynom, &maxSize);
    sortPolynom(newPolynom, maxSize);
    printPolynom(newPolynom, maxSize);
    free(newPolynom);
}

void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size) {
    int maxSize = polynom1Size + polynom1Size;

    Monom *newPolynom = (Monom *) malloc(sizeof(Monom) * maxSize);

    for (int index1 = 0; index1 < polynom1Size; index1++) {
        newPolynom[index1].coefficient = polynom1[index1].coefficient;
        newPolynom[index1].power = polynom1[index1].power;
    }
    for (int index2 = 0; index2 < polynom2Size; index2++) {
        newPolynom[polynom1Size + index2].coefficient = polynom2[index2].coefficient;
        newPolynom[polynom1Size + index2].power = polynom2[index2].power;
    }
    cleanPolynom(newPolynom, &maxSize);
    sortPolynom(newPolynom, maxSize);
    printPolynom(newPolynom, maxSize);
    free(newPolynom);
}

char *inputString() {
    //The size is extended by the input
    char *str = NULL;
    int ch;
    size_t size = 0, len = 0;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (len + 1 >= size) {
            size = size * 2 + 1;
            str = realloc(str, sizeof(char) * size);
            checkMemoryAllocation(str);
        }
        str[len++] = ch;
    }
    if (str != NULL) {
        str[len] = '\0';
        return str;
    } else {
        return NULL;
    }

}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}

int *convertStrToNumArray(char *strNums, int *size) {
    char *token;
    int *numbers;
    int i = 0;

    numbers = (int *) malloc((strlen(strNums) / 2) * sizeof(int));
    checkMemoryAllocation(numbers);

    token = strtok(strNums, " ");
    while (token != NULL) {
        sscanf(token, "%d", &numbers[i]);
        token = strtok(NULL, " ");
        i++;
    }
    *size = i;
    return numbers;
}

void swapMonoms(Monom *value1, Monom *value2) {
    Monom tmp;
    tmp.coefficient = value1->coefficient;
    tmp.power = value1->power;

    value1->coefficient = value2->coefficient;
    value1->power = value2->power;

    value2->coefficient = tmp.coefficient;
    value2->power = tmp.power;

}

void printPolynom(Monom *polynom, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printMonom(polynom[i]);
    }
    printf("\n");
}

void printMonom(Monom c) {
    if (c.power == 0) {
        printf("%dX ", c.coefficient);
    } else {
        printf("%dX^%d ", c.coefficient, c.power);
    }
}

Monom *createPolynom(int *size, int *polynomNumbers, int polynomNumbersSize) {
    int i, y;
    Monom *polynom = (Monom *) malloc(sizeof(Monom) * (*size));
    for (i = 0, y = 0; i < *size - 1; i += 2, y++) {
        if (polynomNumbers[i] == 0) {
            i += 2;
        }
        polynom[y].coefficient = polynomNumbers[i];
        polynom[y].power = polynomNumbers[i + 1];
    }
    *size = y;
    return polynom;
}

void cleanPolynom(Monom *polynom, int *size) {
    int i;
    int plSize = *size;
    for (i = 0; i < plSize; i++) {
        for (int k = i + 1; k < plSize; k++) {
            if (polynom[i].power == polynom[k].power) {
                polynom[i].coefficient = polynom[i].coefficient + polynom[k].coefficient;
                swapMonoms(&polynom[k], &polynom[plSize - 1]);
                plSize--;
            }
        }
    }

    polynom = realloc(polynom, sizeof(Monom) * plSize);
    *size = plSize;
}

void sortPolynom(Monom *polynom, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (polynom[j].power < polynom[j + 1].power) {
                swapMonoms(&polynom[j], &polynom[j + 1]);
            }

        }
    }
}