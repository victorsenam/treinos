#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num;
const num inf = LLONG_MAX;

const int N = 3e3+7;
const int M = 3e5+7;

struct dinic {
    int hd[N], nx[M], to[M], ht[M], es;
    num fl[M], cp[M];
    int n, src, snk;
    int ds[N], sn[N], tr;
    int qi, qf, qu[M];

    void init ()
    { es = 2; memset(hd, 0, sizeof hd); }

    void connect (int i, int j, num cap) {
        to[es] = j; nx[es] = hd[i]; cp[es] = cap; fl[es] = 0; hd[i] = es++;
        to[es] = i; nx[es] = hd[j]; cp[es] = fl[es] = 0; hd[j] = es++;
    }

    bool bfs () {
        tr += 2;
        qi = qf = 0;

        qu[qf++] = snk;
        ds[snk] = 0;

        while (qi < qf) {
            int u = qu[qi++];

            if (sn[u] > tr)
                continue;
            sn[u] = tr+1;

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] == fl[ed^1])
                    continue;

                int v = to[ed];
                if (sn[v] >= tr && ds[v] <= ds[u] + 1)
                    continue;
                sn[v] = tr;
                ds[v] = ds[u] + 1;
                qu[qf++] = v;
            }
        }
        
        return (sn[src] > tr);
    }

    num dfs (int u, num flw) {
        if (u == snk || !flw)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (cp[ed] == fl[ed] || sn[v] < tr || ds[v] + 1 != ds[u])
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
            while (ll val = dfs(src, inf)) {
                res += val;
            }
        }
        return res;
    }
};

int n, m;
dinic flw;

int solve (int x) {
    memset(flw.fl, 0, sizeof flw.fl);
    for (int ed = flw.hd[0]; ed; ed = flw.nx[ed]) {
        flw.cp[ed] = x;
    }

    int r = flw.maxflow();
    return r;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    flw.n = n+m+2;
    flw.src = 0;
    flw.snk = n+m+1;
    flw.init();

    for (int i = 1; i <= n; i++)
        flw.connect(flw.src,i,0);
    for (int i = 1; i <= m; i++)
        flw.connect(i+n,flw.snk,1);

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            flw.connect(i,a+n,1);
        }
    }
    
    int lo = 0, hi = M;
    while (lo < hi) {
        int md = (lo+hi+1)/2;

        if (solve(md) == md*n)
            lo = md;
        else
            hi = md-1;
    }

    if (lo)
        cout << "YES " << lo << endl;
    else
        cout << "NO " << solve(1) << endl;
}

