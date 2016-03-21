#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 400007;

struct seg {
    int n;
    int l[N], r[N];
    ll val[N], lz_val[N];
    int ql, qr;
    
    void build (int v, int ql, int qr) {
        l[v] = ql; r[v] = qr;
        val[v] = lz_val[v] = 0;
        if (ql + 1 == qr) return;
        build(2*v, ql, (ql+qr+1)/2);
        build(2*v+1, (ql+qr+1)/2, qr);
    }

    void unlazy (int v) {
        val[v] += lz_val[v]*ll(r[v]-l[v]);
        ll x = lz_val[v];
        lz_val[v] = 0;
        if (l[v] + 1 == r[v]) return;

        lz_val[2*v] += x;
        lz_val[2*v+1] += x;
    }

    void sum (int v, ll x) {
        unlazy(v);
        if (ql >= r[v] || qr <= l[v]) return;
        if (ql <= l[v] && qr >= r[v]) {
            lz_val[v] += x;
            unlazy(v);
            return;
        }

        sum(2*v, x);
        sum(2*v+1, x);
        val[v] = val[2*v] + val[2*v+1];
    }

    void sum (int l, int r, ll x) {
        ql = l; qr = r;
        sum(1, x);
    }

    ll get (int v) {
        unlazy(v);
        if (ql >= r[v] || qr <= l[v]) return 0ll;
        if (ql <= l[v] && qr >= r[v]) return val[v];

        return get(2*v) + get(2*v+1);
    }

    ll get (int l, int r) {
        ql = l; qr = r;
        return get(1);
    }
};

set<int> s;
set<int>::iterator it, aux;
int cor[N];
int n, m;
int ty, l, r, x;
seg tree;

void define_cor (int i) {
    it = s.upper_bound(i);
    --it;

    cor[i] = cor[*it];
    s.insert(i);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        s.insert(i);
        cor[i] = i+1;
    }
    s.insert(n);
    tree.build(1, 0, n);

    while (m--) {
        scanf("%d", &ty);
        if (ty == 1) {
            scanf("%d %d %d", &l, &r, &x);
            l--;
            define_cor(l);
            define_cor(r);
            int a = l;
            
            it = s.lower_bound(l);

            while (l < r) {
                aux = it++;
                tree.sum(l, *it, abs(x-cor[l]));
                cor[l] = x;
                l = *it;
                s.erase(aux);
            };
            s.insert(a);
        } else {
            scanf("%d %d", &l, &r);
            l--;
            printf("%I64d\n", tree.get(l, r));
        }
        DEBUG("--------\n");
    }
}
