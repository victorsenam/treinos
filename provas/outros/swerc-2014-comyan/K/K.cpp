#include <bits/stdc++.h>

using namespace std;

const int N = 28;

int t;
int n;
char a, b;
int adj[N][N];
int visi[N];
int par[N];
int deep[N];

int dfs (int u, int p, int d) {
    if (visi[u] == 2)
        return -1;
    par[u] = p;
    if (visi[u] == 1)
        return u;
    visi[u] = 1;
    deep[u] = d;

    for (int i = 0; i < 26; i++) {
        int w = dfs(i, u, d+1);
        if (w != -1)
            return w;
    }
    return -1;
}

int main ( ) {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                adj[i][j] = 1;

        for (int i = 0; i < n; i++) {
            scanf(" %c%c", &a, &b);
            a -= 'a'; b -= 'a';
            adj[a][b] = 0;
        }

        int cyc = -1;
        for (int i = 0; cyc == -1 && i < n; i++)
            cyc = dfs(i, i, 0);

        if (cyc >= 0) {
            int aux = cyc;
            for (int i = 0; i < 20; i++)
            }
        } else {
        }
    }
}
