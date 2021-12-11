//
// Created by 315363366 on 11/12/2021.
//

#include "files.h"
#include "utils.h"

char **findAverageGrade(char *database, int avgGrade, int *resSize) {
    int numOfStudents;
    char *newFileName = (char *) malloc(sizeof(char) * (strlen(database) + 4));
    checkMemoryAllocation(newFileName);
    sprintf(newFileName, "%s.ind", database);
    int *studentsIndexList = createStudentsIndexListFromFile(newFileName, &numOfStudents);
    FILE *fp = fopen(database, "rb");
    checkFile(fp);
    int foundIndex = studentBinarySearchByIndexesInFile(fp, studentsIndexList, 0, numOfStudents, avgGrade);
    return createStudentNamesListByIndex(fp, avgGrade, foundIndex, studentsIndexList, numOfStudents, resSize);
}

char **
createStudentNamesListByIndex(FILE *fp, int avg, int index, int studentsIndexList[], int numOfStudents, int *resSize) {
    int logSize = 0, phySize = 1;
    int studentsCounter = 0;
    bool isNotAvg = false;
    char **studentsNames = (char **) malloc(sizeof(char *) * phySize);
    checkMemoryAllocation(studentsNames);
    int loopUpIndex = index, loopDownIndex = index;
    if (index == -1) {
        *resSize = 0;
        return NULL;
    } else {
        studentsCounter++;
        studentsNames[logSize] = createStudentFromStudentsFileByIndex(fp, studentsIndexList[index])->name;
        logSize++;
        loopUpIndex++;
        loopDownIndex--;
        while (loopUpIndex < numOfStudents && isNotAvg == false) {
            if (logSize == phySize) {
                phySize *= 2;
                studentsNames = (char **) realloc(studentsNames, sizeof(char *) * phySize);
                checkMemoryAllocation(studentsNames);
            }
            STUDENT *tmpStudent = createStudentFromStudentsFileByIndex(fp, studentsIndexList[index]);
            if (tmpStudent->average == avg) {
                studentsNames[logSize] = tmpStudent->name;
                logSize++;
            }
            isNotAvg = true;
            loopUpIndex++;
        }
        isNotAvg = false;
        while (loopDownIndex > 0 && isNotAvg == false) {
            if (logSize == phySize) {
                phySize *= 2;
                studentsNames = (char **) realloc(studentsNames, sizeof(char *) * phySize);
                checkMemoryAllocation(studentsNames);
            }
            STUDENT *tmpStudent = createStudentFromStudentsFileByIndex(fp, studentsIndexList[index]);
            if (tmpStudent->average == avg) {
                studentsNames[logSize] = tmpStudent->name;
                logSize++;
            }
            isNotAvg = true;
            loopDownIndex--;
        }
        *resSize = studentsCounter;
        return studentsNames;
    }
}

int *createStudentsIndexListFromFile(char *fname, int *numOfStudents) {
    int logSize = 0, phySize = 1;
    int studentsIndexListCounter = 0;
    int *studentsIndexList = (int *) malloc(sizeof(int) * phySize);
    checkMemoryAllocation(studentsIndexList);

    FILE *fp = fopen(fname, "rb");
    checkFile(fp);
    fseek(fp, 0, SEEK_SET);

    while (1) {
        if (logSize == phySize) {
            phySize *= 2;
            studentsIndexList = (int *) realloc(studentsIndexList, sizeof(int) * phySize);
            checkMemoryAllocation(studentsIndexList);
        }
        int tmp;
        fread(&tmp, sizeof(int), 1, fp);

        if (feof(fp)) {
            break;
        }
        studentsIndexList[logSize] = tmp;
        logSize++;
        studentsIndexListCounter++;
    }
    *numOfStudents = studentsIndexListCounter;
    fclose(fp);
    return studentsIndexList;
}

int studentBinarySearchByIndexesInFile(FILE *fp, int studentsIndexList[], int left, int right, int searchedAvg) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        STUDENT *tmpStudent = createStudentFromStudentsFileByIndex(fp, studentsIndexList[mid]);
        if (tmpStudent->average == searchedAvg) {
            free(tmpStudent);
            return mid;
        }

        if (tmpStudent->average > searchedAvg) {
            free(tmpStudent);
            return studentBinarySearchByIndexesInFile(fp, studentsIndexList, left, mid - 1, searchedAvg);
        }

        free(tmpStudent);
        return studentBinarySearchByIndexesInFile(fp, studentsIndexList, mid + 1, right, searchedAvg);
    }

    return -1;
}


STUDENT *createStudentFromStudentsFileByIndex(FILE *fp, int index) {
    // why fseek(fp, 0, index); doesn't work ?
    fseek(fp, index, SEEK_SET);

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

    return currStudent;
}