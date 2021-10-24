// 315363366
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define OperationSign "%"
#define Decimal 'd'
#define Octal 'o'
#define Hax 'x'
#define Roman 'r'
#define Binary 'b'

// print string with the right numbers formatted
void printFormattedIntegers(char *format, char *numbers);

// create and return array of numbers from string of numbers
int *convertStrToNumArray(char *strNums);

// print decimal as hex
void printHex(int num);

// print decimal as decimal number
void printDecimal(int num);

// print decimal as octal number
void printOctal(int num);

// print decimal as roman number
void printRoman(int num);

// print decimal as binary number
void printBinary(int num);

// powersTen
int powersTen(int num, int power);

// check memory allocation
void checkMemoryAllocation(void *ptr);

int main() {
    char format[100];

    char numbers[100];

    gets(format);

    gets(numbers);

    printFormattedIntegers(format, numbers);
}

void printFormattedIntegers(char *format, char *numbers) {
    char *token;
    int *intNumbers;
    int i = 0;
    intNumbers = convertStrToNumArray(numbers);
    token = strtok(format, OperationSign);
    while (token != NULL) {
        switch (token[0]) {
            case Decimal: {
                printDecimal(intNumbers[i]);
                token++;
                printf("%s", token);
                i++;
                break;
            }
            case Hax: {
                printHex(intNumbers[i]);
                token++;
                printf("%s", token);
                i++;
                break;
            }
            case Octal: {
                printOctal(intNumbers[i]);
                token++;
                printf("%s", token);
                i++;
                break;
            }
            case Binary: {
                printBinary(intNumbers[i]);
                token++;
                printf("%s", token);
                i++;
                break;
            }
            case Roman: {
                printRoman(intNumbers[i]);
                token++;
                printf("%s", token);
                i++;
                break;
            }
            default: {
                printf("%s", token);
                break;
            }
        }
        token = strtok(NULL, OperationSign);
    }
    free(intNumbers);
}

int *convertStrToNumArray(char *strNums) {
    char *token;
    int *numbers;
    int i = 0;

    numbers = (int *) malloc(100 * sizeof(int));
    checkMemoryAllocation(numbers);

    token = strtok(strNums, " ");
    while (token != NULL) {
        sscanf(token, "%d", &numbers[i]);
        token = strtok(NULL, " ");
        i++;
    }
    return numbers;
}

void printHex(int num) {
    printf("%X", num);
}

void printDecimal(int num) {
    printf("%d", num);
}

void printOctal(int num) {
    printf("%o", num);
}

void printRoman(int num) {
    //skip first
    char *m[] = {"", "M", "MM", "MMM"};
    char *c[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    char *x[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    char *i[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    // Converting to roman
    char *thousands = m[num / 1000];
    char *hundreds = c[(num % 1000) / 100];
    char *tens = x[(num % 100) / 10];
    char *ones = i[num % 10];

    //concat the whole number
    printf("%s%s%s%s", thousands, hundreds, tens, ones);
}

int powersTen(int num, int power) {
    int i;
    if (num == 0) {
        return num;
    } else {
        for (i = 0; i < power; i++) {
            num *= 10;
        }
    }
    return num;
}

void printBinary(int num) {
    int count = 0;
    int binNum = 0;
    int remainder;
    while (num != 0) {
        remainder = num % 2;
        binNum += powersTen(remainder, count);
        num /= 2;
        count++;
    }
    printf("%d", binNum);
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}