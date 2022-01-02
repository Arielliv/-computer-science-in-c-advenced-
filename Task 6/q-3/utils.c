// 315363366
#define _CRT_SECURE_NO_WARNINGS

#include "utils.h"

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Memory allocation error");
        exit(1);
    }
}