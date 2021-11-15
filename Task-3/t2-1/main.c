// 315363366
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct listNode {
    int *dataPtr;
    struct listNode *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

List merge(List lst1, List lst2);

List getList();

void makeEmptyList(List *lst);

void printList(List *lst);

bool isEmptyList(List *lst);

void freeList(List *lst);

void insertDataToEndList(List *lst, int data);

void insertNodeToEndListNode(List *lst, ListNode *newTail);

ListNode *createNewListNode(int data, ListNode *next);

void main() {

    List lst1, lst2, mergedList;

    lst1 = getList();
    lst2 = getList();

    mergedList = merge(lst1, lst2);

    printf("Merged list:\n");
    printList(&mergedList);

    freeList(&lst1);
    freeList(&lst2);
    freeList(&mergedList);
}

List getList() {
    List res;
    int size, num, i;

    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);

    printf("Please enter the numbers:\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &num);
        insertDataToEndList(&res, num);
    }

    return res;

}

void makeEmptyList(List *lst) {
    lst->head = lst->tail = NULL;
}


void printList(List *lst) {
    ListNode *curr;

    curr = lst->head;

    while (curr != NULL) {
        printf("%d ", *(curr->dataPtr));
        curr = curr->next;
    }

    printf("\n");
}

bool isEmptyList(List *lst) {
    return (lst->head == NULL);
}

void freeList(List *lst) {
    ListNode *curr = lst->head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        free(curr->dataPtr);
        free(curr);
        curr = saver;
    }
}


void insertDataToEndList(List *lst, int data) {
    ListNode *newTail;

    newTail = createNewListNode(data, NULL);
    insertNodeToEndListNode(lst, newTail);
}

void insertNodeToEndListNode(List *lst, ListNode *newTail) {
    if (isEmptyList(lst)) {
        lst->head = lst->tail = newTail;
    } else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

ListNode *createNewListNode(int data, ListNode *next) {
    ListNode *res;

    res = (ListNode *) malloc(sizeof(ListNode));
    res->dataPtr = (int *) malloc(sizeof(int));
    *res->dataPtr = data;
    res->next = next;

    return res;
}

List merge(List lst1, List lst2) {
    List resultList;

    makeEmptyList(&resultList);

    if (isEmptyList(&lst1) && !isEmptyList(&lst2)) {
        resultList.head = lst2.head;
    } else if (isEmptyList(&lst2) && !isEmptyList(&lst1)) {
        resultList.head = lst1.head;
    } else {
        ListNode *curr1 = lst1.head;
        ListNode *curr2 = lst2.head;
        while (curr1 != NULL && curr2 != NULL) {
            if (*(curr1->dataPtr) >= *(curr2->dataPtr)) {
                insertDataToEndList(&resultList, *(curr1->dataPtr));
                curr1 = curr1->next;
            } else {
                insertDataToEndList(&resultList, *(curr2->dataPtr));
                curr2 = curr2->next;
            }
        }
        while (curr1 != NULL) {
            insertDataToEndList(&resultList, *(curr1->dataPtr));
            curr1 = curr1->next;
        }

        while (curr2 != NULL) {
            insertDataToEndList(&resultList, *(curr2->dataPtr));
            curr2 = curr2->next;
        }

    }

    return resultList;
}