#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node* new_node(int v){
    Node* n = (Node*)malloc(sizeof(Node));
    n->val=v; n->next=NULL;
    return n;
}


void insert_after(Node *pos, int v){
    if (!pos) return;
    Node *n = new_node(v);
    n->next = pos->next;
    pos->next = n;
}


void push_front(Node **tail, int v){
    Node *n = new_node(v);
    if (!*tail){
        n->next = n;
        *tail = n;
        return;
    }
    n->next = (*tail)->next;
    (*tail)->next = n;
}

void delete_value(Node **tail, int v){
    if (!*tail) return;
    Node *prev = *tail;
    Node *cur = (*tail)->next; 
    do {
        if (cur->val == v) {
            if (cur == prev) { 
                free(cur);
                *tail = NULL;
                return;
            }
            prev->next = cur->next;
            if (cur == *tail) *tail = prev; 
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    } while (cur != (*tail)->next);
}

void traverse(Node *tail){
    if (!tail) { printf("(empty)\n"); return; }
    Node *head = tail->next;
    Node *cur = head;
    do {
        printf("%d ", cur->val);
        cur = cur->next;
    } while (cur != head);
    printf("\n");
}

void free_list(Node **tail){
    if (!*tail) return;
    Node *head = (*tail)->next;
    Node *cur = head;
    do {
        Node *t = cur;
        cur = cur->next;
        free(t);
    } while (cur != head);
    *tail = NULL;
}

int main(void){
    Node *tail = NULL;

    push_front(&tail, 3);
    push_front(&tail, 2);
    push_front(&tail, 1); 

    printf("List: "); traverse(tail);

    
    Node *head = tail->next;
    insert_after(head, 99); 
    printf("After insert: "); traverse(tail);

    delete_value(&tail, 3); 
    printf("After delete: "); traverse(tail);

    free_list(&tail);
    return 0;
}
