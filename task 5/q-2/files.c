//
// Created by 315363366 on 10/12/2021.
//
#include "files.h"
#include "employee.h"
#include "utils.h"

void Exe5Q2(char *fname1, char *fname2) {
    int employeeListSize;
    FILE *fp1 = fopen(fname1, "r+b");
    checkFile(fp1);
    FILE *fp2 = fopen(fname2, "rb");
    checkFile(fp2);
    Employee **listOfEmployees = readListOfEmployeesFile(fp1, &employeeListSize);

}

Employee **readListOfEmployeesFile(FILE *fp, int *size) {
    int employeeCounter = 0;
    Employee **listOfEmployees = (Employee **) malloc(sizeof(Employee *) * 1);
    fseek(fp, 0, SEEK_SET);

    while (1) {
        Employee *currEmployee = readEmployeeFromFile(fp);
        if (feof(fp)) {
            break;
        }
        listOfEmployees[employeeCounter] = currEmployee;
        printf("[%d] name  %s ", employeeCounter, currEmployee->name);
        printf("[%d] salary  %.00f \n", employeeCounter, currEmployee->salary);
        employeeCounter++;
    }
    *size = employeeCounter;
    return listOfEmployees;
}

Employee *readEmployeeFromFile(FILE *fp) {
    Employee *currEmployee = (Employee *) malloc(sizeof(Employee));

    int currNameSize;
    fread(&currNameSize, sizeof(int), 1, fp);

    char *currName = (char *) malloc(sizeof(char) * currNameSize);
    fread(currName, sizeof(char) * currNameSize, 1, fp);

    float currSalary;
    fread(&currSalary, sizeof(float), 1, fp);
    currEmployee->name = currName;
    currEmployee->salary = currSalary;
    currEmployee->name_length = currNameSize;

    return currEmployee;
}

float *readListOfSalaryAddonsFile(FILE *fp, int numOfEmployees);

void updateEmployeesSalary(Employee **employees, float *SalaryAddons, int numOfEmployees);

void updateListOfEmployeesFile(FILE *fp, Employee **employees, int numOfEmployees);
