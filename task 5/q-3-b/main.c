#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "files.h"

//// argv[1] - name of the file
//// argv[2] - number for avgGrade
void printNames(char **records, int size);

void main() {
    char **records, fname[] = "Exe5Q3.bin";
    int resSize = 0;

    records = findAverageGrade(fname, 85, &resSize);
    printNames(records, resSize);
}

void printNames(char **records, int size) {

    int i;
    printf("The students names are:\n");

    for (i = 0; i < size; i++)
        printf("%s\n", records[i]);

}