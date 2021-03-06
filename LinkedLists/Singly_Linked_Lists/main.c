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
NODE* findNodeBefore(NODE* head, int target);
NODE* insertHead(NODE* head, NODE* node);
NODE* nodeFactory();
NODE* insertTail(NODE* head, NODE* node);
void insertAfter(NODE* head, NODE* afterMe, NODE* node);
NODE* deleteNode(NODE* head, int target);
NODE* destroyList(NODE* head);

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
        return head;

    NODE* ptr = head;
    NODE* before = NULL;

    if( head->data == target){
        NODE* temp = head->next;
        free(head);
        return temp;        // return new head of the list
    }

    while(ptr && ptr->data != target){
        before = ptr;
        ptr = ptr->next;
    }

    if( !ptr )
        return head;        // Target not found, return the list as it is

    // ptr now points to the node that we want to delete
    before->next = ptr->next;
    free(ptr);

    return head;            // return updated list
}


/*
 * Inserts after the node afterMe, the node can be another list or single node
 */
void insertAfter(NODE* head, NODE* afterMe, NODE* node){
    if ( !head )
        return;

    NODE* before = NULL;

    while(head && head != afterMe)
        head = head->next;

    if( !head )
        return;

    NODE* ptr = afterMe->next;
    afterMe->next = node;
    if( node ) {
        while ( node->next )
            node = node->next;
        node->next = ptr;
    }
}

NODE* insertTail(NODE* head, NODE* node){
    NODE* before = NULL;
    NODE* ptr = head;

    if( head == NULL )
        return insertHead(head,node);

    while( ptr ) {
        before = ptr;
        ptr = ptr->next;
    }

    before->next = node;
    return head;
}

/**
 * @return updated head of the list
 */
NODE* insertHead(NODE* head, NODE* node){
    node->next = head;
    head = node;
    return head;
}

/**
 *
 * @return Finds the node with the target data and returns node before it
 */
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
