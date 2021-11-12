#include <stdio.h>

typedef struct letterEncrypt{
    char letter;
    int count;
}LetterEncrypt;

typedef struct listNode{
    LetterEncrypt* sequencePtr;
    struct listNode* next;
}ListNode;

typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;


int main() {
    printf("Hello, World!\n");
    return 0;
}
