#include <bits/stdc++.h>

using namespace std;

typedef int num;

const int N = 4002;

int n, k, q;
char str[N][N];
int acc[N][N];
int dp[2][N];

inline int cost (int i, int j) 
{ return acc[j][j] + acc[i][i] - acc[i][j] - acc[j][i]; }

int main () {
    scanf("%d %d", &n, &k);

    acc[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        acc[i][0] = acc[0][i] = 0;
        scanf(" %[0-9 ]", str[i]);
        for (int j = 1; j <= n; j++)
            str[i][j] = str[i][((j-1)<<1)]-'0';
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            acc[i][j] = acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1] + str[i][j];

    for (int i = 1; i <= n; i++)
        dp[1][i] = cost(0, i);
    
    for (int q = 2; q <= k; q++) {
        bool t = q%2;
        
        for (int i = q; i <= n; i++) {
            dp[t][i] = dp[!t][q-1] + cost(q-1, i);
            
            for (int j = q; j < i; j++)
                dp[t][i] = min(dp[t][i], dp[!t][j] + cost(j, i));
        }
    }

    printf("%d\n", (dp[k%2][n]>>1));
}
