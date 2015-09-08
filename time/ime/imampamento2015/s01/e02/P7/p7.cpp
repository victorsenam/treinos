#include <bits/stdc++.h>

#define N 100

using namespace std;

vector<int> adj[N];
int v[N], n, m, a, b;
int t, lastvis;

int dfs (int i) {
    if (i == -1) return 0;
    int maxi = -1;

    for (int j = 0; j < adj[i].size(); j++)
        if (maxi == -1 || v[adj[i][j]] > v[maxi])
            maxi = adj[i][j];

    lastvis = i;
    return v[i] + dfs(maxi);
}

int main () {
    scanf("%d", &t);

    for (int c = 1; c <= t; c++) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf("%d", v+i);
            adj[i].clear();
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            adj[a].push_back(b);
        }

        printf("Case %d: %d", c, dfs(0));
        printf(" %d\n", lastvis);
    }
    
}
