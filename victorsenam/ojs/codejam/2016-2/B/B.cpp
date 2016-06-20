#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 16;
const int K = (1<<N);

int t, n, k;
int visi[N][N+N][K], turn;
double memo[N][N+N][K];
double p[N];

double pd (int i, int y, int mask) {
    if (i == n) {
        if (y) return 0;
        return 1.;
    }
    double & me = memo[i][y+N][mask];
    if (visi[i][y+N][mask] == turn)
        return me;
    visi[i][y+N][mask] = turn;
    if (mask&1)
        me = p[i]*pd(i+1, y-1, (mask>>1)) + (1.-p[i])*pd(i+1, y+1, (mask>>1));
    else
        me = pd(i+1, y, (mask>>1));
    return me;
}

int main () {
    scanf("%d", &t);
    for (int cs = 1; cs <= t; cs++) {
        turn++;
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%lf", &p[i]);

        double maxi = 0.;
        for (int i = 0; i < (1<<n); i++) {
            if (__builtin_popcount(i) != k) continue;
            maxi = max(maxi, pd(0,0,i));
        }

        printf("Case #%d: %.20f\n", cs, maxi);
    }
}
