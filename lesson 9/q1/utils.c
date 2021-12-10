//
// Created by Ariel Livshits on 10/12/2021.
//

#include "utils.h"

void checkFile(FILE *fp){
    if (fp == NULL){
        printf("Error opening File\n");
        exit(1);
    }
}