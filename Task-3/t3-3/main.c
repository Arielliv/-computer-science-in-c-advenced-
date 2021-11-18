// 315363366
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct YlistNode {
    int yCoordinate;
    struct YlistNode *next;
} YListNode;

typedef struct Ylist {
    YListNode *head;
    YListNode *tail;
} YList;

typedef struct XlistNode {
    int xCoordinate;
    struct XlistNode *next;
    struct XlistNode *prev;
    struct Ylist son;
} XListNode;

typedef struct list {
    XListNode *head;
    XListNode *tail;
} List;

List getCoordList();

void freeList(List *list);

void freeYList(YList *yList);

void makeEmptyList(List *lst);

void makeEmptyYList(YList *lst);

XListNode *createNewXListNode(int x, int y, XListNode *next, XListNode *prev);

void insertDataToEndList(List *lst, int x, int y);

void insertNodeToEndListNode(List *lst, XListNode *newTail);

bool isEmptyList(List *lst);

void insertDataToEndYList(YList *lst, int y);

void insertNodeToEndListYNode(YList *lst, YListNode *newTail);

YListNode *createNewYListNode(int y, YListNode *next);

bool isEmptyYList(YList *lst);

XListNode *isExistInList(List *lst, int x);

int countYCoordinates(YList *yList);

unsigned int getXOccurrences(List coord_list, int x);

void main() {

    List coordList;
    int x;
    unsigned int res;

    coordList = getCoordList();

// get the (x,*) to look for
    scanf("%d", &x);

    res = getXOccurrences(coordList, x);

    printf("The point (%d,*) appears %u times\n", x, res);

    freeList(&coordList);
}

List getCoordList() {
    List res;
    int size, num1, num2, i;

    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);

    printf("Please enter the numbers  by pers:\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &num1);
        scanf("%d", &num2);
        insertDataToEndList(&res, num1, num2);
    }

    return res;

}

void makeEmptyList(List *lst) {
    lst->head = NULL;
    lst->tail = NULL;
}

void makeEmptyYList(YList *lst) {
    lst->head = NULL;
    lst->tail = NULL;
}

void insertDataToEndList(List *lst, int x, int y) {
    XListNode *head = isExistInList(lst, x);
    if (head == NULL) {
        head = createNewXListNode(x, y, NULL, NULL);
        insertNodeToEndListNode(lst, head);
    } else {
        insertDataToEndYList(&(head->son), y);
    }

}

void insertNodeToEndListNode(List *lst, XListNode *newTail) {
    if (isEmptyList(lst)) {
        lst->head = lst->tail = newTail;
    } else {
        newTail->prev = lst->tail;
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

XListNode *createNewXListNode(int x, int y, XListNode *next, XListNode *prev) {
    XListNode *res;
    res = (XListNode *) malloc(sizeof(XListNode));
    res->xCoordinate = x;
    res->next = next;
    res->prev = prev;
    makeEmptyYList(&(res->son));
    insertDataToEndYList(&(res->son), y);
    return res;
}


void insertDataToEndYList(YList *lst, int y) {
    YListNode *newTail;

    newTail = createNewYListNode(y, NULL);
    insertNodeToEndListYNode(lst, newTail);
}

void insertNodeToEndListYNode(YList *lst, YListNode *newTail) {

    if (isEmptyYList(lst)) {
        lst->head = lst->tail = newTail;
    } else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

YListNode *createNewYListNode(int y, YListNode *next) {
    YListNode *res;

    res = (YListNode *) malloc(sizeof(YListNode));
    res->yCoordinate = y;
    res->next = next;

    return res;
}

bool isEmptyYList(YList *lst) {
    if (lst->head == NULL)
        return true;
    else
        return false;
}

bool isEmptyList(List *lst) {
    if (lst->head == NULL)
        return true;
    else
        return false;
}

XListNode *isExistInList(List *lst, int x) {
    if (isEmptyList(lst)) {
        return NULL;
    }
    XListNode *curr = lst->head;
    while (curr != NULL) {
        if (curr->xCoordinate == x) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int countYCoordinates(YList *yList) {
    int counter = 0;
    YListNode *curr = yList->head;
    while (curr != NULL) {
        counter++;
        curr = curr->next;
    }
    return counter;
}

unsigned int getXOccurrences(List coord_list, int x) {
    int counter = 0;
    XListNode *curr = coord_list.head;
    while (curr != NULL) {
        if (curr->xCoordinate == x) {
            counter += countYCoordinates(&(curr->son));
        }
        curr = curr->next;
    }
    return counter;
}

void freeYList(YList *yList) {
    YListNode *curr = yList->head, *saver;
    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}

void freeList(List *list) {
    XListNode *curr = list->head, *saver;
    while (curr != NULL) {
        saver = curr->next;
        freeYList(&(curr->son));
        free(curr);
        curr = saver;
    }
}