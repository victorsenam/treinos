#include <bits/stdc++.h>

using namespace std;

const int N = 32;
const int K = 53;

bool visi[N][N][K];
int memo[N][N][K];

int dp (int n, int m, int k) {
    if (n*m == k || k == 0)
        return 0;
    if (visi[n][m][k])
        return memo[n][m][k];

    int & me = memo[n][m][k];
    me = INT_MAX;
    visi[n][m][k] = 1;

    for (int i = 1; i < n; i++) {
        int loc;
        if (i*m >= k)
            loc = dp(i, m, k);
        else
            loc = dp(n-i, m, k-i*m);

        me = min(max(loc, loc + m*m), me);
    }

    for (int i = 1; i < m; i++) {
        int loc;
        if (i*n > k)
            loc = dp(n, i, k);
        else
            loc = dp(n, m-i, k-i*n);

        me = min(max(loc, loc + n*n), me);
    }

    return me;
}

int main( ) {
    int t;
    scanf("%d", &t);

    while (t--) {
        int a, b, q;
        scanf("%d %d %d", &a, &b, &q);
        printf("%d\n", dp(a, b, q));
    }
}
