//
// Created by Ariel Livshits on 30/11/2021.
//
#include "utils.h"

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Memory allocation error");
        exit(1);
    }
}