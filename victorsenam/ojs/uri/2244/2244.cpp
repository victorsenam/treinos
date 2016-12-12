#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
const double eps = 1e-7;

ll a[2][N], b[2][N];
int p[N];
int vs[N];
int n;
int anc;
double r[N][2];

struct cvx {
    double st[N];
    int id[N], ss;
    int ty;

    double bests (int i, int j) {
        if (j == -1) return 0.;
        i = id[i]; j = id[j];

        if (a[ty][i] == a[ty][j]) {
            if (b[ty][i] >= b[ty][j]) return 0.;
            assert(false);
            return 1./0.;
        }

        if (a[ty][i] < a[ty][j]) {
            assert(false);
            return 1./0.;
        }

        return double(b[ty][j] - b[ty][i])/double(a[ty][i] - a[ty][j]);
    }

    void add (int i) {
        id[ss] = i;
        st[ss] = 0.;

        while (ss && (st[ss] = bests(ss, ss-1)) <= st[ss-1] + eps) {
            id[ss-1] = id[ss];
            ss--;
        }
        ss++;
    }
};

cvx trk[2];

bool cmp_t (int i, int j) {
    if (a[anc][i] != a[anc][j]) return a[anc][i] < a[anc][j];
    return b[anc][i] < b[anc][j];
}

int main () {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%lld %lld", &b[j][i], &a[j][i]);
            if (j) {
                b[j][i] = -b[j][i];
                a[j][i] = -a[j][i];
            }
        }
        p[i] = i;
        r[i][0] = 0.;
        r[i][1] = 1./0.;
        vs[i] = 0;
    }

    for (anc = 0; anc < 2; anc++) {
        sort(p, p+n, cmp_t);
        trk[anc].ty = anc;
        trk[anc].ss = 0;
        
        for (int i = 0; i < n; i++) {
            if (i && a[anc][p[i]] == a[anc][p[i-1]] && b[anc][p[i]] == b[anc][p[i-1]]) {
                vs[i]--;
                vs[i-1]--;
            }

            trk[anc].add(p[i]);
        }

        for (int i = 0; i < trk[anc].ss; i++) {
            int id = trk[anc].id[i];
            vs[id]++;
            r[id][0] = max(r[id][0], trk[anc].st[i]);
            if (i + 1 < trk[anc].ss)
                r[id][1] = min(r[id][1], trk[anc].st[i+1]);
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (vs[i] < 2) continue;
        if (r[i][0] + eps < r[i][1]) res++;
    }

    printf("%d\n", res);
}
