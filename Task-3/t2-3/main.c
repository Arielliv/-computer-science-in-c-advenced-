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

void insertNodeToStartList(List *lst, struct listNode *head);

void insertDataToStartList(List *lst, int data);

void mergeHelper(ListNode *lnode1, ListNode *lnode2, List *resultList);

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

void insertDataToStartList(List *lst, int data) {
    ListNode *newHead;
    newHead = createNewListNode(data, NULL);
    insertNodeToStartList(lst, newHead);
}

void insertNodeToStartList(List *lst, struct listNode *head) {
    if (isEmptyList(lst) == true) {
        head->next = NULL;
        lst->head = lst->tail = head;
    } else {
        head->next = lst->head;
        lst->head = head;
    }
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

    mergeHelper(lst1.head, lst2.head, &resultList);
    return resultList;
}

void mergeHelper(ListNode *lnode1, ListNode *lnode2, List *resultList) {
    if (lnode1 == NULL && lnode2 == NULL) {
        return;
    } else if (lnode1 == NULL) {
        insertDataToEndList(resultList, *(lnode2->dataPtr));
        mergeHelper(lnode1, lnode2->next, resultList);
    } else if (lnode2 == NULL) {
        insertDataToEndList(resultList, *(lnode1->dataPtr));
        mergeHelper(lnode1->next, lnode2, resultList);
    } else {
        if (*(lnode1->dataPtr) >= *(lnode2->dataPtr)) {
            insertDataToEndList(resultList, *(lnode1->dataPtr));
            mergeHelper(lnode1->next, lnode2, resultList);
        } else {
            insertDataToEndList(resultList, *(lnode2->dataPtr));
            mergeHelper(lnode1, lnode2->next, resultList);
        }

    }
}