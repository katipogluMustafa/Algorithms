#include<stdio.h>
#include<stdlib.h>          // for just allocation
#include<time.h>            // for random number
#include<unistd.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}NODE;

NODE* listFactory(int);
void printList(NODE*);
NODE* findNode(NODE*, int);
int getRandomInt(int, int);
NODE* insertHead(NODE*, NODE*);
NODE* nodeFactory();
NODE* insertTail(NODE*, NODE*);
void insertAfter(NODE*, NODE*, NODE*);
NODE* deleteNode(NODE*, int);
NODE* destroyList(NODE*);

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

     printList(head);
     head = insertHead(head, nodeFactory());
     printList(head);
     head = insertTail(head, nodeFactory());
     printList(head);
     insertAfter(head, head, nodeFactory());
     printList(head);
     insertAfter(head, head->next->next, listFactory(5));
     printList(head);
     head = deleteNode(head, head->data);
     printList(head);
     head = deleteNode(head, head->next->next->next->data);
     printList(head);
     head = destroyList(head);
     if( head )
         printList(head);
     else
         printf("List does not exists!");

    return 0;
}

/* LinkedList Functions */

/**
 *
 * @return always return NULL, in case in caller forgets the node(argument) still points to the node that has already been freed
 * returns false head
 */
NODE* destroyList(NODE* head){
    NODE* next;
    while(head){
        next = head->next;
        free(head);
        head = next;
    }
}

/**
 * @return Deletes node with the given target data, if not found, does nothing
 */
NODE* deleteNode(NODE* head, int target){
    if( !head )
        return NULL;

    NODE* ptr = head;
    NODE* tmp;

    if( head->data == target){
        NODE* temp = head->next;
        free(head);
        temp->prev = NULL;
        return temp;        // return new head of the list
    }

    while(ptr->next && ptr->next->data != target)
        ptr = ptr->next;


    if( ptr->next == NULL )
        return head;        // Target not found, return the list as it is

    // ptr->next now points to the node that we want to delete
    tmp = ptr->next;
    ptr->next = tmp->next;
    if( tmp->next )
        tmp->next->prev = ptr;
    free(tmp);

    return head;            // return updated list
}


/*
 * Inserts after the node afterMe, the node can be another list or single node
 */
void insertAfter(NODE* head, NODE* afterMe, NODE* newNode){
    if ( !head )
        return;

    while(head && head != afterMe)
        head = head->next;

    if( !head )
        return;

    NODE* ptr = afterMe->next;
    afterMe->next = newNode;
    if( newNode ) {
        newNode->prev = afterMe;
        while ( newNode->next )
            newNode = newNode->next;
        newNode->next = ptr;
        ptr->prev = newNode;
    }
}

NODE* insertTail(NODE* head, NODE* newNode){
    NODE* ptr = head;

    if( head == NULL )
        return insertHead(head, newNode);

    while( ptr->next )
        ptr = ptr->next;

    ptr->next = newNode;

    if(newNode)
        newNode->prev = ptr;

    return head;
}

/**
 * @return updated head of the list
 */
NODE* insertHead(NODE* head, NODE* newHead){
    newHead->next = head;
    newHead->prev = NULL;
    head->prev = newHead;
    return newHead;
}

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
    NODE* tmp;
    --n;
    for(; n>0; n--, ptr = ptr->next ) {
        tmp = nodeFactory();
        ptr->next = tmp;
        tmp->prev = ptr;
    }

    return head;
}

NODE* nodeFactory(){
    int getRandomInt(int, int);

    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = getRandomInt(0, 100);
    node->next = NULL;
    node->prev = NULL;

    return node;
}


int getRandomInt(int rangeMin, int rangeMax){
    double randomNumber = (double)rand() / RAND_MAX;   // get random number between 0 and 1
    return (int)(rangeMin +  ( randomNumber * rangeMax - randomNumber * rangeMin) );
}