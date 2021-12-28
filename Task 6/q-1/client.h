//
// Created by 315363366 on 28/12/2021.
//

#ifndef Q_1_CLIENT_H
#define Q_1_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include <stdbool.h>
#include <string.h>

typedef struct _client {
    char id[9];     // “12345678”
    char phone[12]; // “054-1234567”
} Client;

typedef struct _short_client {
    unsigned char short_id[4];
    unsigned char short_phone[5];
} Short_client;

Short_client *createShortClientArr(int n);

Client getClient();

void getClientId(char *id);

void getClientPhone(char *phone);

Short_client getShortClient(Client client);

void getShortId(unsigned char short_id[4], char id[9], int size);

void getShortPhone(unsigned char short_phone[5], char phone[12], int size);

void convertShortPhoneToRegular(char phone[12], unsigned char short_phone[5], int size);

int asciiToNumber(char num);

char numberToAscii(int num);

char *searchClientByID(Short_client *arr, int n, char *id);

char *findPhoneById(Short_client *arr, int size, unsigned char short_id[4]);

bool isUnsignedCharArrayEq(unsigned char *array1, unsigned char *array2, int size);

#endif //Q_1_CLIENT_H
