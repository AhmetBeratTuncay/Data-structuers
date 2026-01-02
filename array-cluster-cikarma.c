#include <stdio.h>

#define N 8

void dfs_comp(int G[N][N], int v, int vis[N]) {
    vis[v] = 1;
    printf("%d ", v);
    for (int u = 0; u < N; u++) {
        if (G[v][u] && !vis[u]) dfs_comp(G, u, vis);
    }
}

int main(void) {
  
    int G[N][N] = {0};

   
    G[0][1]=G[1][0]=1;
    G[1][2]=G[2][1]=1;

    
    G[3][4]=G[4][3]=1;

   
    G[5][6]=G[6][5]=1;
    G[6][7]=G[7][6]=1;

    int vis[N] = {0};
    int comp = 0;

    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            comp++;
            printf("Cluster %d: ", comp);
            dfs_comp(G, i, vis);
            printf("\n");
        }
    }
    return 0;
}
