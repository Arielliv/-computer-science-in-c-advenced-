#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20
#define DISTANCE_CAN_WALK 2
#define DISTANCE_CAN_RIDE 5
#define INDEX_CAN_WALK   0
#define INDEX_CAN_RIDE   1
#define INDEX_NEED_DRIVE 2

typedef struct {
    char name[MAX_NAME_LEN];
    double homeDistance; // in kilometers
} Friend;

typedef Friend *type;

typedef struct listNode {
    type data;
    struct listNode *next;
} LNode;

typedef struct list {
    LNode *head;
    LNode *tail;
} List;

List makeEmptyList();

int isEmpty(List *list);

LNode *createNewNode(type newData, LNode *next);

void insertValueToTail(List *list, type newData);

void insertNodeToTail(List *list, LNode *newNode);

void printList(List *list);

void freeList(List *list);

List *getFriendsByDistance(Friend mtFriends[], int size);

int main() {
    int i;
    Friend myFriends[] = {{"gogo", 3},
                          {"momo", 6},
                          {"yoyo", 1},
                          {"koko", 4},
                          {"toto", 2}};
    List *friendsByDistance;
    friendsByDistance = getFriendsByDistance(myFriends, sizeof(myFriends) / sizeof(myFriends[0]));

    printf("My friends to whom I can walk: ");
    printList(&friendsByDistance[INDEX_CAN_WALK]);
    printf("My friends to whom I can ride: ");
    printList(&friendsByDistance[INDEX_CAN_RIDE]);
    printf("My friends to whom I need to drive: ");
    printList(&friendsByDistance[INDEX_NEED_DRIVE]);

    for (i = 0; i < 3; i++) {
        freeList(&friendsByDistance[i]);
    }
    free(friendsByDistance);

    return 1;
}

List makeEmptyList() {
    List list;
    list.head = list.tail = NULL;
    return list;
}

int isEmpty(List *list) {
    return list->head == NULL;
}

LNode *createNewNode(type newData, LNode *next) {
    LNode *newNode = (LNode *) malloc(sizeof(LNode));
    newNode->data = newData;
    newNode->next = next;
    return newNode;
}

void insertValueToTail(List *list, type newData) {
    LNode *newNode = createNewNode(newData, NULL);
    insertNodeToTail(list, newNode);
}

void insertNodeToTail(List *list, LNode *newNode) {
    if (isEmpty(list)) {
        list->tail = list->head = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void printList(List *list) {
    if (isEmpty(list)) {
        return;
    }

    LNode *curr = list->head;
    while (curr != NULL) {
        printf("%s ", curr->data->name);
        curr = curr->next;
    }
    printf("\n");
}

void freeList(List *list) {
    if (isEmpty(list)) {
        return;
    }

    LNode *curr = list->head;
    LNode *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = list->tail = NULL;
}

List *getFriendsByDistance(Friend mtFriends[], int size) {
    List *friendsByDistance = (List *) malloc(sizeof(List) * 3);
    int i;
    for (i = 0; i < 3; i++) {
        friendsByDistance[i] = makeEmptyList();
    }

    for (i = 0; i < size; i++) {
        if (mtFriends[i].homeDistance <= DISTANCE_CAN_WALK) {
            insertValueToTail(&friendsByDistance[INDEX_CAN_WALK], &mtFriends[i]);
        } else if (mtFriends[i].homeDistance <= DISTANCE_CAN_RIDE) {
            insertValueToTail(&friendsByDistance[INDEX_CAN_RIDE], &mtFriends[i]);
        } else {
            insertValueToTail(&friendsByDistance[INDEX_NEED_DRIVE], &mtFriends[i]);
        }
    }

    return friendsByDistance;
}