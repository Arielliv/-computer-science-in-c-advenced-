#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define INIT_SIZE 1

int readText(char ***ptext);

char *findMaxLen(char **text, int size);

void myFree(char **text, int size);

void checkMemoryAllocation(void *ptr);

int main() {
    char **text;
    int size;
    char *maxRow;
    size = readText(&text);
    if (size != 0) {
        maxRow = findMaxLen(text, size);
        printf("The longest row is: \"%s\"\n", maxRow);
        myFree(text, size);
    }

    return 0;
}


int readText(char ***ptext) {
    int logSize = 0, phsSize = INIT_SIZE;
    char **text;

    text = (char **) malloc(sizeof(char *) * INIT_SIZE);
    checkMemoryAllocation(text);
    char staticLine[MAX_LINE_LEN + INIT_SIZE];

    // in cae you want a static size str
    // char *dynamicLine = (char *) malloc(sizeof(char) * MAX_LINE_LEN + INIT_SIZE);

    puts("Please enter sentences");
    gets(staticLine);

    if (staticLine[0] == '\0') {
        free(text);
        *ptext = NULL;
        return 0;
    }
    // another way to check
    //    while (strcmp(staticLine, "\0") != 0) {
    //
    //    }
    while (staticLine[0] != '\0') {
        if (logSize == phsSize) {
            phsSize *= 2;
            text = (char **) realloc(text, phsSize * sizeof(char *));
            checkMemoryAllocation(text);
        }
        text[logSize] = (char *) malloc(strlen(staticLine) + 1 * sizeof(char));
        checkMemoryAllocation(text[logSize]);
        strcpy(text[logSize], staticLine);
        logSize++;
        gets(staticLine);
    }
    if (logSize < phsSize) {
        text = (char **) realloc(text, logSize * sizeof(char *));
        checkMemoryAllocation(text);
    }

    *ptext = text;
    return phsSize;

}

char *findMaxLen(char **text, int size) {
    int maxIndex = 0;
    int i;

    for (i = 1; i < size; i++) {
        if (strlen(text[i]) > strlen(text[maxIndex])) {
            maxIndex = i;
        }
    }

    return text[maxIndex];
}

void myFree(char **text, int size) {
    int i;
    for (i = 0; i < size; i++) {
        free(text[i]);
    }
    free(text);
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}
