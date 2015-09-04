#include <bits/stdc++.h>

using namespace std;

const int K = 28;
const int N = 5007;

int n, m, t;
int sum[2][N][K];
int tot[K];
int memo[N][N];
char str[2][N];
int vis[N][N];
int turn;

int opens (int i, int j) {
    int res = 0;
    for (int k = 0; k < 26; k++) {
        int aux = sum[0][i][k] + sum[1][j][k];
        if (aux > 0 && aux < tot[k])
            res++;
    }
    return res;
}

int pd (int i, int j) {
    if (i == n && j == m)
        return 0;

    int & me = memo[i][j];

    if (vis[i][j] == turn)
        return me;
    
    me = INT_MAX;

    if (i < n)
        me = min(me, pd(i+1, j));
    if (j < m)
        me = min(me, pd(i, j+1));

    me = max(me, me + opens(i, j));
    return me;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf(" %s %s", str[0], str[1]);
        n = strlen(str[0]);
        m = strlen(str[1]);

        turn++;
        for (int k = 0; k < 26; k++)
            sum[0][0][k] = sum[1][0][k] = tot[k] = 0;
        
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < 26; k++)
                sum[0][i+1][k] = sum[0][i][k];
            sum[0][i+1][str[0][i]-'A']++;
            tot[str[0][i]-'A']++;
        }
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < 26; k++)
                sum[1][i+1][k] = sum[1][i][k];
            sum[1][i+1][str[1][i]-'A']++;
            tot[str[1][i]-'A']++;
        }

        printf("%d\n", pd(0,0));
    }
}
