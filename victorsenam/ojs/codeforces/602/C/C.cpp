#include<bits/stdc++.h>

using namespace std;

const int N = 407;

int qi, qf, qa[N*N], qb[N*N];
int adj[N][N];
int n, m;
int dist[N][N];
bool visi[N][N];

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj[a][b] = adj[b][a] = 1;
    }
    
    dist[0][0] = 0;
    visi[0][0] = 1;
    qa[qf] = 0; qb[qf++] = 0;

    while (qi < qf && !visi[n-1][n-1]) {
        int a = qa[qi];
        int b = qb[qi++];

        if (a && a == b)
            continue;

        for (int i = 0; i < n; i++) {
            if (a == n-1)
                i = n-1;
            else if (adj[a][i] == 0 || a == i)
                continue;

            for (int j = 0; j < n; j++) {
                if (b == n-1)
                    j = n-1;
                else if (adj[b][j] || b == j)
                    continue;

                if (visi[i][j])
                    continue;
                visi[i][j] = 1;
                dist[i][j] = dist[a][b] + 1;
                qa[qf] = i; qb[qf++] = j;
            }
        }
    }
    
    if (!visi[n-1][n-1])
        printf("-1\n");
    else
        printf("%d\n", dist[n-1][n-1]);
}
