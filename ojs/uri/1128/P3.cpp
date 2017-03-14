#include <bits/stdc++.h>

using namespace std;

#define N 2000

int ret[N];
int o[N];
vector<int> adj[N];
int cont;

int dfs (int i) {
    if (ret[i] != -1) return ret[i];
    o[i] = cont++;
    ret[i] = o[i];

    for (int j = 0; j < adj[i].size(); j++) {
        ret[i] = min(ret[i], dfs(adj[i][j]));   
    }

    return ret[i];
}

int main () {
    int n, m;
    int a, b, q;
    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        cont = 0;
        for (int i = 0; i < n; i++) {
            ret[i] = -1;
            o[i] = -1;
            adj[i].clear();
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &q);
            adj[a-1].push_back(b-1);
            if (q == 2) adj[b-1].push_back(a-1);
        }
        
        dfs(0);

        int i;
        for (i = 1; i < n && o[i] > ret[i]; i++);

        if (i >= n) printf("1\n");
        else printf("0\n");
    }
}
