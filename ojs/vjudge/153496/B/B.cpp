// Dinicão da massa
// Generico: O(V^2 E)
// BipMatch: O(V^(1/2) E)
// UnitCap: O(min{V^(2/3),E^(1/2)} E)
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int N = 102;
const int M = 2*N*N;

struct dinic {
    int hd[N], nx[M], to[M], ht[M], es;
    ll fl[M], cp[M];
    int n, src, snk;
    int dist[N], seen[N], visi[N], turn;
    int qi, qf, qu[N];

    inline void init () // antes de montar o grafo
    { es = 2; }

    inline void reset () {
        es = 2;
        memset(hd, 0, sizeof hd);
        memset(seen, 0, sizeof seen);
        memset(visi, 0, sizeof visi);
    }

    inline void connect (int i, int j, ll cap) {
 //       printf("%d-%d [%lld]\n", i, j, cap);
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

    ll dfs (int u, ll flw) {
        if (u == snk || flw == 0)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (fl[ed] >= cp[ed] || seen[v] != turn || dist[v]+1 != dist[u])
                continue;
            if (ll ret = dfs(v, min(flw, cp[ed] - fl[ed]))) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }

    ll debug () {
        for (int i = 0; i < n; i++){ 
            printf("%d:", i);
            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d[%lld/%lld]", to[ed], fl[ed], cp[ed]);
            printf("\n");
        }
    }

    ll maxflow () {
        ll res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            while (ll val = dfs(src, LLONG_MAX))
                res += val;
        }
        return res;
    }
};

dinic flw;
int ts, n;
int a[N];

int main () {
    scanf("%d", &ts);

    while (ts--) {
        int res = 0;
        scanf("%d", &n);

        flw.reset();
        flw.n = 2*n+2;
        flw.src = flw.n - 2;
        flw.snk = flw.n - 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    flw.connect(i, n+j, 1);

        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if (a[i] > n-1) {
                res += a[i] - (n-1);
                a[i] = n-1;
            }

            flw.connect(flw.src, i, a[i]);
            flw.connect(n+i, flw.snk, n-1-a[i]);
        }

        printf("%d\n", res + n*(n-1)/2 - flw.maxflow());
    }
}

