#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;
const int M = 2e4+7;

struct dinic {
    int hd[N], nx[M], to[M], ht[M], es;
    ll fl[M], cp[M];
    int n, src, snk;
    int dist[N];
    ll seen[N], visi[N], turn;
    int qi, qf, qu[N];

    inline void init () // antes de montar o grafo
    { es = 2; }

    inline void reset () {
        es = 2;
        memset(hd, 0, sizeof hd);
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
            while (ll val = dfs(src, LLONG_MAX)) {
                res += val;
            }
        }
        return res;
    }
};

dinic flow;
int hd[N], nx[M], to[M], es;
int t;
int n, m;
int visi[N], val[N], turn;

bool dfs (int u, int c) {
    if (visi[u] == turn)
        return (c == val[u]);
    visi[u] = turn;
    val[u] = c;

    bool ok = 1;
    for (int ed = hd[u]; ed; ed = nx[ed])
        ok |= dfs(to[ed], !c);
    return ok;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        turn++;
        scanf("%d %d", &n, &m);
        
        flow.reset();
        flow.src = n;
        flow.snk = flow.src+1;
        flow.n = flow.snk+1;

        for (int i = 0; i < n; i++)
            hd[i] = 0;
        es = 2;
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            nx[es] = hd[a]; to[es] = b; hd[a] = es++;
            nx[es] = hd[b]; to[es] = a; hd[b] = es++;
        }

        for (int i = 0; i < n; i++) {
            if (visi[i] != turn)
                assert(dfs(i,0));
            if (val[i]) {
                flow.connect(i, flow.snk, 1);
            } else {
                flow.connect(flow.src, i, 1);
                for (int ed = hd[i]; ed; ed = nx[ed])
                    flow.connect(i, to[ed], 1);
            }
        }

        printf("%lld\n", n-flow.maxflow());
    }
}
