//
// Created by Ariel Livshits on 10/12/2021.
//

#include "student.h"
#include "utils.h"

void saveStudentsToFile(Student *allStudents, int numOfStudents, char *fileName) {
    FILE *fp = fopen(fileName, "wb");
    checkFile(fp);

    // fwrite returns num of object written which succeeded
    if (fwrite(allStudents, sizeof(Student), numOfStudents, fp) != numOfStudents) {
        printf("error writing");
        exit(1);
    }
    fclose(fp);
}

void sortStudentsInFile(int *numOfStudents, char *fileName) {
    FILE *fp = fopen(fileName, "r+b");
    fseek(fp, 0, SEEK_END);
    // ftell - return num of the indicator location
    *numOfStudents = ftell(fp) / sizeof(Student);

    for (int i = (*numOfStudents) - 1; i > 0; i--) {
        fseek(fp, 0, SEEK_SET);
        for (int j = 0; j < i; j++) {
            Student temp1, temp2;

            fread(&temp1, sizeof(Student), 1, fp);
            fread(&temp2, sizeof(Student), 1, fp);

            if (temp1.avg > temp2.avg) {
                fseek(fp, (-2) * (int) sizeof(Student), SEEK_CUR);

                fwrite(&temp2, sizeof(Student), 1, fp);
                fwrite(&temp1, sizeof(Student), 1, fp);
            }
            fseek(fp, (-1) * (int) sizeof(Student), SEEK_CUR);
        }
    }
    fclose(fp);
}

Student *loadStudentsFromFile(int numOfStudents, char *fileName) {
    FILE *fp = fopen(fileName, "rb");
    Student *allStudents = (Student *) malloc(sizeof(Student) * numOfStudents);

    fread(allStudents, sizeof(Student), numOfStudents, fp);
    fclose(fp);
    return allStudents;
}

void printStudents(Student *allStudents, int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        printf("Id: %d ", allStudents[i].id);
        printf("Name: %s ", allStudents[i].name);
        printf("Avg: %.2f \n", allStudents[i].avg);
    }
}