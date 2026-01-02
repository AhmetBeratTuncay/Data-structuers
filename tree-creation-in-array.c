#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    int val;
    struct TNode *left, *right;
} TNode;

TNode* new_tnode(int v){
    TNode* n=(TNode*)malloc(sizeof(TNode));
    n->val=v; n->left=n->right=NULL;
    return n;
}


TNode* build_tree(const int *a, int n, int i){
    if (i >= n) return NULL;
    if (a[i] == -1) return NULL;
    TNode *root = new_tnode(a[i]);
    root->left  = build_tree(a, n, 2*i + 1);
    root->right = build_tree(a, n, 2*i + 2);
    return root;
}

void preorder(TNode* r){
    if(!r) return;
    printf("%d ", r->val);
    preorder(r->left);
    preorder(r->right);
}
void inorder(TNode* r){
    if(!r) return;
    inorder(r->left);
    printf("%d ", r->val);
    inorder(r->right);
}
void postorder(TNode* r){
    if(!r) return;
    postorder(r->left);
    postorder(r->right);
    printf("%d ", r->val);
}

void free_tree(TNode* r){
    if(!r) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main(void){
    
    int a[] = {1,2,3,4,-1,-1,7};
    int n = (int)(sizeof(a)/sizeof(a[0]));

    TNode *root = build_tree(a, n, 0);

    printf("Preorder : "); preorder(root); printf("\n");
    printf("Inorder  : "); inorder(root); printf("\n");
    printf("Postorder: "); postorder(root); printf("\n");

    free_tree(root);
    return 0;
}
