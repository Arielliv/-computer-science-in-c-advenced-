//
// Created by 315363366 on 10/12/2021.
//

#include "utils.h"

void checkFile(FILE *fp){
    if (fp == NULL){
        printf("Error opening File\n");
        exit(1);
    }
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Memory allocation error");
        exit(1);
    }
}