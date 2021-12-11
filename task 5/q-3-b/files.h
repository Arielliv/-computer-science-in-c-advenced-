//
// Created by 315363366 on 11/12/2021.
//

#ifndef Q_3_B_FILES_H
#define Q_3_B_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "students.h"

char **findAverageGrade(char *database, int avgGrade, int *resSize);

int *createStudentsIndexListFromFile(char *fname, int *numOfStudents);

STUDENT *createStudentFromStudentsFileByIndex(FILE *fp, int index);

char **
createStudentNamesListByIndex(FILE *fp, int avg, int index, int studentsIndexList[], int numOfStudents, int *resSize);

int studentBinarySearchByIndexesInFile(FILE *fp, int studentsIndexList[], int left, int right, int searchedAvg);

#endif //Q_3_B_FILES_H
