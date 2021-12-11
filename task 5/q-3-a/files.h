//
// Created by 315363366 on 11/12/2021.
//

#ifndef Q_3_A_FILES_H
#define Q_3_A_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"

typedef struct studentWithIndex {
    STUDENT student;
    int index;
} StudentWithIndex;


void Exe5Q3(char *fname);

StudentWithIndex *createStudentsListWithIndexesFromStudentsFile(FILE *fp, int *numOfStudents);

STUDENT createStudentWithIndexFromStudentsFile(FILE *fp);

void sortStudents(STUDENT *studentsList, int numOfStudents);

void createStudentIndexFile(STUDENT *studentsList, int numOfStudents);


#endif //Q_3_A_FILES_H