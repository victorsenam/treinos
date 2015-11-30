#include <bits/stdc++.h>

using namespace std;

const int N = 103;

int a, b, k, n, m;
int memo[N][N];
int visi[N][N];
int turn;
int qt[20][N], be[20][N], cs[20][N];
char str[20];

int dp (int i, int k) {
    if (i == m || k <= 0)
        return 0;

    int & me = memo[i][k];
    if (visi[i][k] == turn)
        return me;
    visi[i][k] = turn;

    me = dp(i+1, k);
    int pr = be[b][i]-cs[a][i];

    if (pr <= 0)
        return me;

    for (int j = 1; j <= min(qt[a][i], k); j++) {
        me = max(me, pr*j + dp(i+1, k-j));
    }

    return me;
}

int main ( ){
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf(" %s", str);
        for (int j = 0; j < m; j++) {
            scanf("%d", &cs[i][j]);
            scanf("%d", &be[i][j]);
            scanf("%d", &qt[i][j]);
        }
    }

    int res = 0;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            turn++;
            a = i;
            b = j;
            int val = dp(0, k);
            res = max(res, val);
        }
    }

    printf("%d\n", res);
}
