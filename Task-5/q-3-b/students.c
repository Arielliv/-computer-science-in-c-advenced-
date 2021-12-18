//
// Created by 315363366 on 11/12/2021.
//
#define _CRT_SECURE_NO_WARNINGS
#include "students.h"

void freeStudent(STUDENT *student) {
    free(student->name);
    free(student);
}