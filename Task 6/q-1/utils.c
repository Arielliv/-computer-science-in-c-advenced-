//
// Created by 315363366 on 28/12/2021.
//

#define _CRT_SECURE_NO_WARNINGS

#include "utils.h"

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Memory allocation error");
        exit(1);
    }
}
