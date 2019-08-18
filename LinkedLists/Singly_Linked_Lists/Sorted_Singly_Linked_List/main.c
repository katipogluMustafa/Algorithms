#include<stdio.h>
#include<stdlib.h>          // for just allocation
#include<time.h>            // for random number
#include<unistd.h>

typedef struct Node{
    int data;
    struct Node* next;
}NODE;


void printList(NODE*);
NODE* sortedListFactory(int);
int getRandomInt(int, int);
NODE* nodeFactory();
NODE* insertNode(NODE* head, NODE* newNode);


NODE* insertHead(NODE*, NODE*);

int main() {
    time_t t;
    srand((unsigned)time(&t) * getppid() * (unsigned)&t );

    NODE* head = sortedListFactory(8);

    printList(head);

    return 0;
}

void printList(NODE* head){
    while(head){
        printf("%d\n", head->data);
        head = head->next;
    }
}

NODE* insertNode(NODE* head, NODE* newNode){
    if(head == NULL)
        return newNode;

    NODE* oldHead = head;
    NODE* prev = NULL;
    int target = newNode->data;

    if( target < head->data)
        return insertHead(head, newNode);

    while( head && head->data <= target) {
        prev = head;
        head = head->next;
    }

    prev->next = newNode;

return oldHead;
}

/**
 * @return the updated head
 */
NODE* insertHead(NODE* head, NODE* newHead) {
    if(!newHead)
        return head;        // if newHead is null, return the list as it is

    newHead->next = head;

    return newHead;
}

/* List Factory */



NODE* sortedListFactory(int n){
    NODE* head = nodeFactory();
    int i;
    for(i = 0; i < n; i++)
        head = insertNode(head, nodeFactory());

    return head;
}

NODE* nodeFactory(){
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = getRandomInt(0, 100);
    node->next = NULL;

    return node;
}


int getRandomInt(int rangeMin, int rangeMax){
    double randomNumber = (double)rand() / RAND_MAX;   // get random number between 0 and 1
    return (int)(rangeMin +  ( randomNumber * rangeMax - randomNumber * rangeMin) );
}