//
// Created by 315363366 on 10/12/2021.
//

#ifndef Q1_FILES_H
#define Q1_FILES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Exe5Q1(char *fname, unsigned int x);

char **creatStrArrayFromFile(FILE *fp, int numOfItems);

void sortLexicographically(char *strArray[], int size);

void createTextFile(char *fname, char *strArray[], int size);

void freeAll(char *strArray[], int size);

#endif //Q1_FILES_H
