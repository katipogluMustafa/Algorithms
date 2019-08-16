#include<stdio.h>
#include<stdlib.h>          // for just allocation
#include<time.h>            // for random number
#include<unistd.h>
#include<limits.h>

typedef struct Node{
    int data;
    struct Node* next;
}NODE;

NODE* listFactory(int);
void printList(NODE* head);
NODE* findNode(NODE* head, int data);
int getRandomInt(int rangeMin, int rangeMax);

NODE* findNodeBefore(NODE* head, int target){
    if( head == NULL )
        return NULL;
    else if( head->data == target )
        return NULL;

    NODE* before = NULL;
    while(head && head->data != target){
        before = head;
        head = head->next;
    }

    if( head )
        return before;

    return NULL;
}

int main() {
    time_t t;
    srand((unsigned)time(&t) * getppid() * (unsigned)&t );

    NODE* head = listFactory(10);
    printList(head);

    NODE* theNode = findNode(head, 1);
    if( theNode )
        printf("\n Yeap, Found it at adress %p, with the searched data %d\n", theNode,theNode->data);
    else
        printf("Couldn't found, Sorry...\n");

    NODE* theNodeBefore = findNodeBefore(head, 5);
    if( theNodeBefore != NULL )
        printf("\nFound the node before it at address %p, with the next node having the data %d", theNodeBefore, theNodeBefore->next->data);
    else if( head->data == 5)
        printf("\nFound the data but since it corresponds the head of the list, there is no node before it, Sorry...\n");
    else
        printf("Couldn't found it, Sorry...\n");

    return 0;
}

/* LinkedList Functions */

void printList(NODE* head) {
    printf("------ Print List Starts ------\n");
    while (head) {
        printf("%d\n", head->data);
        head = head->next;
    }
    printf("------ Print List Ends ------\n");
}

NODE* findNode(NODE* head, int data){
    while(head && head->data != data)
        head = head->next;

    if(head)
        return head;

    return NULL;
}


/* List Factory */

NODE* listFactory(int n){
    NODE* nodeFactory();

    NODE* head = nodeFactory();
    NODE* ptr = head;
    --n;
    for(; n>0; n--, ptr = ptr->next )
        ptr->next = nodeFactory();

    return head;
}

NODE* nodeFactory(){
    int getRandomInt(int, int);

    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = getRandomInt(0, 100);
    node->next = NULL;

    return node;
}


int getRandomInt(int rangeMin, int rangeMax){
    double randomNumber = (double)rand() / RAND_MAX;   // get random number between 0 and 1
    return (int)(rangeMin +  ( randomNumber * rangeMax - randomNumber * rangeMin) );
}