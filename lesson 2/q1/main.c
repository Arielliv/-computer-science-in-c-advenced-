#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define INIT_SIZE 1

int readText(char ***ptext);

char *findMaxLen(char **text, int size);

void myFree(char **text, int size);

int main() {
    char **text;
    int size;
    char *maxRow;
    size = readText(&text);
    maxRow = findMaxLen(text, size);
    printf("The longest row is: \"%s\"\n", maxRow);
    myFree(text, size);
    return 0;
}


int readText(char ***ptext) {

}

char *findMaxLen(char **text, int size) {

}

void myFree(char **text, int size) {

}