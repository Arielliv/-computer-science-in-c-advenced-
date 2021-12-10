//
// Created by 315363366 on 10/12/2021.
//

#ifndef Q_2_FILES_H
#define Q_2_FILES_H

#include <stdlib.h>
#include <stdio.h>
#include "employee.h"

void Exe5Q2(char *fname1, char *fname2);

int getLengthOfEmployeeListFile(FILE *fp);

Employee **readListOfEmployeesFile(FILE *fp, int *size);

Employee *readEmployeeFromFile(FILE *fp);

float *readListOfSalaryAddonsFile(FILE *fp, int numOfEmployees);

void updateEmployeesSalary(Employee **employees, float *SalaryAddons, int numOfEmployees);

void updateListOfEmployeesFile(FILE *fp, Employee **employees, int numOfEmployees);

#endif //Q_2_FILES_H
