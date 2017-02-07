#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;
const int K = 22;

int n;
ll qt[N][K][2];
int pr[N];
ll a[N];
vector<int> adj[N];
ll res;
int deg[N];

void dfs (int u, int p) {
    pr[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        deg[u]++;
    }
}

int main () {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    for (int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d", &x, &y);
        x--; y--;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(0, 0);
    queue<int> qu;

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < K; k++)
            qt[i][k][!!((1ll<<k)&a[i])]++;
        res += a[i];
        if (!deg[i])
            qu.push(i);
    }
    
    while (!qu.empty()) {
        int u = qu.front();
        int p = pr[u];
        qu.pop();

        if (p == u) continue;

        for (int k = 0; k < K; k++)
            res += (qt[p][k][0]*qt[u][k][1] + qt[p][k][1]*qt[u][k][0]) * (1ll << k);
        for (int k = 0; k < K; k++)
            for (int t = 0; t < 2; t++)
                qt[p][k][t^(!!(a[p]&(1ll<<k)))] += qt[u][k][t];

        deg[p]--;
        if (!deg[p])
            qu.push(p);
    }

    printf("%lld\n", res);
}
