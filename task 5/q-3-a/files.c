//
// Created by 315363366 on 11/12/2021.
//
#include "files.h"
#include "utils.h"

void Exe5Q3(char *fname) {
    FILE *fp = fopen(fname, "rb");
    checkFile(fp);
    short int numOfStudents;
    StudentWithIndex **studentWithIndexArray = createStudentsListWithIndexesFromStudentsFile(fp, &numOfStudents);
    fclose(fp);
    sortStudents(studentWithIndexArray, numOfStudents);
    createStudentIndexFile(studentWithIndexArray, numOfStudents, fname);
    freeAll(studentWithIndexArray, numOfStudents);
}

StudentWithIndex **createStudentsListWithIndexesFromStudentsFile(FILE *fp, short int *numOfStudents) {
    fread(numOfStudents, sizeof(short int), 1, fp);
    StudentWithIndex **listOfStudentWithIndex = (StudentWithIndex **) malloc(
            sizeof(StudentWithIndex *) * (*numOfStudents));
    checkMemoryAllocation(listOfStudentWithIndex);
    for (int i = 0; i < *numOfStudents; i++) {
        StudentWithIndex *currStudentWithIndex = createStudentWithIndexFromStudentsFile(fp);
        listOfStudentWithIndex[i] = currStudentWithIndex;
    }

    return listOfStudentWithIndex;
};

StudentWithIndex *createStudentWithIndexFromStudentsFile(FILE *fp) {
    int currIndex = (int) ftell(fp);
    StudentWithIndex *currStudentWithIndex = (StudentWithIndex *) malloc(sizeof(StudentWithIndex));
    checkMemoryAllocation(currStudentWithIndex);
    STUDENT *currStudent = (STUDENT *) malloc(sizeof(STUDENT));
    checkMemoryAllocation(currStudent);
    short int currNameSize;
    fread(&currNameSize, sizeof(short int), 1, fp);

    char *currName = (char *) malloc(sizeof(char) * currNameSize);
    checkMemoryAllocation(currName);
    fread(currName, sizeof(char) * currNameSize, 1, fp);

    int currAvg;
    fread(&currAvg, sizeof(int), 1, fp);
    currStudent->name = currName;
    currStudent->average = currAvg;
    currStudentWithIndex->student = currStudent;
    currStudentWithIndex->index = currIndex;
    printStudentWithIndex(currStudentWithIndex);
    return currStudentWithIndex;
}

void printStudentWithIndex(StudentWithIndex *studentWithIndex) {
    printf("index : %d ", studentWithIndex->index);
    printf("name : %s ", studentWithIndex->student->name);
    printf("avg : %d \n", studentWithIndex->student->average);
}

void sortStudents(StudentWithIndex **studentsList, short int numOfStudents) {
    mergeSortStudentWithIndex(studentsList, numOfStudents);
    printf("\n");
    for (int i = 0; i < numOfStudents; i++) {
        printStudentWithIndex(studentsList[i]);
    }
}

void createStudentIndexFile(StudentWithIndex **studentsList, short int numOfStudents, char *fname) {
    char *newFileName = (char *) malloc(sizeof(char) * (strlen(fname) + 4));
    checkMemoryAllocation(newFileName);
    sprintf(newFileName, "%s.ind", fname);
    FILE *fp = fopen(newFileName, "wb");
    checkFile(fp);
    for (int i = 0; i < numOfStudents; i++) {
        fwrite(&studentsList[i]->index, sizeof(int), 1, fp);
    }
    fclose(fp);
}

void freeAll(StudentWithIndex **studentsList, short int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        free(studentsList[i]->student->name);
        free(studentsList[i]->student);
        free(studentsList[i]);
    }
    free(studentsList);
}