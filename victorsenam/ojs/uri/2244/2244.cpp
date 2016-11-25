#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef double cood;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+6;
const cood eps = 1e-9;

struct line {
    cood a, b;
    int id;

    line() {}

    double bests (line & ot) {
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

    int insert (line & x) {
        v[n] = x;

        while (n > 1 && v[n].bests(v[n-1]) < v[n-1].bests(v[n-2]))
            swap(v[n], v[--n]);

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
        return v[i][k].a < v[j][k].a;
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
        }
        rs[i][0] = -1./0.;
        rs[i][1] = 1./0.;
    }

    for (k = 0; k < 2; k++) {
        sort(p, p+n, cmp_t);

        for (int _i = 0; _i < n; _i++) {
            int i = p[_i];
            trk[k].insert(v[i][k]);
            
            if (_i && v[p[_i]] == v[p[_i-1]]) {
                vs[p[_i]]--;
                vs[p[_i-1]]--;
            }
        }
        
        vs[trk[k].v[0].id]++;
        for (int j = 1; j < trk[k].n; j++) {
            vs[trk[k].v[j-1].id]++;
            rs[trk[k].v[j-1].id][1] = min(rs[trk[k].v[j-1].id][1], trk[k].v[j].bests(trk[k].v[j-1]));
            rs[trk[k].v[j].id][0] = max(rs[trk[k].v[j].id][0], trk[k].v[j].bests(trk[k].v[j-1]));
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (vs[i] != 2) continue;
        if (rs[i][0] + eps < rs[i][1])
            res++;
    }
    printf("%d\n", res);
}
