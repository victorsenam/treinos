#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

int uf[N], wf[N];
int n, m, k;
int hd[N], nx[N], to[N], es;
int pr[N], siz[N], dpt[N];
int visi[N], turn;
vector<int> rs[N];
int cr;

int find (int u) {
    if (uf[u] == u) return u;
    return uf[u] = find(uf[u]);
}

int join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return 0;
    if (wf[u] < wf[v]) swap(u, v);
    wf[u] += wf[v];
    uf[v] = u;
    return 1;
}

int dfs (int u, int fr) {
    if (visi[u] == turn) return 0;
    visi[u] = turn;
    pr[u] = fr;
    siz[u] = 1;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (to[ed] != fr && !dpt[to[ed]])
            siz[u] += dfs(to[ed], u);
    }

    return siz[u];
}

int go (int u, int fr) {
    bool ok = 0;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (to[ed] != fr && !dpt[to[ed]]) {
            rs[cr].push_back(u);
            go(to[ed], u);
        }
    }
    rs[cr].push_back(u);
}

void build (int u, int depth, int fr) {
    turn++;
    int size = dfs(u, fr);
    int ed = -1;
    while (ed) {
        for (ed = hd[u]; ed && (pr[u] == to[ed] || dpt[to[ed]] || siz[to[ed]] + siz[to[ed]] <= size); ed = nx[ed]);
        if (ed) u = to[ed];
    }
    
    dpt[u] = depth;

    if (size+size <= (n + n + k - 1)/k) {
        go(u, fr);
        cr++;
    } else {
        for (ed = hd[u]; ed; ed = nx[ed])
            if(to[ed] != fr && !dpt[to[ed]])
                build(to[ed], depth+1, u);
    }
}

int main () {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        if (join(a,b)) {
            printf("has %d %d\n", a, b);
            to[es] = b; nx[es] = hd[a]; hd[a] = es++;
            to[es] = a; nx[es] = hd[b]; hd[b] = es++;
        }
    }

    build(0, 1, -1);
    assert(cr == k);

    for (int i = 0; i < k; i++) {
        printf("%d", int(rs[i].size()));
        for (int j : rs[i])
            printf(" %d", j+1);
        printf("\n");
    }
}
