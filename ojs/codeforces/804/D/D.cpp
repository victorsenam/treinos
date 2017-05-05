#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n, m, q;
ll md[N];
int uf[N], wf[N];
vector<int> adj[N];

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(u);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] < wf[v]) swap(u,v);
    wf[u] += wf[v];
    uf[v] = u;
}

int main () {
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        u--; v--;
    }
}
