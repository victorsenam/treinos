#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int n, k;
int x[N], w[N];
int dp[2][N], acc[N], sum[N];

int main () {
    while (scanf("%d %d", &n, &k) != EOF && n && k) {
        for (int i = 0; i < n; i++)
            scanf("%d %d", x+i, w+i);

        sum[0] = 0;
        for (int i = 0; i < n; i++)
            sum[i] = sum[i-!!i] + w[i];

        acc[0] = 0;
        for (int i = 0; i < n; i++)
            acc[i] = dp[1][i] = acc[i-!!i] + sum[i-!!i]*(x[i]-x[i-!!i]);

        for (int q = 2; q <= k; q++) {
            bool t = q&1;
            
            for (int i = q-1; i < n; i++) {
                dp[t][i] = dp[!t][i-1];

                for (int j = q-2; j < i; j++)
                    dp[t][i] = min(dp[t][i], dp[!t][j] + acc[i] - acc[j] - sum[j]*(x[i]-x[j]));
            }
        }

        printf("%d\n", dp[k&1][n-1]);
    }
}
