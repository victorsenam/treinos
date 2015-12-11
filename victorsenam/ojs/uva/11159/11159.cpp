#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int M = 600;

int hd[N], ht[N], to[M], nx[M], us[M], es;
int a[N], b[N];
int n, m;
int tt;
int src, snk;
int qu[N], qi, qf;
int dist[N];
int turn;
int visi[N];

inline void connect (int u, int v) {
    nx[es] = hd[u]; hd[u] = es; to[es] = v; us[es] = 0; es++;
    nx[es] = hd[v]; hd[v] = es; to[es] = u; us[es] = 1; es++;
}

int bfs() {
    qi = qf = 0;
    turn++;
    qu[qf++] = snk;
    dist[snk] = 0;
    visi[snk] = turn;

    while (qi < qf) {
        int u = qu[qi++];
        for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
            if (us[ed^1])
                continue;
            if (visi[to[ed]] == turn && dist[to[ed]] <= dist[u]+1)
                continue;
            visi[to[ed]] = turn;
            dist[to[ed]] = dist[u]+1;
            qu[qf++] = to[ed];
        }
    }

    if (visi[src] != turn)
        return INT_MAX;
    return dist[src];
}

int dfs(int u) {
    if (u == snk)
        return 1;

    for (int & ed = ht[u]; ed != -1; ed = nx[ed]) {
        if (dist[u] != dist[to[ed]]+1 || us[ed])
            continue;
        if (dfs(to[ed])) {
            us[ed] = 1;
            us[ed^1] = 0;
            return 1;
        }
    }

    return 0;
}

int dinic() {
    int res = 0;
    while (bfs() != INT_MAX) {
        for (int i = 0; i <= snk; i++)
            ht[i] = hd[i];
        while (dfs(src))
            res++;
    }
    return res;
}

int main () {
    scanf("%d", &tt);
    for (int ts = 1; ts <= tt; ts++) {
        memset(hd, -1, sizeof hd);

        scanf("%d", &n);
        for (int i =0 ; i < n; i++)
            scanf("%d", a+i);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%d", b+i);

        src = n+m;
        snk = src+1;

        for (int i = 0; i < n; i++)
            connect(src, i);
        for (int i = 0; i < m; i++)
            connect(i+n, snk);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i] != 0 && b[j]%a[i] == 0)
                    connect(i, j+n);

        printf("Case %d: %d\n", ts, dinic());
    }
}
