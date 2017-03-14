#include <bits/stdc++.h>

using namespace std;

const int N = 100;

vector<int> adj[N];
bool vis[N];
bool cor[N];
int n;
int a;

bool dfs(int u, int c) {
    if (vis[u])
        return c == cor[u];

    vis[u] = 1;
    cor[u] = c;

    for (int i = 0; i < adj[u].size(); i++)
        if (!dfs(adj[u][i], !c))
            return 0;
    return 1;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        while (scanf("%d", &a)!=EOF && a) {
            a--;
            adj[i].push_back(a);
            adj[a].push_back(i);
        }
    }

    bool ok = 1;
    for (int i = 0; i < n; i++) {
        if (vis[i])
            continue;
        ok = dfs(i, 0);
    }

    if (!ok)
        printf("-1\n");
    else {
        for (int i = 0; i < n; i++)
            printf("%d", cor[i]);
        printf("\n");
    }
}
