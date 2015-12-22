#include <bits/stdc++.h>

using namespace std;

typedef double num;

const int N = 3007;
const num eps = 1e-9;

int n;
num w, mid;
int uf[N], wf[N], vf[N];
num x[N], y[N];
num cost[N][N];
int res[2];
int turn;

inline num sq (num a)
{ return a*a; }

inline num dist (int i, int j)
{ return sq(x[i]-x[j])+sq(y[i]-y[j]); }

int find (int i) {
    if (vf[i] != turn) {
        uf[i] = i;
        wf[i] = 1;
        vf[i] = turn;
    }
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

bool solve () {
    turn++;
    for (int i = 0; i < n; i++) {
        if (cost[i][n] <= mid)
            join(n, i);
        if (cost[i][n+1] <= mid)
            join(n+1, i);

        for (int j = 0; j < n; j++)
            if (cost[i][j] <= mid)
                join(i, j);
    }

    if (find(n) == find(n+1)) {
        res[0] = res[1] = 0;
        return 1;
    }

    num aux = 4.*mid;
    for (int i = 0; i < n; i++) {
        if (find(i) == find(n+1) && cost[i][n] <= aux) {
            res[0] = n;
            res[1] = i;
            return 1;
        }

        if (find(i) == find(n) && cost[i][n+1] <= aux) {
            res[0] = n+1;
            res[1] = i;
            return 1;
        }

        if (find(i) != find(n))
            continue;
        for (int j = 0; j < n; j++) {
            if (find(j) != find(n+1))
                continue;

            if (cost[i][j] <= aux) {
                res[0] = i;
                res[1] = j;
                return 1;
            }
        }
    }

    return 0;
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cost[i][j] = dist(i, j);
        cost[i][n] = sq(x[i]);
        cost[i][n+1] = sq(w-x[i]);
    }

    num lo = 0;
    num hi = sq(w);

    while (hi - lo > 1e-1) {
        mid = .5*(hi+lo);

        if (solve())
            hi = mid;
        else
            lo = mid;
    }

    mid = hi;
    solve();

    int a = res[0];
    int b = res[1];

    if (a == n)
        printf("%.3f %.3f\n", .5*x[b], y[b]);
    else if (a == n+1)
        printf("%.3f %.3f\n", x[b] + .5*(w-x[b]), y[b]);
    else
        printf("%.3f %.3f\n", .5*(x[a]+x[b]), .5*(y[a]+y[b]));
}
