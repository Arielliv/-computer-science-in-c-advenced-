//
// Created by 315363366 on 11/12/2021.
//

#ifndef Q_3_A_FILES_H
#define Q_3_A_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"

void Exe5Q3(char *fname);

StudentWithIndex **createStudentsListWithIndexesFromStudentsFile(FILE *fp, short int *numOfStudents);

StudentWithIndex *createStudentWithIndexFromStudentsFile(FILE *fp);

void sortStudents(StudentWithIndex **studentsList, short int numOfStudents);

void createStudentIndexFile(StudentWithIndex **studentsList, short int numOfStudents, char *fname);

void printStudentWithIndex(StudentWithIndex *studentWithIndex);

void freeAll(StudentWithIndex **studentsList, short int numOfStudents);
#endif //Q_3_A_FILES_H