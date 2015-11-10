// INCOMPLETO - NOOBANDO PRA CODAR DO JEITO NOOB, SEU NOOB
#include <bits/stdc++.h>

using namespace std;

typedef int num;

const int N = 4002;

int n, k, q;
char str[N][N];
int acc[N][N];
int dp[2][N];

inline int cost (int i, int j) {
    int val = acc[j][j] - acc[i][j] - acc[j][i] + acc[i][i];
    printf("cost (%d,%d) = %d\n", i+1, j, val);
    return val;
}

int main () {
    scanf("%d %d", &n, &k);

    acc[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        acc[i][0] = acc[0][i] = 0;
        scanf(" %[0-9 ]", &str[i]);
        for (int j = 1; j <= n; j++)
            str[i][j] = str[i][((j-1)<<1)]-'0';
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            acc[i][j] = int(str[i][j]) + acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1];


    for (int i = 1; i <= n; i++)
        dp[1][i] = cost(0, i);

    for (int i = 1; i <= n; i++)
        printf("%d ", dp[1][i]);
    printf("\n");

    for (int q = 2; q <= k; q++) {
        bool ty = (q&1);

        for (int i = q; i <= n; i++) {
            dp[ty][i] = INT_MAX;
            for (int j = q-1; j <= i; j++) {
                dp[ty][i] = min(dp[ty][i], dp[!ty][j-1] + cost(j-1,i));
            }
            printf("%d ", dp[ty][i]);
        }

        printf("\n");
    }

    printf("%d\n", dp[k&1][n]);
}
