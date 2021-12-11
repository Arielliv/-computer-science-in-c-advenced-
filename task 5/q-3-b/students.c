//
// Created by 315363366 on 11/12/2021.
//
#include "students.h"

void freeStudent(STUDENT *student) {
    free(student->name);
    free(student);
}