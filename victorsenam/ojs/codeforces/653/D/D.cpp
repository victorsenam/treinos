#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 70;
const int M = 2007;
const double eps = 1e-9;
typedef long long ll;

struct dinic {
    int n, m;
    int hd[N], to[M], nx[M], es;
    ll cp[M], fl[M], wg[M];
    int he[N];
    int src, snk;
    int qu[N], qi, qf;
    int dist[N], turn;
    int visi[N];

    void clear (int in)  {
        memset(hd, 0, sizeof hd);
        memset(dist, 0, sizeof dist);
        memset(visi, 0, sizeof visi);
        turn = 0;
        es = 2;
        n = in;
        src = 0;
        snk = n-1;
    }

    void reset (double p) {
        for (int i = 2; i < es; i++) {
            fl[i] = 0;
            cp[i] = (ll) floor(double(wg[i])/p);
        }
    }

    void connect (int i, int j, int w) {
        nx[es] = hd[i]; hd[i] = es; to[es] = j; wg[es] = w; es++;
        nx[es] = hd[j]; hd[j] = es; to[es] = i; wg[es] = 0; es++;
    }

    bool bfs () {
        ++turn;
        qu[qf++] = snk;
        visi[snk] = turn;
        dist[snk] = 0;

        while (qi < qf) {
            int u = qu[qi++];
            
            he[u] = hd[u];
            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] == fl[ed^1] || visi[to[ed]] == turn)
                    continue;
                visi[to[ed]] = turn;
                dist[to[ed]] = dist[u]+1;
                qu[qf++] = to[ed];
            }
        }

        return (visi[src] == turn);
    }

    ll dfs (int u, ll att) {
        if (att <= 0)
            return 0;
        for (int & ed = he[u]; ed; ed = nx[ed]) {
            if ((visi[to[ed]] != turn || dist[to[ed]] + 1 != dist[u])) continue;
            if (ll loc = dfs(to[ed], min(att, cp[ed]-fl[ed]))) {
                fl[ed] += loc;
                fl[ed^1] -= loc;
                return loc;
            }
        }
        return 0;
    }

    ll run () {
        ll res = 0;
        while (bfs())
            while (ll loc = dfs(src, INT_MAX))
                res += loc;
        return res;
    }
};

dinic flow;
int n, m, x;

bool solve (double qt) {
    flow.reset(qt);
    if (flow.run() >= x)
        return 1;
    return 0;
}

int main () {
    scanf("%d %d %d", &n, &m, &x);   
    flow.clear(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;
        flow.connect(a, b, c);
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

    printf("%.20f\n", lo*x);
}
