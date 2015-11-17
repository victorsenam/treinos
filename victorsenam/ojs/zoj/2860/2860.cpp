#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
typedef long long int num;

int n;
int x[N];
num dp[N][N];
int op[N][N];
int r;

int main () {
    while (scanf("%d %d", &r, &n) != EOF) {
        x[0] = 0; x[n+1] = r;
        for (int i = 1; i <= n; i++)
            scanf("%d", x+i);

        for (int i = 0; i <= n; i++) {
            dp[i][i+1] = 0;
            op[i][i+1] = i;
        }

        for (int k = 2; k <= n+1; k++) {
            for (int i = 0; i <= n-k+1; i++) {
                dp[i][i+k] = INT_MAX;
                op[i][i+k] = i;
                
                for (int j = op[i][i+k-1]; j <= op[i+1][i+k]; j++) {
                    num loc = dp[i][j] + dp[j][i+k] + x[i+k] - x[i];
                    if (loc < dp[i][i+k]) {
                        dp[i][i+k] = loc;
                        op[i][i+k] = j;
                    }
                }
            }
        }

        printf("%lld\n", dp[0][n+1]);
    }
}
