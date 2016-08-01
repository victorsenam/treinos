#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e3+7;

int t;
int n, k;
ll h;
ll x[N], y[N], p[N];
ll memo[N][N];
int visi[N][N], turn;

bool cmp_t (int i, int j) {
    if ((x[i]<=y[i]) != (x[j]<=y[j]))
        return x[i]<=y[i];
    if (x[i]<=y[i] && x[i]!=x[j])
        return x[i]<x[j];
    if (y[i]!=y[j])
        return y[i]>y[j];
    return i<j;
}

ll dp (int i, int k) {
    if (k < 0) return 1e14;
    if (i == n) return 0;
    
    ll & me = memo[i][k];
    if (visi[i][k] == turn) return me;
    visi[i][k] = turn;
    return me = min(dp(i+1, k-1), max(dp(i+1, k) + x[p[i]] - y[p[i]], x[p[i]]));
}

int main () {
    scanf("%d", &t);

    while (t--) {
        turn++;
        scanf("%d %lld %d", &n, &h, &k);

        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", x+i, y+i);
            p[i] = i;
        }

        sort(p, p+n, cmp_t);

        int i;
        for (i = 0; i < n && x[p[i]]<=y[p[i]]; i++) {
            if (x[p[i]] >= h) {
                k--;
            } else {
                h += y[p[i]] - x[p[i]];
            }
        }
        
        if (dp(i, k) < h)
            printf("Y\n");
        else
            printf("N\n");
    }
}
