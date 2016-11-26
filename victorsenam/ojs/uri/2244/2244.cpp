#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef double cood;

//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {} {fprintf(stdout, __VA_ARGS__); }
#else
#define debug(...) {}
#endif

const int N = 1e5+6;
const cood eps = 1e-9;

struct line {
    cood a, b;
    int id;

    line() {}

    bool operator == (line & ot) {
        return (a == ot.a) && (b == ot.b);
    }

    cood bests (line & ot) {
        if (a == ot.a) {
            if (b >= ot.b)
                return -1./0.;
            assert(false);
        }
        return (b-ot.b)/(ot.a-a);
    }
};

struct cvx {
    line v[N];
    int n;

    cvx() {
        n = 0;
    }

    cood getst (int i) {
        if (i == 0) return -1./0.;
        return v[i].bests(v[i-1]);
    }

    int insert (line & x) {
        v[n] = x;

        while (n && getst(n) <= getst(n-1)) {
            swap(v[n], v[n-1]);
            n--;
        }

        return n++;
    }
};

int n;
int k;
line v[N][2];
cood rs[N][2];
int vs[N];
cvx trk[2];
int p[N];

bool cmp_t (int i, int j) {
    if (v[i][k].a != v[j][k].a)
        return v[i][k].a > v[j][k].a;
    if (v[i][k].b != v[j][k].b)
        return v[i][k].b < v[j][k].b;
    return i < j;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        for (k = 0; k < 2; k++) {
            scanf("%lf %lf", &v[i][k].b, &v[i][k].a);
            if (k) {
                v[i][k].a = -v[i][k].a;
                v[i][k].b = -v[i][k].b;
            }
            v[i][k].id = i;
        }
        rs[i][0] = 0.;
        rs[i][1] = 1./0.;
        vs[i] = 0;
    }

    for (k = 0; k < 2; k++) {
        debug("== %d ==\n", k);
        sort(p, p+n, cmp_t);

        for (int _i = 0; _i < n; _i++) {
            int i = p[_i];
            trk[k].insert(v[i][k]);
            
            if (_i && v[p[_i]][k] == v[p[_i-1]][k]) {
                vs[p[_i]]--;
                vs[p[_i-1]]--;
            }
        }
        
        for (int j = 0; j < trk[k].n; j++) {
            debug("%d[%f] ", trk[k].v[j].id, trk[k].getst(j));
            if (j)
                rs[trk[k].v[j-1].id][1] = min(rs[trk[k].v[j-1].id][1], trk[k].getst(j));
            rs[trk[k].v[j].id][0] = max(rs[trk[k].v[j].id][0], trk[k].getst(j));
            vs[trk[k].v[j].id]++;
        }
        debug("\n");
    }

    debug("== = ==\n");
    int res = 0;
    for (int i = 0; i < n; i++) {
        debug("%d(%d) [%f,%f]\n", i, vs[i], rs[i][0], rs[i][1]);
        if (vs[i] != 2) continue;
        if (rs[i][0] + eps <= rs[i][1]) {
            res++;
        }
    }

    printf("%d\n", res);
}
