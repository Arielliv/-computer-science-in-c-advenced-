//
// Created by 315363366 on 11/12/2021.
//
#include "files.h"

void Exe5Q3(char *fname) {};

StudentWithIndex *createStudentsListWithIndexesFromStudentsFile(FILE *fp, int *numOfStudents);

STUDENT createStudentWithIndexFromStudentsFile(FILE *fp);

void sortStudents(STUDENT *studentsList, int numOfStudents);

void createStudentIndexFile(STUDENT *studentsList, int numOfStudents);
