#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *prev, *next;
} Node;

Node* new_node(int v){
    Node* n = (Node*)malloc(sizeof(Node));
    n->val=v; n->prev=n->next=NULL;
    return n;
}

void push_front(Node **head, int v){
    Node* n = new_node(v);
    n->next = *head;
    if (*head) (*head)->prev = n;
    *head = n;
}

void insert_after(Node *pos, int v){
    if (!pos) return;
    Node* n = new_node(v);
    n->prev = pos;
    n->next = pos->next;
    if (pos->next) pos->next->prev = n;
    pos->next = n;
}

void delete_value(Node **head, int v){
    Node *cur = *head;
    while (cur && cur->val != v) cur = cur->next;
    if (!cur) return;

    if (cur->prev) cur->prev->next = cur->next;
    else *head = cur->next;

    if (cur->next) cur->next->prev = cur->prev;
    free(cur);
}

void traverse_forward(Node *head){
    for (Node* c=head; c; c=c->next) printf("%d ", c->val);
    printf("\n");
}

void traverse_backward(Node *head){
    if (!head) { printf("\n"); return; }
    Node* tail = head;
    while (tail->next) tail = tail->next;
    for (Node* c=tail; c; c=c->prev) printf("%d ", c->val);
    printf("\n");
}

void free_list(Node *head){
    while (head){ Node* t=head; head=head->next; free(t); }
}

int main(void){
    Node *head = NULL;
    push_front(&head, 3);
    push_front(&head, 2);
    push_front(&head, 1); 

    printf("Forward : "); traverse_forward(head);
    printf("Backward: "); traverse_backward(head);

    insert_after(head->next, 99); 
    printf("After insert: "); traverse_forward(head);

    delete_value(&head, 2); 
    printf("After delete: "); traverse_forward(head);

    free_list(head);
    return 0;
}
