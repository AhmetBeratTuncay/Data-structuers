#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int v;
    struct Node *next;
} Node;

Node* push(Node *head, int v){
    Node *n = (Node*)malloc(sizeof(Node));
    n->v = v;
    n->next = head;
    return n;
}

void add_edge(Node **adj, int u, int v, int undirected){
    adj[u] = push(adj[u], v);
    if (undirected)
        adj[v] = push(adj[v], u);
}


void dfs_rec(Node **adj, int *vis, int x){
    vis[x] = 1;
    printf("%d ", x);

    for (Node *p = adj[x]; p; p = p->next){
        if (!vis[p->v])
            dfs_rec(adj, vis, p->v);
    }
}

void dfs(Node **adj, int n, int start){
    int *vis = (int*)calloc(n, sizeof(int));
    dfs_rec(adj, vis, start);
    printf("\n");
    free(vis);
}

void bfs(Node **adj, int n, int start){
    int *vis = (int*)calloc(n, sizeof(int));
    int *q = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;

    vis[start] = 1;
    q[back++] = start;

    while (front < back){
        int x = q[front++];
        printf("%d ", x);

        for (Node *p = adj[x]; p; p = p->next){
            if (!vis[p->v]){
                vis[p->v] = 1;
                q[back++] = p->v;
            }
        }
    }
    printf("\n");
    free(vis);
    free(q);
}

int main(){
    int n = 6;
    Node **adj = (Node**)calloc(n, sizeof(Node*));

    add_edge(adj, 0, 1, 1);
    add_edge(adj, 0, 2, 1);
    add_edge(adj, 1, 3, 1);
    add_edge(adj, 2, 4, 1);
    add_edge(adj, 4, 5, 1);

    printf("DFS: ");
    dfs(adj, n, 0);

    printf("BFS: ");
    bfs(adj, n, 0);

    return 0;
}
