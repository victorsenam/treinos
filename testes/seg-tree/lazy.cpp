// spoj.com/problems/HORRIBLE
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int tc, n, q;

struct seg {
    struct val {
        ll v;

        val () {}
        val (ll a) : v(a) {}
        val operator + (const val & ot) const
        { return val(v + ot.v); }
    };

    val v[4*N], lz[4*N];
    int l[4*N], r[4*N];
    int lo, hi;

    seg () {}

    void update (int u) {
        v[u] = v[u] + (lz[u].v)*ll(r[u]-l[u]);
        val aux = lz[u];
        lz[u] = 0;
        if (l[u] + 1 == r[u]) return;
        lz[2*u] = lz[2*u] + aux;
        lz[2*u+1] = lz[2*u+1] + aux;
    }

    void build (int u, int lo, int hi) {
        l[u] = lo;
        r[u] = hi;
        v[u] = lz[u] = 0;
        if (lo + 1 == hi) return;
        build(2*u, lo, (lo+hi)/2);
        build(2*u+1, (lo+hi)/2, hi);
    }

    void sum (int u, ll x) {
        update(u);
        if (lo >= r[u] || hi <= l[u]) return;
        if (lo <= l[u] && r[u] <= hi) {
            lz[u] = lz[u] + x;
            update(u);
            return;
        }
        sum(2*u, x);
        sum(2*u+1, x);
        v[u] = v[2*u] + v[2*u+1];
    }

    void sum (int l, int r, ll x) {
        lo = l; hi = r;
        sum(1, x);
    }

    val query (int u) {
        update(u);
        if (lo >= r[u] || hi <= l[u]) return 0;
        if (lo <= l[u] && r[u] <= hi) return v[u];
        return (query(2*u) + query(2*u+1));
    }

    val query (int l, int r) {
        lo = l; hi = r;
        return query(1);
    }

};

seg tree;

int main () {
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {
        scanf("%d %d", &n, &q);

        tree.build(1, 0, n);

        int c, lo, hi, x;
        for (int i = 0; i < q; i++) {
            scanf("%d %d %d", &c, &lo, &hi);
            if (c == 0) {
                scanf("%d", &x);
                tree.sum(lo-1, hi, x);
            } else {
                printf("%lld\n", tree.query(lo-1, hi).v);
            }
        }
    }
}
