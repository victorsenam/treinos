typedef long long int num;

const int N = 203;
const int M = N*N;

// Dinicão da massa
#include <bits/stdc++.h>
using namespace std;

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

    num debug () {
        for (int i = 0; i < n; i++){ 
            printf("%d:", i);
            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d[%lld/%lld]", to[ed], fl[ed], cp[ed]);
            printf("\n");
        }
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

int t;
int n;
dinic flow;

int main () {
    scanf("%d", &t);

    flow.init();
    while (t--) {
        scanf("%d", &n);

        flow.src = 0;
        flow.snk = n-1;
        flow.n = n;

        for (int i = 0; i < n-1; i++) {
            int m, a;
            scanf("%d", &m);

            for (int j = 0; j < m; j++) {
                scanf("%d", &a); a--;
                if (!i || a == n-1)
                    flow.connect(i, a, 1);
                else
                    flow.connect(i, a, LLONG_MAX);
            }

        }

        printf("%lld\n", flow.maxflow());
        if (t) {
            flow.reset();
        }
    }
}
