//
// 315363366
//

#ifndef Q_3_LIST_H
#define Q_3_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct listNode {
    int data;
    struct listNode *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

void insertDataToEndList(List *lst, int data);

void makeEmptyList(List *lst);

void freeList(List *lst);

ListNode *createNewListNode(int data, ListNode *next);

bool isEmptyList(List *lst);

void insertNodeToEndListNode(List *lst, ListNode *newTail);

void insertDataToStartList(List *lst, int data);

void insertNodeToStartList(List *lst, ListNode *head);

ListNode *getListNode(List *lst, int i);

bool insertNodeToPlaceInList(List *lst, struct listNode *node, int i);

bool insertDataToPlaceInList(List *lst, int data, int i);

int findListNode(List *lst, int data);
void updateDataToPlaceInList(List *lst, int data, int i);

void printList(List lst);

#endif //Q_3_LIST_H
