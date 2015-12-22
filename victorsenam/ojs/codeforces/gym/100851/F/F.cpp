#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 3007;

int n;
int p[N];
num w;
num x[N], y[N];
num dist[2][N];
num cost[N][N];

void djs (int ty) {
    for (int i = 0; i < n; i++) {
        dist[ty][i] = ty?(w-x[i])*(w-x[i]):x[i]*x[i];
        p[i] = i;
    }

    for (int i = n-1; i >= 0; i--) {
        int imin = 0;
        for (int j = 1; j <= i; j++)
            if (dist[ty][p[j]] < dist[ty][p[imin]])
                imin = j;
        swap(p[imin], p[i]);

        for (int j = 0; j < i; j++)
            dist[ty][p[j]] = min(dist[ty][p[j]], max(dist[ty][p[i]], cost[p[i]][p[j]]));
    }
}

int main () {
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    scanf("%I64d %d", &w, &n);

    for (int i = 0; i < n; i++)
        scanf("%I64d %I64d", x+i, y+i);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);

    djs(0); djs(1);

    double res = .25*w*w;
    double rx = .5*w;
    double ry = .26;
    for (int i = 0; i < n; i++) {
        double cst;
        cst = max(.25*x[i]*x[i], double(dist[1][i]));
        if (cst < res) {
            res = cst;
            rx = .5*x[i];
            ry = y[i];
        }

        cst = max(.25*(w-x[i])*(w-x[i]), double(dist[0][i]));
        if (cst < res) {
            res = cst;
            rx = .5*(x[i]+w);
            ry = y[i];
        }

        for (int j = 0; j < n; j++) {
            cst = max((double) max(dist[0][i], dist[1][j]), .25*cost[i][j]);
            if (cst < res) {
                res = cst;
                rx = .5*(x[i]+x[j]);
                ry = .5*(y[i]+y[j]);
            }
        }
    }

    printf("%.3f %.3f\n", rx, ry);
}
