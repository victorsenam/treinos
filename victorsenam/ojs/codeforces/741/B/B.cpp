#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int n, m, w;
int uf[2*N];
int wf[2*N];
int p[2*N];

int v[2*N], c[2*N];
int av[N], ac[N];

ll memo[2*N][N][2];
int visi[2*N][N][2];

int a, b;

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] < wf[v]) swap(u, v);
    wf[u] += wf[v];
    uf[v] = u;
}

bool cmp_t (int i, int j) {
    if (find(i) != find(j)) return find(i) < find(j);
    return i < j;
}

ll pd (int _i, int w, bool st) {
    if (w < 0) return -1e10;
    if (_i == n) return 0;
    int i = p[_i];
    if (st && _i && find(i) != find(p[_i-1])) st = 0;
    
    ll & me = memo[_i][w][st];
    if (visi[_i][w][st]) return me;
    visi[_i][w][st] = 1;

    me = pd(_i+1, w, st);

    if (!st) {
        me = max(pd(_i+1, w-c[i], 1) + v[i], me);
    }

    return me;
}

int main () {
    scanf("%d %d %d", &n, &m, &w);

    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
        uf[i] = i;
        wf[i] = 1;
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        join(a, b);
    }

    for (int i = 0; i < n; i++) {
        int u = find(i);
        av[u] += v[i];
        ac[u] += c[i];
    }

    for (int i = 0; i < n; i++) {
        p[i] = i;
        int u = find(i);
        if (u != i) continue;
        uf[n] = u;
        v[n] = av[u];
        c[n] = ac[u];
        n++;
    }

    sort(p, p+n, cmp_t);
    
    printf("%lld\n", pd(0, w, 0));
}
