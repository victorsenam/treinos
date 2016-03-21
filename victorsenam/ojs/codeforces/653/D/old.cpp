// Dinicão da massa
#include <bits/stdc++.h>
using namespace std;

typedef long long int num;
const int N = 70;
const int M = 4007;
const double eps = 1e-13;

struct dinic {
    int hd[N], nx[M], to[M], ht[M], es;
    num fl[M], cp[M];
    int n, src, snk;
    int dist[N], seen[N], visi[N], turn;
    int qi, qf, qu[N];

    inline void init () // antes de montar o grafo
    { es = 2; }

    inline void reset () {
        es = 2;
        memset(hd, 0, sizeof hd);
        memset(fl, 0, sizeof fl);
        memset(seen, 0, sizeof seen);
        memset(visi, 0, sizeof visi);
    }

    inline void connect (int i, int j, num cap) {
        nx[es] = hd[i]; hd[i] = es; to[es] = j; cp[es] = cap; fl[es] = 0; es++; 
        nx[es] = hd[j]; hd[j] = es; to[es] = i; cp[es] = fl[es] = 0; es++;
    }

    bool bfs () {
        turn++;
        qi = qf = 0;

        qu[qf++] = snk;
        dist[snk] = 0;
        seen[snk] = turn;

        while (qi < qf) {
            int u = qu[qi++];

            if (visi[u] == turn)
                continue;
            visi[u] = turn;

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] == fl[ed^1])
                    continue;
                int v = to[ed];

                if (seen[v] == turn && dist[v] <= dist[u]+1)
                    continue;
                seen[v] = turn;
                dist[v] = dist[u]+1;
                qu[qf++] = v;
            }
        }

        return (seen[src] == turn);
    }

    num dfs (int u, num flw) {
        if (u == snk || flw == 0)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (fl[ed] >= cp[ed] || seen[v] != turn || dist[v]+1 != dist[u])
                continue;
            if (num ret = dfs(v, min(flw, cp[ed] - fl[ed]))) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }


    num maxflow () {
        num res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            while (num val = dfs(src, (((num(1)<<(numeric_limits<num>::digits-1))-1)<<1) ))
                res += val;
        }
        return res;
    }
};

int n, m, x;
dinic flow;
int a[N], b[N], c[N];

bool solve (double val) {
    if (val < eps) return 1;
    flow.reset();
    flow.n = n;
    flow.src = 0;
    flow.snk = n-1;
    for (int i = 0; i < m; i++) {
        flow.connect(a[i], b[i], min(x, int(c[i]/val)));
    }

    return (flow.maxflow() >= x);
}

int main () {
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", a+i, b+i, c+i);
        a[i]--; b[i]--;
    }

    double lo = 0.;
    double hi = 1000007.;

    while (hi - lo > eps) {
        double mid = .5*(lo+hi);
        if (solve(mid))
            lo = mid;
        else
            hi = mid;
    }

    printf("%.20f\n", lo*double(x));
}

