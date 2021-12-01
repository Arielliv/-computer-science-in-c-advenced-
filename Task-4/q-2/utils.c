//
// 315363366
//

#include "utils.h"

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Memory allocation error");
        exit(1);
    }
}

bool isOneDigitNumber(char num) {
    if (num >= '0' && num <= '9') {
        return true;
    } else {
        return false;
    }
}

bool isOperatorSign(char sign) {
    if (sign == '+' || sign == '-' || sign == ':' || sign == '*' || sign == '%') {
        return true;
    } else {
        return false;
    }
}

bool isBracketsSign(char sign) {
    if (sign == '(' || sign == ')') {
        return true;
    } else {
        return false;
    }
}