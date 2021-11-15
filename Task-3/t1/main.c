#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct list_node {
    char *dataPtr;
    struct list_node *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

typedef struct student {
    List first;
    int grade;
} Student;

Student unScramble(List lst);

void insertDataToEndList(List *lst, char data);

void makeEmptyList(List *lst);

void freeList(List *lst);

ListNode *createNewListNode(char data, ListNode *next);

bool isEmptyList(List *lst);

void insertNodeToEndListNode(List *lst, ListNode *newTail);

void removeNodeFromList(List *lst, ListNode *nodeTobeRemoved);

void removeNodeFromEndList(List *lst);

void removeNodeFromStartList(List *lst);

void removeNodeFromMiddleList(List *lst, ListNode *nodeTobeRemoved);

void printList(List lst);

void printStudent(Student *student);

bool isDigit(char c);

void main() {
    List lst;
    Student student;
    char ch;

    makeEmptyList(&lst);

    printf("Please enter the scrambled student:\n");

    ch = (char) getchar();
    while (ch != '\n') {
        insertDataToEndList(&lst, ch);
        ch = (char) getchar();
    }

    student = unScramble(lst);

    printStudent(&student);

    freeList(&student.first);
}

Student unScramble(List lst) {
    ListNode *curr, *saver;
    char numStr[3];
    int numCounter = 0;
    curr = lst.head;
    Student fixedStudent;
    List studentLst;
    makeEmptyList(&studentLst);

    while (curr != NULL) {
        if (isDigit(*(curr->dataPtr))) {
            saver = curr;
            numStr[numCounter] = *(curr->dataPtr);
            numCounter++;
            removeNodeFromList(&lst, curr);
            curr = saver->next;

        } else {
            saver = curr;
            curr = curr->next;
            insertNodeToEndListNode(&studentLst, saver);
        }
    }
    fixedStudent.first = studentLst;
    fixedStudent.grade = atoi(numStr);
    return fixedStudent;
}

bool isDigit(char c) {
    bool result = false;
    if (c >= '0' && c <= '9') {
        result = true;
    }
    return result;
}

void removeNodeFromList(List *lst, ListNode *nodeTobeRemoved) {
    if (lst->tail == nodeTobeRemoved) {
        removeNodeFromEndList(lst);
    } else if (lst->head == nodeTobeRemoved) {
        removeNodeFromStartList(lst);
    } else {
        removeNodeFromMiddleList(lst, nodeTobeRemoved);
    }
}

void removeNodeFromEndList(List *lst) {
    ListNode *curr;
    curr = lst->head;

    while (curr->next != lst->tail) {
        curr = curr->next;
    }

    lst->tail = curr;
    curr->next = NULL;
}

void removeNodeFromStartList(List *lst) {
    if (lst->head == NULL) {
        return;
    } else {
        lst->head = lst->head->next;
    }
}

void removeNodeFromMiddleList(List *lst, ListNode *nodeTobeRemoved) {
    ListNode *curr;
    curr = lst->head;

    while (curr->next != nodeTobeRemoved) {
        curr = curr->next;
    }

    curr->next = nodeTobeRemoved->next;
}

void insertDataToEndList(List *lst, char data) {
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
        printf("%c", *(curr->dataPtr));
        curr = curr->next;
    }

    printf("\n");
}

void printStudent(Student *student) {
    printf("First name: ");
    printList(student->first);
    printf("Grade: ");
    printf("%d", student->grade);
    printf("\n");
}


void makeEmptyList(List *lst) {
    lst->head = lst->tail = NULL;
}

bool isEmptyList(List *lst) {
    return (lst->head == NULL);
}

ListNode *createNewListNode(char data, ListNode *next) {
    ListNode *res;

    res = (ListNode *) malloc(sizeof(ListNode));
    res->dataPtr = (char *) malloc(sizeof(char));
    *res->dataPtr = data;
    res->next = next;

    return res;
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