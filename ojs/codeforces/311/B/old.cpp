#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const int P = 102;

int n, m, p;
num d[N];
num t[N];
num dp[P][N];
num pre[N];

int main () {
    scanf("%d %d %d", &n, &m, &p);

    d[0] = 0;
    for (int i = 1; i < n; i++) {
        scanf("%I64d", d+i);
        d[i] += d[i-1];
    }

    num add = 0;
    for (int i = 0; i < m; i++) {
        int h;
        scanf("%d %I64d", &h, t+i);
        t[i] -= d[h-1];
        add -= t[i];
        if (t[i] < 0)
            t[i] = 0;
    }

    sort(t, t+m);

    dp[1][0] = 0;
    for (num i = 1; i <= m; i++)
        dp[1][i] = t[i-1]*i;

    for (int k = 2; k <= p; k++) {
        dp[k][0] = 0;
        for (num i = 1; i <= m; i++) {
            dp[k][i] = LLONG_MAX;
            for (num j = 0; j <= i; j++)
                dp[k][i] = min(dp[k][i], dp[k-1][j] + t[i-1]*(i-j));
        }
    }

    printf("%I64d\n", dp[p][m]+add);
}
