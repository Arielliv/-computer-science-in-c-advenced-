//
// Created by Ariel Livshits on 10/12/2021.
//

#ifndef Q1_STUDENT_H
#define Q1_STUDENT_H

#include <stdlib.h>
#include <stdio.h>

#define FILE_NAME "student.dat"
typedef struct student {
    char name[10];
    int id;
    float avg;
} Student;

void saveStudentsToFile(Student *allStudents, int numOfStudents, char *fileName);

void sortStudentsInFile(int *numOfStudents, char *fileName);

Student *loadStudentsFromFile(int numOfStudents, char *fileName);

void printStudents(Student *allStudents, int numOfStudents);

#endif //Q1_STUDENT_H
