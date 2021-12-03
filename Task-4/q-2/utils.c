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

int charToInt(unsigned char num) {
    return (num - '0');
}

int calc(int num1, unsigned char operator, int num2) {
    if (operator == '+') {
        return num1 + num2;
    } else if (operator == '-') {
        return num1 - num2;
    } else if (operator == '*') {
        return num1 * num2;
    } else if (operator == '/') {
        return num1 / num2;
    } else if (operator == '%') {
        return num1 % num2;
    } else {
        return -1;
    }
}