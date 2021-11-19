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

bool isCoordinateExistInList(List *lst, int x, int y);

bool isExistInYList(YList *lst, int y);

YListNode *findExistInYList(YList *lst, int y);

int removeCoordinate(List *coord_list, int x, int y);

void printYList(YList *lst, int x);

void printList(List *lst);

void removeYNode(YList *lst, YListNode *exitingYNode);

void removeXNode(List *lst, XListNode *exitingXNode);

void main() {

    List coordList;

    int x, y;

    int res;

    coordList = getCoordList();

// get the (x,y) to remove

    scanf("%d%d", &x, &y);


    res = removeCoordinate(&coordList, x, y);

    if (res == 1)

        printf("The point (%d,%d) didn't appear\n", x, y);

    else if (res == 2)

        printf("The point (%d,%d) has another occurrence\n", x, y);

    else if (res == 3)

        printf("The point (%d,%d) was the only point with this x\n", x, y);

    else

        printf("Other\n");

    printf("Updated list: ");

    printList(&coordList);

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

YListNode *findExistInYList(YList *lst, int y) {
    if (isEmptyYList(lst)) {
        return NULL;
    }
    YListNode *curr = lst->head;
    while (curr != NULL) {
        if (curr->yCoordinate == y) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

bool isExistInYList(YList *lst, int y) {
    bool res = false;
    if (isEmptyYList(lst)) {
        return false;
    }
    YListNode *curr = lst->head;
    while (curr != NULL) {
        if (curr->yCoordinate == y) {
            res = true;
        }
        curr = curr->next;
    }
    return res;
}

bool isCoordinateExistInList(List *lst, int x, int y) {
    bool res = false;
    if (isEmptyList(lst)) {
        return false;
    }
    XListNode *curr = lst->head;
    while (curr != NULL) {
        if (curr->xCoordinate == x) {
            res = isExistInYList(&(curr->son), y);
        }
        curr = curr->next;
    }
    return res;
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

int removeCoordinate(List *coord_list, int x, int y) {
    YListNode *exitingYNode;
    XListNode *exitingXNode = isExistInList(coord_list, x);
    if (exitingXNode != NULL) {
        if (exitingXNode->son.head->yCoordinate == y && exitingXNode->son.head == exitingXNode->son.tail) {
            removeXNode(coord_list, exitingXNode);
            return 3;
        } else {
            exitingYNode = findExistInYList(&exitingXNode->son, y);
            if (exitingYNode != NULL) {
                removeYNode(&exitingXNode->son, exitingYNode);
            } else {
                return 1;
            }

        }
        exitingYNode = findExistInYList(&exitingXNode->son, y);
        if (exitingYNode == NULL) {
            return 0;
        } else {
            return 2;
        }
    } else {
        return 1;
    }
    return 0;
}

void removeXNode(List *lst, XListNode *exitingXNode) {
    if (lst->head == exitingXNode) {
        lst->head = exitingXNode->next;
        lst->head->prev = NULL;
    } else if (lst->tail == exitingXNode) {
        lst->tail = exitingXNode->prev;
        lst->tail->next = NULL;
    } else {
        exitingXNode->prev->next = exitingXNode->next;
        exitingXNode->next->prev = exitingXNode->prev->prev;
    }
    free(exitingXNode);
}

void removeYNode(YList *lst, YListNode *exitingYNode) {
    YListNode *curr, *prev;
    curr = lst->head;
    if (curr == exitingYNode) {
        lst->head = curr->next;
        return;
    }
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        if (curr == exitingYNode) {
            if (lst->tail == curr) {
                lst->tail = prev;
                prev->next = NULL;
            } else {
                prev->next = prev->next->next;
            }
        }
    }
    free(exitingYNode);
}

void printYList(YList *lst, int x) {
    YListNode *curr;

    curr = lst->head;

    while (curr != NULL) {

        printf("(%d %d), ", x, curr->yCoordinate);

        curr = curr->next;
    }
}

void printList(List *lst) {
    XListNode *curr;

    curr = lst->head;

    while (curr != NULL) {

        printYList(&(curr->son), curr->xCoordinate);

        curr = curr->next;
    }

    printf("\n");
}