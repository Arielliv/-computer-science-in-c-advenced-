// 315363366
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct monom {
    int coefficient;
    int power;
};
typedef struct monom Monom;
//
// return new array of monoms from the user input according to polynomSize param
Monom *getPolynom(unsigned int *polynomSize);

// print multiply of polynoms ( two arrays of monoms)
void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);

// print sum of polynoms ( two arrays of monoms)
void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);

// get user input for unknow size of string
char *getStringInput();

// create and return array of numbers from string of numbers
int *convertStrToNumArray(char *strNums, int *size);

// check memory allocation
void checkMemoryAllocation(void *ptr);

// swap two monos in array (polymon)
void swapMonoms(Monom *value1, Monom *value2);

// multiply two monoms -  return new value
Monom mulMonoms(Monom monom1, Monom monom2);

// print polymon by the rules
void printMonom(Monom c, bool shouldAddSign);

// organize polymon ( all same power combined )
void organizePolynom(Monom *polynom, int *size);

// create array of monoms from numbers ( by couples )
Monom *createPolynom(int *size, int *polynomNumbers, int polynomNumbersSize);

// sort polymon asc
void sortPolynom(Monom *polynom, int size);

// print polynom by the rules
void printPolynom(Monom *polynom, int size);

// main function
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

Monom *getPolynom(unsigned int *polynomSize) {
    char *str = getStringInput();
    int *intNumbers;
    int size = 0;
    Monom *polynom;

    intNumbers = convertStrToNumArray(str, &size);
    polynom = createPolynom(&size, intNumbers, size);
    organizePolynom(polynom, &size);
    sortPolynom(polynom, size);
    *polynomSize = size;
    free(intNumbers);

    return polynom;
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

Monom *createPolynom(int *size, int *polynomNumbers, int polynomNumbersSize) {
    int i, j;
    Monom *polynom = (Monom *) malloc(sizeof(Monom) * (*size));
    checkMemoryAllocation(polynom);

    for (i = 0, j = 0; i < *size - 1; i += 2, j++) {
        if (polynomNumbers[i] == 0) {
            i += 2;
        }
        polynom[j].coefficient = polynomNumbers[i];
        polynom[j].power = polynomNumbers[i + 1];
    }
    *size = j;
    return polynom;
}

void organizePolynom(Monom *polynom, int *size) {
    int i, j;
    int polynomSize = *size;
    for (i = 0; i < polynomSize; i++) {
        // check for monom with coefficient 0
        if (polynom[i].coefficient == 0) {
            swapMonoms(&polynom[i], &polynom[polynomSize - 1]);
            polynomSize--;
        }
        for (j = i + 1; j < polynomSize; j++) {
            if (polynom[i].power == polynom[j].power) {
                polynom[i].coefficient = polynom[i].coefficient + polynom[j].coefficient;
                swapMonoms(&polynom[j], &polynom[polynomSize - 1]);
                // in order to check with the swaped item
                j--;
                polynomSize--;
            }

            //check again after sum of two fields for monom with coefficient 0
            if (polynom[j].coefficient == 0) {
                swapMonoms(&polynom[j], &polynom[polynomSize - 1]);
                j--;
                polynomSize--;
            }
        }
    }

    // realloc size to real size after finished
    polynom = realloc(polynom, sizeof(Monom) * polynomSize);
    *size = polynomSize;
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

void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size) {
    int maxSize = polynom1Size * polynom2Size;
    Monom *newPolynom = (Monom *) malloc(sizeof(Monom) * maxSize);
    checkMemoryAllocation(newPolynom);

    int counter = 0;
    for (int index1 = 0; index1 < polynom1Size; index1++) {
        for (int index2 = 0; index2 < polynom2Size; index2++) {
            newPolynom[counter] = mulMonoms(polynom1[index1], polynom2[index2]);
            counter++;
        }
    }

    organizePolynom(newPolynom, &maxSize);
    sortPolynom(newPolynom, maxSize);
    printPolynom(newPolynom, maxSize);
    free(newPolynom);
}

void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size) {
    int maxSize = polynom1Size + polynom1Size;

    Monom *newPolynom = (Monom *) malloc(sizeof(Monom) * maxSize);
    checkMemoryAllocation(newPolynom);

    for (int index1 = 0; index1 < polynom1Size; index1++) {
        newPolynom[index1].coefficient = polynom1[index1].coefficient;
        newPolynom[index1].power = polynom1[index1].power;
    }
    for (int index2 = 0; index2 < polynom2Size; index2++) {
        newPolynom[polynom1Size + index2].coefficient = polynom2[index2].coefficient;
        newPolynom[polynom1Size + index2].power = polynom2[index2].power;
    }

    organizePolynom(newPolynom, &maxSize);
    sortPolynom(newPolynom, maxSize);
    printPolynom(newPolynom, maxSize);
    free(newPolynom);
}

Monom mulMonoms(Monom monom1, Monom monom2) {
    Monom newMonom;
    newMonom.coefficient = monom1.coefficient * monom2.coefficient;
    newMonom.power = monom1.power + monom2.power;
    return newMonom;
}

void printMonom(Monom c, bool shouldAddSign) {
    if (c.power == 0) {
        if (c.coefficient != 1) {
            if (shouldAddSign) {
                printf(" %d +", c.coefficient);
            } else {
                printf(" %d ", c.coefficient);
            }
        }
    } else if (c.power == 1 || c.power == -1) {
        if (c.coefficient == 1) {
            if (shouldAddSign) {
                printf(" X +");
            } else {
                printf(" X ");
            }
        } else if (c.coefficient == -1) {
            if (shouldAddSign) {
                printf(" -X +");
            } else {
                printf(" -X ");
            }
        } else {
            if (shouldAddSign) {
                printf(" %dX +", c.coefficient);
            } else {
                printf(" %dX ", c.coefficient);
            }
        }
    } else if (c.coefficient == 1) {
        if (shouldAddSign) {
            printf(" X^%d +", c.power);
        } else {
            printf(" X^%d ", c.power);
        }
    } else if (c.coefficient == -1) {
        if (shouldAddSign) {
            printf(" -X^%d +", c.power);
        } else {
            printf(" -X^%d ", c.power);
        }
    } else {
        if (shouldAddSign) {
            printf(" %dX^%d +", c.coefficient, c.power);
        } else {
            printf(" %dX^%d ", c.coefficient, c.power);
        }

    }
}

void printPolynom(Monom *polynom, int size) {
    int i;
    bool shouldPrintSign = true;
    for (i = 0; i <= size - 1; i++) {
        if (polynom[i + 1].coefficient < 0 || i + 1 == size) {
            shouldPrintSign = false;
        }
        printMonom(polynom[i], shouldPrintSign);
    }
    printf("\n");
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