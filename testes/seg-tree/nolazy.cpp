// spoj.com/problems/RPLN
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

int inp[N];
int tc, n, q;

struct seg {
    struct val {
        int v;

        val () {}
        val (int a) : v(a) {}
        val operator + (const val & ot) const
        { return val(min(v, ot.v)); }
    };

    val v[4*N];
    int l[4*N], r[4*N];
    int lo, hi;

    seg () {}

    void build (int u, int lo, int hi) {
        l[u] = lo;
        r[u] = hi;
        if (lo + 1 == hi) {
            v[u] = val(inp[lo]);
            return;
        }
        build(2*u, lo, (lo+hi)/2);
        build(2*u+1, (lo+hi)/2, hi);
        v[u] = v[2*u] + v[2*u+1];
    }

    val query (int l, int r) {
        lo = l; hi = r;
        return query(1);
    }

    val query (int u) {
        if (lo <= l[u] && r[u] <= hi) return v[u];
        if (lo >= r[u] || hi <= l[u]) return INT_MAX;
        return (query(2*u) + query(2*u+1));
    }
};

seg tree;

int main () {
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {
        scanf("%d %d", &n, &q);

        printf("Scenario #%d:\n", t);

        for (int i = 0; i < n; i++)
            scanf("%d", inp+i);
        tree.build(1, 0, n);

        int lo, hi;
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &lo, &hi);
            printf("%d\n", tree.query(lo-1, hi).v);
        }
    }
}
