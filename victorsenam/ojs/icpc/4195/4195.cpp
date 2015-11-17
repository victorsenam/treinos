#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
typedef long long int num;

num dp[2][N];
int n, k;
int x[N];

int main ( ) {
    while (scanf("%d %d", &n, &k) != EOF && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", x+i);

        dp[0][0] = 0;
        num acc = 0, cst;
        for (int i = 0; i < n; i++) {
            dp[0][i] = dp[0][i-!!i] + acc*x[i];
            acc += x[i];
        }

        for (int q = 1; q <= k; q++) {
            bool ty = (q&1);
            for (int i = 0; i < n; i++) {
                acc = x[i]; 
                cst = 0;
                dp[ty][i] = dp[!ty][i-1];

                for (int j = i-1; j >= 0; j--) {
                    cst += acc*x[j];
                    dp[ty][i] = min(dp[ty][i], dp[!ty][j-!!j] + cst);
                    acc += x[j];
                }
            }
        }

        printf("%lld\n", dp[k&1][n-1]);
    }
}
