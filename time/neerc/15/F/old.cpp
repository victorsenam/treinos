#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 3007;

num n, m;
num cost[N][N];
num res[2][N];
int visi[2][N];
int turn;
num x[N], y[N];
int qu[N], qt[N], qi, qf;

inline num sq (num a)
{ return a*a; }

inline num dist (int a, int b) {
    return sq(x[a]-x[b]) + sq(y[a]-y[b]);
}

bool solve (num w) {
    turn++;
    qi = qf = 0;
    for (int i = 0; i < n; i++) {
        if (sq(x[i]) <= w) {
            visi[0][i] = turn;
            qu[qf] = i; qt[qf++] = 0;
        } else if (sq(x[i]) <= num(4)*w) {
            visi[1][i] = turn;
            res[0][i] = -1;
            res[1][i] = i;
            qu[qf] = i; qt[qf++] = 1;
        }
    }

    while (qi < qf) {
        int u = qu[qi];
        bool t = qt[qi++];

        if (sq(m-x[u]) <= w) {
            res[0][n] = res[0][u];
            res[1][n] = res[1][u];
            printf("de %d(%lld,%lld) ao fim\n", u, x[u], y[u], m, sqrt(w));
            return 1;
        } else if (!t && sq(m-x[u]) <= num(4)*w) {
            res[0][n] = u;
            res[1][n] = n;
            printf("de %d(%lld,%lld) ao fim (com pedra)\n", u, x[u], y[u], m, 2*sqrt(w));
            return 1;
        }

        for (int i = 0; i < n; i++) {
            if (visi[0][i] == turn)
                continue;
            if (dist(u, i) <= w) {
                qu[qf] = i; qt[qf++] = t;
                res[0][i] = res[0][u];
                res[1][i] = res[1][u];
                visi[t][i] = turn;
                printf("de %d(%lld,%lld) a %d(%lld,%lld) [%lld]\n", u, x[u], y[u], i, x[i], y[i], dist(u, i));
            } else if (!t && visi[1][i] != turn && dist(u, i) <= num(4)*w) {
                qu[qf] = i; qt[qf++] = t;
                res[0][i] = u;
                res[1][i] = i;
                visi[1][i] = turn;
                printf("de %d(%lld,%lld) a %d(%lld,%lld) [%lld] (com pedra)\n", u, x[u], y[u], i, x[i], y[i], dist(u, i));
            }
        }
    }
    return 0;
}

int main() {
    scanf("%lld %lld", &m, &n);

    num lo, hi;
    lo = 0;
    hi = sq(m);
    
    for (int i = 0; i < n; i++)
        scanf("%lld %lld", x+i, y+i);

    while (lo < hi) {
        num mid = lo + ((hi-lo)>>1);
        bool ok;
        printf("== %lld %lld %lld\n", lo, mid, hi);
        if (ok = solve(mid))
            hi = mid;
        else
            lo = mid+1;

    }
    printf("%lld\n", lo);
    solve(lo);

    int a = res[0][n];
    int b = res[1][n];
    printf("!! %d %d\n", a, b);
    if (a == -1)
        printf("%.3f %.3f\n", double(x[b])/2., double(y[b]));
    else if (b == n)
        printf("%.3f %.3f\n", double(x[a]) + double(m-x[a])/2., double(y[a]));
    else
        printf("%.3f %.3f\n", double(x[a]) + double(x[b]-x[a])/2., double(y[a]) + double(y[b]-y[a])/2.);
}
