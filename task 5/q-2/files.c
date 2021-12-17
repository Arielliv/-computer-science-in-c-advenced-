//
// Created by 315363366 on 10/12/2021.
//
#include "files.h"
#include "employee.h"
#include "utils.h"

void Exe5Q2(char *fname1, char *fname2) {
    int numOfEmployees;
    FILE *fp1 = fopen(fname1, "r+b");
    checkFile(fp1);
    FILE *fp2 = fopen(fname2, "rb");
    checkFile(fp2);
    Employee **listOfEmployees = readListOfEmployeesFile(fp1, &numOfEmployees);
    float *salaryArray = readListOfSalaryAddonsFile(fp2, numOfEmployees);
    updateEmployeesSalary(listOfEmployees, salaryArray, numOfEmployees);
    sortEmployeesList(listOfEmployees, numOfEmployees);
    updateListOfEmployeesFile(fp1, listOfEmployees, numOfEmployees);
    fclose(fp1);
    fclose(fp2);
    freeAll(listOfEmployees, salaryArray, numOfEmployees);
}

Employee **readListOfEmployeesFile(FILE *fp, int *size) {
    int logSize = 0, phySize = 1;
    int employeeCounter = 0;
    Employee **listOfEmployees = (Employee **) malloc(sizeof(Employee *) * phySize);
    checkMemoryAllocation(listOfEmployees);

    fseek(fp, 0, SEEK_SET);

    while (1) {
        if (logSize == phySize) {
            phySize *= 2;
            listOfEmployees = (Employee **) realloc(listOfEmployees, sizeof(Employee *) * phySize);
            checkMemoryAllocation(listOfEmployees);
        }
        Employee *currEmployee = readEmployeeFromFile(fp);
        if (feof(fp)) {
            break;
        }
        listOfEmployees[employeeCounter] = currEmployee;
        logSize++;
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

float *readListOfSalaryAddonsFile(FILE *fp, int numOfEmployees) {
    float *salaryArray = (float *) malloc(sizeof(float) * numOfEmployees);
    fread(salaryArray, sizeof(float) * numOfEmployees, 1, fp);
    return salaryArray;
}

void updateEmployeesSalary(Employee **employees, float *salaryAddons, int numOfEmployees) {
    for (int i = 0; i < numOfEmployees; i++) {
        employees[i]->salary += salaryAddons[i];
    }
}

void sortEmployeesList(Employee **employees, int numOfEmployees) {
    for (int i = 0; i < numOfEmployees - 1; i++) {
        for (int j = 0; j < numOfEmployees - i - 1; j++) {
            if (employees[j]->salary < employees[j + 1]->salary) {
                swapEmployees(employees[j], employees[j + 1]);
            }
        }
    }
}

void swapEmployees(Employee *employee1, Employee *employee2) {
    Employee tmp = *employee1;
    *employee1 = *employee2;
    *employee2 = tmp;
}


void updateListOfEmployeesFile(FILE *fp, Employee **employees, int numOfEmployees) {
    fseek(fp, 0, SEEK_SET);
    for (int i = 0; i < numOfEmployees; i++) {
        fwrite(&employees[i]->name_length, sizeof(int), 1, fp);
        fwrite(employees[i]->name, sizeof(char) * employees[i]->name_length, 1, fp);
        fwrite(&employees[i]->salary, sizeof(float), 1, fp);
    }
}

void freeAll(Employee **employees, float *salaryAddons, int numOfEmployees) {
    for (int i = 0; i < numOfEmployees; i++) {
        free(employees[i]->name);
        free(employees[i]);
    }
    free(employees);
    free(salaryAddons);
}