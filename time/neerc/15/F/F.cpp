#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 3007;
const double eps = 1e-9;

num n;
double m;
double w;
double x[N], y[N];
int res[2];
int uf[N], wf[N];

inline double sq (double a)
{ return a*a; }

inline double dist (int a, int b) 
{ return sq(x[a]-x[b]) + sq(y[a]-y[b]); }

int find (int i) {
    if (i == uf[i])
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] < wf[j])
        swap(i, j);
    uf[j] = i;
    wf[i] += wf[j];
}

bool solve () {
    for (int i = 0; i <= n+1; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    res[0] = res[1] = 0;
    for (int i = 0; i < n; i++) {
        if (sq(x[i]) - w <= eps)
            join(i, n+1);
        if (sq(m - x[i]) - w <= eps)
            join(i, n);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (dist(i, j) - w <= eps)
                join(i, j);

    if (find(n) == find(n+1))
        return 1;

    for (int i = 0; i < n; i++) {
        if (sq(x[i]) - w <= eps) {
            res[0] = -1;
            res[1] = i;
            return 1;
        }
        if (sq(m - x[i]) - w <= eps) {
            res[0] = i;
            res[1] = n;
        }
    }

    for (int i = 0; i < n; i++) {
        if (find(i) != find(n))
            continue;
        for (int j = 0; j < n; j++) {
            if (find(j) != find(n+1))
                continue;

            if (dist(i, j) - 4.*w <= eps) {
                res[0] = i;
                res[1] = j;
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    scanf("%lf %I64d", &m, &n);

    if (n == 0) {
        printf("%.20f %.20f\n", double(m)/2., 7.);
        return 0;
    }

    double lo, hi;
    lo = 0;
    hi = sq(m);
    
    for (int i = 0; i < n; i++)
        scanf("%lf %lf", x+i, y+i);

    while (hi - lo > eps) {
        w = (hi+lo)/2.;
        if (solve())
            hi = w;
        else
            lo = w;
    }
    w = lo;
    solve();

    int a = res[0];
    int b = res[1];
    if (a == -1)
        printf("%.20f %.20f\n", (x[b])/2., (y[b]));
    else if (b == n)
        printf("%.20f %.20f\n", (m+x[a])/2., (y[a]));
    else
        printf("%.20f %.20f\n", (x[b]+x[a])/2., (y[b]+y[a])/2.);
}
