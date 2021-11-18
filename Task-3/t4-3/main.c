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

List mergeHelper(List lst1, List lst2);

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
    if (isEmptyList(&lst1) && !isEmptyList(&lst2)) {
        return lst2;
    } else if (isEmptyList(&lst2) && !isEmptyList(&lst1)) {
        return lst1;
    } else {
        if (*(lst1.head->dataPtr) >= *(lst2.head->dataPtr)) {
            return mergeHelper(lst1, lst2);
        } else {
            return mergeHelper(lst2, lst1);
        }
    }
}

List mergeHelper(List lst1, List lst2) {
    ListNode *curr1 = lst1.head;
    ListNode *curr2 = lst2.head;
    ListNode *saver1 = NULL;
    ListNode *saver2 = NULL;
    while (curr1 != NULL && curr2 != NULL) {
        if (*(curr1->dataPtr) >= *(curr2->dataPtr)) {
            saver1 = curr1;
            curr1 = curr1->next;
        } else {
            saver2 = curr2->next;
            curr2->next = curr1;
            saver1->next = curr2;
            saver1 = saver1->next;
            curr2 = saver2;
        }
    }

    if (curr2 != NULL) {
        saver1->next = curr2;
    }

    return lst1;
}

