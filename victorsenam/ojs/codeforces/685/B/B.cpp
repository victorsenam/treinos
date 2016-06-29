#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 300010;

int n, q;
vector<int> adj[N];
int p[N];
int ord;
int pre[N], pos[N];
int siz[N];
int res[N];
int maxc[N];

int dfs (int u) {
    siz[u] = 1;
    pre[u] = ord++;
    maxc[u] = n;
    for (int v : adj[u]) {
        siz[u] += dfs(v);
        if (siz[v] > siz[maxc[u]])
            maxc[u] = v;
    }
    pos[u] = ord++;
    return siz[u];
}

void calc (int u) {
    int nx = u;
    if (u && pre[res[p[u]]] >= pre[u] && pos[res[p[u]]] <= pos[u])
        nx = res[p[u]];

    while (nx != -1) {
        res[u] = nx;       
        nx = -1;

        if (siz[maxc[res[u]]] > siz[u]/2)
            nx = maxc[res[u]];
    }

    for (int v : adj[u])
        calc(v);
}

int main () {
    scanf("%d %d", &n, &q);

    for (int  i = 1; i < n; i++) {
        scanf("%d", p+i);
        p[i]--;

        adj[p[i]].push_back(i);
    }

    dfs(0);
    calc(0);

    for (int i = 0; i < q; i++) {
        int val;
        scanf("%d", &val);
        printf("%d\n", res[val-1]+1);
    }
}
