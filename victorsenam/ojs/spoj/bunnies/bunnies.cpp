#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

const int N = 3007;
const num INF = LLONG_MAX - 1000000000ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

num dp[N][N];
int opt[N][N];
int turn;
int k, n, t;
num a[N];

void solve (int qk, int qn) {
    for (int i = 1; i <= qk; i++) {
        dp[i][i] = dp[i-1][i-1] + a[i-1];
        opt[i][i] = i;
    }

    for (int t = 1; t <= qn; t++) {
        for (int k = 1; k <= qk && k + t <= qn; k++) {
            int st = opt[k][k+t-1];
            dp[k][k+t] = dp[k-(a[st-1]==a[k+t-1])][k+t-1] + a[st-1];
            opt[k][k+t] = st;

            int en = k+t;
            if (k < qk)
                en = opt[k+1][k+t];

            for (int j = st+1; j <= en; j++) {
                num val = dp[k-(a[j-1]==a[k+t-1])][k+t-1] + a[j-1];
                if (val < dp[k][k+t]) {
                    dp[k][k+t] = val;
                    opt[k][k+t] = j;
                }
            }
        }
    }
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++)
            scanf("%lld", a+i);

        sort(a, a+n);

        solve(k, n);

        printf("%lld\n", dp[k][n]);
    }
}
