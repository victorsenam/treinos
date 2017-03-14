#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 200007;
const ll MOD = 1e9+7ll;

struct seg {
    ll v[4*N], lz[4*N];
    int l[4*N], r[4*N];
    int lo, hi;

    void build (int u, int lo, int hi) {
        l[u] = lo; r[u] = hi; v[u] = 0; lz[u] = 1ll;
        if (lo + 1 == hi)
            return;
        build(2*u, lo, (lo+hi)/2);
        build(2*u+1, (lo+hi)/2, hi);
    }

    void refresh (int u) {
        v[u] = (v[u]*lz[u])%MOD;
        if (l[u] + 1 != r[u]) {
            lz[2*u] = (lz[2*u]*lz[u])%MOD;
            lz[2*u+1] = (lz[2*u+1]*lz[u])%MOD;
        }
        lz[u] = 1;
    }

    void add (int u, int p, ll x) {
        refresh(u);
        if (l[u] + 1 == r[u] && l[u] == p) {
            v[u] = (v[u]+x)%MOD;
            assert(v[u] == x);
            return;
        }
        if (l[u] > p || r[u] <= p) return;
        add(2*u, p, x);
        add(2*u+1, p, x);
        v[u] = (v[2*u] + v[2*u+1])%MOD;
    }

    void times (int l, int r, ll x) {
        lo = l; hi = r;
        times(1, x);
    }

    void times (int u, ll x) {
        refresh(u);
        if (l[u] >= lo && r[u] <= hi) {
            lz[u] = (lz[u]*x)%MOD;
            assert(lz[u] == x);
            refresh(u);
            return;
        }
        if (l[u] >= hi || r[u] <= lo) return;
        times(2*u, x);
        times(2*u+1, x);
        v[u] = (v[2*u] + v[2*u+1])%MOD;
    }

    ll query (int l, int r) {
        lo = l; hi = r;
        return query(1);
    }

    ll query (int u) {
        refresh(u);
        if (l[u] >= lo && r[u] <= hi) return v[u];
        if (l[u] >= hi || r[u] <= lo) return 0ll;
        return (query(2*u) + query(2*u+1))%MOD;
    }
};

struct qr {
    int t, u;
};

ll fexp (ll x, ll e) {
    ll r = 1ll;
    while (e) {
        if (e%2) r = (r*x)%MOD;
        x = (x*x)%MOD;
        e /= 2;
    }
    return r;
}

ll inv (ll x) {
    return fexp(x, MOD-2);
}

int hd[N], to[N], nx[N], es;
int pr[N];
ll sz[N];
int ord[N][2], os;
qr q[N];
ll v[N];
int n, qrs;

void dfs (int u) {
    ord[u][0] = os++;
    for (int ed = hd[u]; ed; ed = nx[ed])
        dfs(to[ed]);
    ord[u][1] = os;
}

seg tree;

int main () {
    scanf("%lld %d", &v[0], &qrs);
    
    n = 1;

    es = 2;
    for (int i = 0; i < qrs; i++) {
        scanf("%d %d", &q[i].t, &q[i].u);
        q[i].u--;
        if (q[i].t == 1) {
            scanf("%lld", &v[n]);
            pr[n] = q[i].u;           
            nx[es] = hd[q[i].u]; to[es] = n++; hd[q[i].u] = es++;
        }
    }

    dfs(0);

    tree.build(1, 0, n);
    sz[0] = 1ll;
    tree.add(1, ord[0][0], v[0]);
    int qt = 1;

    for (int i = 0; i < qrs; i++) {
        int u = q[i].u;
        if (q[i].t == 1) {
            sz[qt] = 1ll;
            tree.times(ord[u][0], ord[u][1], ((sz[u]+1ll)*inv(sz[u]))%MOD);
            sz[u]++;
            ll s = tree.query(ord[u][0], ord[u][0]+1);
            s = (s*inv(v[u]))%MOD;
            s = (s*v[qt])%MOD;
            tree.add(1, ord[qt][0], s);
            qt++;
        } else {
            ll s = 1ll;
            s = (inv(tree.query(ord[u][0], ord[u][0]+1))*v[u])%MOD;
            s = (s*sz[u])%MOD;
            s = (s*tree.query(ord[u][0], ord[u][1]))%MOD;
            printf("%lld\n", s);
        }
    }
}
