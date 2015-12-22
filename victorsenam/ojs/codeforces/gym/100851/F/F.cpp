#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 3007;

int n, mid;
num w;
int uf[N], wf[N];
num x[N], y[N];
num cost[N][N];
num dists[N*N];
int ds;
int res[2];
int turn;

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

bool solve () {
    for (int i = 0; i <= n+1; i++) {
        uf[i] = i;
        wf[i] = 1;
    }
    num aux = dists[mid];
    num met = (aux>>2);

    for (int i = 0; i < n; i++) {
        if (cost[n][i] <= met)
            join(n, i);
        if (cost[n+1][i] <= met)
            join(n+1, i);

        for (int j = 0; j < n; j++)
            if (cost[i][j] <= met)
                join(i, j);
    }
    if (w*w <= met)
        join(n, n+1);

    if (find(n) == find(n+1)) {
        res[0] = res[1] = 0;
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (find(i) == find(n+1) && cost[n][i] <= aux) {
            res[0] = n;
            res[1] = i;
            return 1;
        }

        if (find(i) == find(n) && cost[n+1][i] <= aux) {
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
    if (w*w <= aux) {
        res[0] = n;
        res[1] = n+1;
        return 1;
    }

    return 0;
}

int main () {
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    scanf("%lld %d", &w, &n);

    for (int i = 0; i < n; i++)
        scanf("%lld %lld", x+i, y+i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dists[ds++] = cost[i][j] = dist(i, j);
            dists[ds] = (dists[ds-1]<<2); ds++;
        }
        dists[ds++] = cost[n][i] = sq(x[i]);
        dists[ds] = (dists[ds-1]<<2); ds++;
        dists[ds++] = cost[n+1][i] = sq(w-x[i]);
        dists[ds] = (dists[ds-1]<<2); ds++;
    }
    dists[ds++] = w*w;

    sort(dists, dists+ds);
    ds = unique(dists, dists+ds) - dists;

    int lo = 0;
    int hi = ds;

    while (lo < hi) {
        mid = lo + ((hi-lo)>>1);

        if (solve())
            hi = mid;
        else
            lo = mid+1;
    }

    mid = hi;
    printf("%lld\n", dists[mid]);
    assert(solve());

    int a = res[0];
    int b = res[1];
 //   printf("%d %d\n", a, b);

    if (a == n && b == n+1)
        printf("%.3f %.3f\n", .5*double(w), 7.);
    else if (a == n)
        printf("%.3f %.3f\n", .5*double(x[b]), double(y[b]));
    else if (a == n+1)
        printf("%.3f %.3f\n", double(x[b]) + .5*double(w-x[b]), double(y[b]));
    else
        printf("%.3f %.3f\n", .5*double(x[a]+x[b]), .5*double(y[a]+y[b]));
}
