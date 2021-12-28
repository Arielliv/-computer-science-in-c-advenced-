//
// Created by 315363366 on 28/12/2021.
//
#define _CRT_SECURE_NO_WARNINGS

#include "client.h"

Short_client *createShortClientArr(int n) {
    int i;
    Client *clients = (Client *) malloc(sizeof(Client) * n);
    checkMemoryAllocation(clients);
    for (i = 0; i < n; i++) {
        Client tmpClient = getClient();
        clients[i] = tmpClient;
    }

    Short_client *shortClients = (Short_client *) malloc(sizeof(Short_client) * n);
    checkMemoryAllocation(shortClients);

    for (i = 0; i < n; i++) {
        Short_client tmpShortClient = getShortClient(clients[i]);
        shortClients[i] = tmpShortClient;
    }
    free(clients);

    return shortClients;
}

Client getClient() {
    Client newClient;
    getClientId(newClient.id);
    getClientPhone(newClient.phone);
    return newClient;
}

void getClientId(char *id) {
    printf("Please enter your ID (8 numbers without check digit ) \n");
    scanf("%s", id);
}

void getClientPhone(char *phone) {
    printf("Please enter phone number (12 numbers - first 3 numbers then '-' and then another 7 numbers) \n");
    scanf("%s", phone);
}

Short_client getShortClient(Client client) {
    Short_client newShortClient;

    getShortId(newShortClient.short_id, client.id, 8);
    getShortPhone(newShortClient.short_phone, client.phone, 11);

    return newShortClient;
}

void getShortId(unsigned char short_id[4], char id[9], int size) {
    int i;
    int counter = 0;
    int res;
    char copyId[9];
    strncpy(copyId, id, 9);
    for (i = 0; i < size; i += 2) {
        res = 0x00;
        res = (asciiToNumber(copyId[i]) | res);
        res = ((asciiToNumber(copyId[i + 1]) << 4) | res);
        short_id[counter] = res;
        counter++;
    }
}

void getShortPhone(unsigned char short_phone[5], char phone[12], int size) {
    int i;
    int counter = 0;
    int res;
    char copyPhone[12];
    strncpy(copyPhone, phone, 12);
    for (i = 0; i < size; i += 2) {
        res = 0x00;
        res = (asciiToNumber(copyPhone[i]) | res);
        if (i + 1 == 3) {
            i++;
        }
        res = ((asciiToNumber(copyPhone[i + 1]) << 4) | res);
        short_phone[counter] = res;
        counter++;
    }
}

void convertShortPhoneToRegular(char phone[12], unsigned char short_phone[5], int size) {
    int i;
    int res;
    int mask = 0x0F;
    int counter = 0;
    for (i = 0; i < size; i++) {
        res = 0x00;

        phone[counter] = numberToAscii((short_phone[i] & mask));
        counter++;
        if (i == 1) {
            phone[counter] = '-';
            counter++;
            phone[counter] = numberToAscii((short_phone[i] >> 4 | res));
            counter++;
        } else {
            phone[counter] = numberToAscii((short_phone[i] >> 4 | res));

            counter++;
        }

    }
    phone[11] = '\0';
}

int asciiToNumber(char num) {
    return num - '0';
}

char numberToAscii(int num) {
    return (char) num + '0';
}


char *searchClientByID(Short_client *arr, int n, char *id) {
    unsigned char short_id[4];
    getShortId(short_id, id, 8);
    return findPhoneById(arr, n, short_id);
}

char *findPhoneById(Short_client *arr, int size, unsigned char short_id[4]) {
    int i;
    int isFound = false;
    char *phone = (char *) malloc(sizeof(char) * 12);
    for (i = 0; i < size; ++i) {
        if (isUnsignedCharArrayEq(arr[i].short_id, short_id, 4) == true) {
            convertShortPhoneToRegular(phone, arr[i].short_phone, 5);
            isFound = true;
        }
    }
    if (isFound == true) {
        return phone;
    } else {
        return NULL;
    }
}

bool isUnsignedCharArrayEq(unsigned char *array1, unsigned char *array2, int size) {
    int i;
    bool isEq = true;
    for (i = 0; i < size; i++) {
        if (array1[i] != array2[i]) {
            isEq = false;
        }
    }
    return isEq;
}