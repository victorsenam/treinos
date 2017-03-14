#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
typedef long long int num;

num dp[2][N];
int n, k;
num x[N];
num cost[N][N];

void solve (int lo, int hi, int l, int r, bool ty) {
    if (lo == hi)
        return;

    int mid = (lo+hi)/2;
    
    int ind = mid;
    num res = dp[!ty][mid];

    for (int i = l; i <= min(r, mid); i++) {
        num loc = dp[!ty][i-!!i] + cost[i][mid];
        if (loc < res) {
            res = loc;
            ind = i;
        }
    }
    dp[ty][mid] = res;

    solve(lo, mid, l, ind, ty);
    solve(mid+1, hi, ind, r, ty);
}

int main () {
    while (scanf("%d %d", &n, &k) != EOF && n) {
        for (int i = 0; i < n; i++)
            scanf("%lld", x+i);

        for (int i = 0; i < n; i++) {
            num acc = x[i];
            cost[i][i] = 0;
            for (int j = i+1; j < n; j++) {
                cost[i][j] = cost[i][j-1] + x[j]*acc;
                acc += x[j];
            }
        }

        for (int i = 0; i < n; i++)
            dp[0][i] = cost[0][i];

        for (int q = 1; q <= k; q++) {
            solve(0, n, 0, n, q&1);
        }
        printf("%lld\n", dp[k&1][n-1]);
    }
}
