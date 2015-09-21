#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int v[2][N];
vector<int> adj[2][N];
int n;
int a, b;
int sol[N];
int ss;

void dfs (int u, int t) {
    if (v[t][u])
        return;

    v[t][u] = 1;

    for (int i = 0; i < adj[t][u].size(); i++)
        dfs(adj[t][u][i], t);
}

int main () {
    scanf("%d", &n);

    while (scanf("%d %d", &a, &b) > 0) {
        a--;
        b--;
        adj[0][a].push_back(b);
        adj[1][b].push_back(a);
    }
    scanf("BLOOD");

    while (scanf("%d", &a) != EOF) {
        a--;
        dfs(a, 0);
        dfs(a, 1);
    }

    for (int i = 0; i < n; i++) {
        if (v[0][i] || v[1][i])
            continue;

        sol[ss++] = i;
    }

    if (!ss)
        printf("0");
    
    for (int i = 0; i < ss; i++) {
        if (i)
            printf(" ");
        printf("%d", sol[i]+1);
    }
    printf("\n");
}
