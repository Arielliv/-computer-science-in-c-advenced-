//
// Created by 315363366 on 11/12/2021.
//

#ifndef Q_3_A_STUDENTS_H
#define Q_3_A_STUDENTS_H

typedef struct student {
    char *name;
    int average;
} STUDENT;

typedef struct studentWithIndex {
    STUDENT *student;
    int index;
} StudentWithIndex;

void mergeSortStudentWithIndex(StudentWithIndex **array, short int size);

void copyArray(StudentWithIndex **des, StudentWithIndex **src, short int size);

StudentWithIndex **mergeArrays(StudentWithIndex **array1, short int size1, StudentWithIndex **array2, short int size2);

#endif //Q_3_A_STUDENTS_H
