#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+6;

struct num {
    ll a, b;

    num (ll x, ll y) {
        if (y < 0) {
            x = -x;
            y = -y;
        }
        a = x;
        b = y;
    }
    num () {}

    bool operator < (const num & ot) const {
        if (ot.b == 0 && b == 0)
            return a < ot.a;
        return a*ot.b < ot.a*b;
    }
    operator double () const
    { return double(a)/double(b); }
};

struct line {
    ll a, b;
    int idx;

    line (ll x, ll y, int i) : a(x), b(y), idx(i) {}
    line () {}

    bool operator == (const line & ot) const
    { return (a == ot.a) && (b == ot.b); }

    ll get (ll x) 
    { return a*x + b; }

    num inter (line & x) {
        if (a == x.a) {
            if (b <= x.b)
                return num(-1, 0);
            else
                return num(1, 0);
        }
        return num(x.b-b, a-x.a);
    }

    ll comp (line & x, line & y)
    { return inter(x) < inter(y); }

    bool ang_comp (const num & ot) const
    { return a < ot.a; }
};

struct cvx {
    line st[N];
    int ss;

    num getst (int i) {
        if (i == 0) return num(-1, 0);
        if (i == ss) return num(1, 0);
        return st[i].inter(st[i-1]);
    }

    int add (line & ot) {
        st[ss] = ot;
        while (ss > 1 && !(getst(ss-1) < getst(ss)))
            swap(st[ss], st[--ss]);
        st[ss++] = ot;        
        return ss-1;
    }

    void print () {
        debug("%d", st[0].idx);
        for (int i = 1; i < ss; i++)
            debug(" [%f] %d", double(getst(i)), i);
        debug("\n");
    }
};

int n;
line v[2][N];
int ps[2][N];
int p[N];
int cmp_a;
cvx trk[2];

bool cmp_t (int i, int j) {
    if (v[cmp_a][i].a != v[cmp_a][j].a)
        return v[cmp_a][i].a > v[cmp_a][j].a;
    if (v[cmp_a][i].b != v[cmp_a][j].b)
        return v[cmp_a][i].b < v[cmp_a][j].b;
    return v[cmp_a][i].idx < v[cmp_a][j].idx;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        for (int k = 0; k < 2; k++) {
            v[k][i].idx = i;
            scanf("%lld %lld", &v[k][i].b, &v[k][i].a);
            if (k) {
                v[k][i].b = -v[k][i].b;
                v[k][i].a = -v[k][i].a;
            }
        }
    }

    for (int k = 0; k < 2; k++) {
        cmp_a = k;
        sort(p, p+n, cmp_t);

        for (int i = 0; i < n; i++) {
            debug("== %lld %lld\n", v[k][p[i]].a, v[k][p[i]].b);
            ps[k][p[i]] = trk[k].add(v[k][p[i]]);
            if (i && v[k][p[i]] == v[k][p[i-1]])
                ps[k][p[i]] = -1;
        }
        trk[k].print();
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        bool ok = 1;
        num mi = num(0,1);
        num ma = num(1,0);

        for (int k = 0; k < 2; k++) {
            debug("%d ", ps[k][i]);
            if (ps[k][i] == -1) ok = 0;
            else if (trk[k].st[ps[k][i]].idx != i) ok = 0;
            else {
                num a = trk[k].getst(ps[k][i]);
                num b = trk[k].getst(ps[k][i]+1);
                debug("(%f %f) ", double(a), double(b));

                if (mi < a) mi = a;
                if (b < ma) ma = b;
            }
        }

        if (ok && mi < ma) {
            debug("[%d] : (%f %f)", i, double(mi), double(ma));
            res++;
        }
        debug("\n");
    }
    printf("%d\n", res);
}
