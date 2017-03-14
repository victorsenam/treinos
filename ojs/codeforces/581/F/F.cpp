#include <bits/stdc++.h>

using namespace std;

const int N = 5006;

int memo[N][2];
int ord[N];
int pr;
int n;
vector<int> adj[N];

void dfs(int u, int p) {
    ord[pr++] = u;

    for (int i = 0; i < adj[u].size(); i++)
        if (adj[u][i] != p)
            dfs(adj[u][i], i);
}

int main () {
    scanf("%d", &n);
    pr = 0;

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        a--;
        b--;
        adj[a].push_back(b);
        bdj[b].push_back(a);
    }

    for (int i = 0; i < n; i++)
        dfs(i,i);


}
