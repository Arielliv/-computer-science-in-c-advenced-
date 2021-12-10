//
// 315363366
//

#include "list.h"

void updateDataToPlaceInList(List *lst, int data, int i) {
    bool res;
    ListNode *updatedNode = getListNode(lst, i);
    updatedNode->data = data;
}

bool insertDataToPlaceInList(List *lst, int data, int i) {
    bool res;
    ListNode *newNode;
    newNode = createNewListNode(data, NULL);
    res = insertNodeToPlaceInList(lst, newNode, i);
    if (res == false)
        free(newNode);
    return res;
}

ListNode *getListNode(List *lst, int i) {
    ListNode *curr;
    curr = lst->head;
    while (curr != NULL && i > 0) {
        curr = curr->next;
        i--;
    }
    return curr;
}

bool insertNodeToPlaceInList(List *lst, struct listNode *node, int i) {
    ListNode *after;
    after = getListNode(lst, i - 1);
    if (after == NULL && i > 0) // Illegal location
        return false;
    else if (i == 0) // Start of list
        insertNodeToStartList(lst, node);
    else if (after->next == NULL) // End of list
        insertNodeToEndListNode(lst, node);
    else // “Middle”
    {
        node->next = after->next;
        after->next = node;
    }
    return true;
}

void insertDataToStartList(List *lst, int data) {
    struct listNode *newHead;
    newHead = createNewListNode(data, NULL);
    insertNodeToStartList(lst, newHead);
}

void insertNodeToStartList(List *lst, ListNode *head) {
    if (isEmptyList(lst) == true) {
        head->next = NULL;
        lst->head = lst->tail = head;
    } else {
        head->next = lst->head;
        lst->head = head;
    }
}

int findListNode(List *lst, int data) {
    ListNode *curr = lst->head;
    int index = 0;
    while (curr != NULL) {
        if (curr->data == data) {
            return index;
        }
        index++;
        curr = curr->next;
    }
    return -1;
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

void printList(List lst) {
    ListNode *curr;

    curr = lst.head;

    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }

    printf("\n");
}

void makeEmptyList(List *lst) {
    lst->head = lst->tail = NULL;
}


bool isEmptyList(List *lst) {
    return (lst->head == NULL);
}

ListNode *createNewListNode(int data, ListNode *next) {
    ListNode *res;

    res = (ListNode *) malloc(sizeof(ListNode));
    res->data = data;
    res->next = next;

    return res;
}

void freeList(List *lst) {
    ListNode *curr = lst->head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}