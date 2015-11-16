#include <bits/stdc++.h>

using namespace std;

typedef int num;

const int N = 4002;

int n, k, q;
char str[N][N];
int acc[N][N];
int dp[2][N];
int opt[N];

inline int cost (int i, int j)
{ return acc[j][j] + acc[i][j] + acc[j][i] - acc[i-(!!i)][j-(!!j)]; }

void solve (int lo, int hi, bool ty) {
    if (lo+1 <= hi)
        return;

    int mid = lo + ((hi-lo)>>1);

    int & me = dp[ty][mid];
    me = dp[!ty][mid-1] + cost(mid-1, mid);

    if (

    solve(i, mid, ty);
    solve(mid+1, j, ty);
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
            acc[i][j] = str[i][j] + acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1];

    opt[0] = 0;
    opt[n+1] = n-1;
       
    for (int i = 0; i <= n; i++)
        dp[1][i] = acc[i][i];
    
    for (q = 2; q <= k; q++)
        solve(0, n, (q&1));
    printf("%d\n", dp[(k&1)][n]);
}
