#include <bits/stdc++.h>

using namespace std;

typedef double num;

const int N = 3007;
const num eps = 1e-9;

int n;
num w, mid;
int uf[N], wf[N];
num x[N], y[N];

inline num sq (num a)
{ return a*a; }

inline num dist (int i, int j)
{ return sq(x[i]-x[j])+sq(y[i]-y[j]); }

int find (int i) {
    if (uf[i] == i)
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

pair<bool, int> solve () {
    for (int i = 0; i <= n+1; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (sq(x[i]) - mid <= eps)
            join(n, i);
        if (sq(w-x[i]) - mid <= eps)
            join(n+1, i);

        for (int j = 0; j < n; j++)
            if (dist(i, j) - mid <= eps)
                join(i, j);
    }

    if (find(n) == find(n+1))
        return make_pair(true, 0);

    for (int i = 0; i < n; i++) {
        if (find(i) == find(n+1) && sq(x[i]) - 4.*mid <= eps)
            return make_pair(true, (n)*(n+2) + i);

        if (find(i) == find(n) && sq(w-x[i]) - 4.*mid <= eps)
            return make_pair(true, (n+1)*(n+2) + i);

        if (find(i) != find(n))
            continue;
        for (int j = 0; j < n; j++) {
            if (find(j) != find(n+1))
                continue;

            if (dist(i, j) - 4.*mid <= eps)
                return make_pair(true, i*(n+2) + j);
        }
    }

    return make_pair(false, 0);
}

int main () {
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    scanf("%lf %d", &w, &n);

    if (n == 0) {
        printf("%.3f %.3f\n", .5*w, 7.);
        return 0;
    }

    for (int i = 0; i < n; i++)
        scanf("%lf %lf", x+i, y+i);

    num lo = 0;
    num hi = sq(w);

    while (hi - lo > 1e-2) {
        mid = .5*(hi+lo);

        pair<bool, int> res = solve();
        if (res.first)
            hi = mid;
        else
            lo = mid;
    }

    mid = hi;
    pair<bool, int> res = solve();

    int a = res.second/(n+2);
    int b = res.second%(n+2);

    if (a == n)
        printf("%.3f %.3f\n", .5*x[b], y[b]);
    else if (a == n+1)
        printf("%.3f %.3f\n", x[b] + .5*(w-x[b]), y[b]);
    else
        printf("%.3f %.3f\n", .5*(x[a]+x[b]), .5*(y[a]+y[b]));
}
