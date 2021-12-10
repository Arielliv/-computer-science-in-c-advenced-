#include "student.h"

void main() {
    Student allStudents[5] = {
            {"Adi", 14587, 100},
            {"Benyamin", 14392, 85},
            {"Eden", 48392, 70},
            {"Ariel", 38094, 110},
            {"David", 92847, 90}
    };

    int numOfStudents;
    Student* studentFromFile;

    saveStudentsToFile(allStudents, 5, FILE_NAME);
    sortStudentsInFile(&numOfStudents, FILE_NAME);
    studentFromFile = loadStudentsFromFile(numOfStudents, FILE_NAME);
    printStudents(studentFromFile, numOfStudents);
}
