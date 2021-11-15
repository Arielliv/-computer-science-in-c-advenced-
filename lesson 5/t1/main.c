#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct letterEncrypt {
    char letter;
    int count;
} LetterEncrypt;

typedef struct listNode {
    LetterEncrypt *sequencePtr;
    struct listNode *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

void printList(List lst);

List makeEmptyList();

int isEmptyList(List lst);

void insertDataToEndListNode(List *lst, LetterEncrypt sequence);

ListNode *createNewListNode(LetterEncrypt sequence, ListNode *next);

LetterEncrypt createSequence(char letter, int count);

void insertNodeToEndListNode(List *lst, ListNode *tail);

void freeList(List lst);

List encode(char *str);

int encodedStrcmp(List str1, List str2);

int main() {
    printf("Hello, World!\n");
    return 0;
}


void printList(List lst) {
    ListNode *curr;

    curr = lst.head;

    while (curr != NULL) {
        printf("%c %d\n", curr->sequencePtr->letter, curr->sequencePtr->count);
        curr = curr->next;
    }

    printf("\n");
}

List makeEmptyList() {
    List res;

    res.head = res.tail = NULL;

    return res;
}

int isEmptyList(List lst) {
    return (lst.head == NULL);
}

ListNode *createNewListNode(LetterEncrypt sequence, ListNode *next) {
    ListNode *res;

    res = (ListNode *) malloc(sizeof(ListNode));
    res->sequencePtr = (LetterEncrypt *) malloc(sizeof(LetterEncrypt));
    *res->sequencePtr = sequence;
    res->next = next;

    return res;
}

void insertDataToEndListNode(List *lst, LetterEncrypt sequence) {
    ListNode *newTail;

    newTail = createNewListNode(sequence, NULL);
    insertNodeToEndListNode(lst, newTail);
}

void insertNodeToEndListNode(List *lst, ListNode *newTail) {
    if (isEmptyList(*lst)) {
        lst->head = lst->tail = newTail;
    } else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void freeList(List lst) {
    ListNode *curr = lst.head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        free(curr->sequencePtr);
        free(curr);
        curr = saver;
    }
}

LetterEncrypt createSequence(char letter, int count) {
    LetterEncrypt sequence;

    sequence.letter = letter;
    sequence.count = count;

    return sequence;
}


List encode(char *str) {
    List list = makeEmptyList();
    bool isEmptyStr = strcmp(str, "");
    int i = 0;
    int counter = 1;
    char currLetter;
    LetterEncrypt newLetterEncrypt;

    if (isEmptyStr) {
        return list;
    } else {
        while (str[i] != '\0') {
            currLetter = str[i];
            if (currLetter == str[i + 1]) {
                counter++;
            } else {
                newLetterEncrypt = createSequence(currLetter, counter);
                insertDataToEndListNode(&list, newLetterEncrypt);
                counter = 1;
            }
            i++;
        }
    }
    return list;
}

int encodedStrcmp(List str1, List str2) {
    ListNode *curr1;
    ListNode *curr2;

    if (str1.head == NULL && str2.head == NULL) {
        return 0;
    }
    if (str1.head == NULL && str2.head != NULL) {
        return 1;
    }

    if (str1.head != NULL && str2.head == NULL) {
        return -1;
    }

    curr1 = str1.head;
    curr2 = str2.head;
    while (curr1 != NULL || curr2 != NULL) {
        if (curr1->sequencePtr->letter == curr2->sequencePtr->letter) {
            if (curr1->sequencePtr->count == curr2->sequencePtr->count) {
                curr1 = curr1->next;
                curr2 = curr2->next;
            } else if (curr1->sequencePtr->count > curr2->sequencePtr->count) {
//                curr2 = curr2->next;
            } else {
                curr1 = curr1->next;
            }
        } else {
            if (curr1->sequencePtr->letter > curr2->sequencePtr->letter) {
                return -1;
            } else {
                return 1;
            }
        }
    }

    if (curr1 == NULL && curr2 == NULL) {
        return 0;
    }
    if (curr1 == NULL && curr2 != NULL) {
        return 1;
    }

    if (curr1 != NULL && curr2 == NULL) {
        return -1;
    }

}