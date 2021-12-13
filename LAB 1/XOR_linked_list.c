#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct node {
    int data;
    struct node* npx;
};
 
struct node* XOR(struct node *x, struct node *y) {
    return (struct node*) ((uintptr_t)(x) ^ (uintptr_t)(y));
}
 
//Insert a node at the begining of the XOR linked list
void insert(struct node **head, int data) {
    
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->npx = XOR(*head, NULL);
    
    if (*head != NULL) {
        struct node* next = XOR((*head)->npx, NULL);
        (*head)->npx = XOR(new_node, next);
    }

    *head = new_node;
}
 
//Print XOR Linked List
void printList(struct node *head) {
    struct node *curr = head;
    struct node *prev = NULL;
    struct node *next;
    
    while (curr != NULL) {
        printf("%d -> ", curr->data);

        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    printf(" NULL\n\n");
}

//delete
void delete(struct node **head) {
    if(*head == NULL) {
        printf("\nList is Empty");
        return;
    }
    struct node *curr = *head;
    struct node *prev = NULL;
    struct node *next;
    while(XOR(curr->npx,prev) != NULL) {
        next = XOR(prev,curr->npx);
        prev = curr;
        curr = next;
    }
    if (prev != NULL) {
        prev->npx = XOR(XOR(prev->npx,curr),NULL);
    }
    else {
        *head = NULL;
    }
    free(curr);
}
 

int main() {
    struct node *head = NULL;
    insert(&head, 40);
    insert(&head, 30);
    insert(&head, 20);
    insert(&head, 10);
    printList(head);
 
    delete(&head);
    delete(&head);
    printList(head);
    return 0;
}
