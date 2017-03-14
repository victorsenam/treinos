#include <bits/stdc++.h>

using namespace std;

#define N 1000

vector<int> g[N];
int o[N], r[N], cnt, n, v;

int dfs(int i, int p) {
    int a;
    o[i] = cnt++;
    r[i] = o[i];
    for (int c = 0; c < g[i].size(); c++) {
        if (g[i][c] == p) continue;
        if (o[g[i][c]] != -1)
            r[i] = min(r[i], o[g[i][c]]);
        else
            r[i] = min(r[i], dfs(g[i][c], i));
    }
    return r[i];
}

int main () {
    while ( scanf("%d %d", &n, &v) != EOF && n && v) {
        for (int i = 0; i < n; i++) {
            o[i] = -1;
            g[i].clear();
        }

        for (int i = 0; i < v; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            g[a-1].push_back(b-1);
            g[b-1].push_back(a-1);
        }

        cnt = 0;
        dfs(0, -1);

        int i;
        for (i = 1; i < n; i++) 
            if (o[i] == r[i]) break;

        if (i < n) printf("N\n");
        else printf("S\n");
    }
}
