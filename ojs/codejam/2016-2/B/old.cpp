#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 203;

int t, n, k;
int visi[N][N+N][N], turn;
double memo[N][N+N][N];
double p[N];

double pd (int i, int y, int k) {
    if (i == n) {
        if (k) return -1./0.;
        if (y) return 0;
        return 1.;
    }
    if (k < 0)
        return -1./0.;
    double & me = memo[i][y+N][k];
    if (visi[i][y+N][k] == turn)
        return me;
    me = max(pd(i+1, y, k), p[i]*pd(i+1, y-1, k-1) + (1.-p[i])*pd(i+1, y+1, k-1));
    printf("%d %d %d -> %.20f\n", i, y, k, me);
    return me;
}

int main () {
    scanf("%d", &t);
    for (int cs = 1; cs <= t; cs++) {
        turn++;
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++)
            scanf("%lf", &p[i]);
        printf("Case #%d: %.20f\n", cs, pd(0, 0, k));
    }
}
