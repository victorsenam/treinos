#include <bits/stdc++.h>

using namespace std;

const int N = 607;
const int M = N*N/2;

int n, k;
int src, snk;
int ht[N], hd[N], nx[M], to[M], cp[M], fl[M], es;
int dist[N];
int x[N];
int q[N];

bool l_cmp (int i, int j) {
    if ((i|1) == (j|1))
        return i < j;
    return (i&1) < (j&1);
}

inline void connect (int i, int j, int c) {
    nx[es] = hd[i]; hd[i] = es; to[es] = j; cp[es] = c; fl[es] = 0; es++;
    nx[es] = hd[j]; hd[j] = es; to[es] = i; cp[es] = 0; fl[es] = 0; es++;
}

int bfs() {
    int qi, qf;
    qi = qf = 0;

    for (int i = 0; i < n+2; i++)
        dist[i] = INT_MAX;

    q[qf++] = snk;
    dist[snk] = 0;

    while (qi < qf) {
        int u = q[qi++];

        for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
            if (cp[ed^1] <= fl[ed^1])
                continue;

            if (dist[to[ed]] < INT_MAX)
                continue;

            dist[to[ed]] = dist[u]+1;
            q[qf++] = to[ed];
        }
    }

    return dist[src];
}

int dfs(int u) {
    if (u == snk)
        return 1;

    for (int & ed = ht[u]; ed != -1; ed = nx[ed]) {
        if (fl[ed] >= cp[ed] || dist[to[ed]] > dist[u] - 1)
            continue;

        if (dfs(to[ed])) {
            fl[ed]++;
            fl[ed^1]--;
            return 1;
        }
    }
    return 0;
}

int dinic() {
    int res = 0;

    while (bfs() < INT_MAX) {
        for (int i = 0; i < n+2; i++)
            ht[i] = hd[i];

        while (int pls = dfs(src))
            res += pls;
    }

    return res;
}

int main () {
    while (scanf("%d %d", &n, &k) != EOF && n) {
        memset(hd, -1, sizeof hd);

        for (int i = 0; i < n; i++)
            scanf("%d", x+i);

        src = n;
        snk = n+1;
        es = 0;

        sort(x, x+n, l_cmp);

        int fp;
        for (fp = 0; fp < n && !(x[fp]&1); fp++);

        for (int i = 0; i < fp; i++)
            connect(src, i, 1);
        for (int i = fp; i < n; i++)
            connect(i, snk, 1);

        for (int i = 0; i < fp; i++)
            for (int j = fp; j < n; j++)
                if (abs(x[i]-x[j]) <= k)
                    connect(i, j, 1);

        printf("%d\n", dinic());
    }
}
