//
// Created by 315363366 on 10/12/2021.
//

#include "files.h"
#include "utils.h"

void Exe5Q1(char *fname, unsigned int x) {
    FILE *fp = fopen(fname, "rb");
    checkFile(fp);
    char **strArray = creatStrArrayFromFile(fp, x);
    fclose(fp);
    sortLexicographically(strArray, x);
//    for (int i = 0; i < x; i++) {
//        printf("str [%d] : %s\n", i, strArray[i]);
//    }

    createTextFile(fname, strArray, x);
    freeAll(strArray, x);
}

//char **creatStrArrayFromFile(FILE *fp, int numOfItems) {
//    char **newStrArray = (char **) malloc(sizeof(char *) * numOfItems);
//    int sizeOfCurrentStr;
//    fseek(fp, 0, SEEK_SET);
//    for (int i = 0; i < numOfItems; i++) {
//        fread(&sizeOfCurrentStr, sizeof(int), 1, fp);
//        char *currentStr = (char *) malloc(sizeof(char) * sizeOfCurrentStr);
//        fread(currentStr, sizeof(char) * sizeOfCurrentStr, 1, fp);
//        newStrArray[i] = currentStr;
//    }
//    return newStrArray;
//}

char **creatStrArrayFromFile(FILE *fp, int numOfItems) {
    char **newStrArray = (char **) malloc(sizeof(char *) * numOfItems);
    checkMemoryAllocation(newStrArray);
    int sizeOfCurrentStr;

    fseek(fp, 0, SEEK_SET);
    for (int i = 0; i < numOfItems; i++) {
        int currentCounter = 0;
        fread(&sizeOfCurrentStr, sizeof(int), 1, fp);
        char *currentStr = (char *) malloc(sizeof(char) * sizeOfCurrentStr);
        checkMemoryAllocation(currentStr);

        for (int j = 0; j < sizeOfCurrentStr; j++) {
            char tmpChar;
            fread(&tmpChar, sizeof(char), 1, fp);
            if (tmpChar >= 'a' && tmpChar <= 'z') {
                strncat(currentStr, &tmpChar, 1);
                currentCounter++;
            }

        }
        currentStr += '\0';
        currentStr = (char *) realloc(currentStr, currentCounter + 1);
        checkMemoryAllocation(currentStr);
//        printf("str [%d] : %s\n", i, currentStr);
        newStrArray[i] = currentStr;
    }

    return newStrArray;
}

void sortLexicographically(char *strArray[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // swapping strings if they are not in the lexicographical order
            if (strcmp(strArray[i], strArray[j]) > 0) {
                int tempStrSize = strlen(strArray[i]);
                char *temp = (char *) malloc(sizeof(char) * tempStrSize);
                checkMemoryAllocation(temp);

                strcpy(temp, strArray[i]);
                strcpy(strArray[i], strArray[j]);
                strcpy(strArray[j], temp);
            }
        }
    }
}

void createTextFile(char *fname, char *strArray[], int size) {
    char *newFileName = (char *) malloc(sizeof(char) * (strlen(fname) + 4));
    checkMemoryAllocation(newFileName);
    sprintf(newFileName, "%s.txt", fname);
    FILE *fp = fopen(newFileName, "w");
    checkFile(fp);
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s\n", strArray[i]);
    }
    fclose(fp);
}

void freeAll(char *strArray[], int size) {
    for (int i = 0; i < size; ++i) {
        free(strArray[i]);
    }
    free(strArray);
}