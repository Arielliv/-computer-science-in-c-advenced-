//
// Created by 315363366 on 11/12/2021.
//

#ifndef Q_3_B_STUDENTS_H
#define Q_3_B_STUDENTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    char *name;
    int average;
} STUDENT;

void freeStudent(STUDENT * student);

#endif //Q_3_B_STUDENTS_H
