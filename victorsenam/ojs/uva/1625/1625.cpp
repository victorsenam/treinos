#include <bits/stdc++.h>

using namespace std;

const int K = 28;
const int N = 5007;

int n, m, t;
int turn;
int memo[N][K];
int sum[2][N][K];
int vis[N][K];
char str[2][N];

int pd (int i, int j) {
    if (i >= n && j >= m)
        return 0;

    int & me = memo[i][j];

    if (vis[i][j] == turn)
        return me;
    vis[i][j] = turn;
    
    me = INT_MAX;

    if (i < n) {
        int loc = pd(i+1, j);
        int aux = str[0][i]-'A';

        if (sum[0][i][aux] == 0)
            if (sum[1][j][aux] == 0)
                loc -= i+j;
        if (sum[0][i+1][aux] == sum[0][n][aux])
            if (sum[1][j][aux] == sum[1][m][aux]) {
                loc = max(loc, loc+i+j);
            }

        me = min(me, loc);
    }
    
    if (j < m) {
        int loc = pd(i, j+1);
        int aux = str[1][j]-'A';

        if (sum[1][j][aux] == 0)
            if (sum[0][i][aux] == 0)
                loc -= i+j;
        if (sum[1][j+1][aux] == sum[1][m][aux])
            if (sum[0][i][aux] == sum[0][n][aux]) {
                loc = max(loc, loc+i+j);
            }

        me = min(me, loc);
    }

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
            sum[0][0][k] = sum[1][0][k] = 0;

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < 26; k++)
                sum[0][i+1][k] = sum[0][i][k];
            sum[0][i+1][str[0][i]-'A']++;
        }

        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 26; k++)
                sum[1][j+1][k] = sum[1][j][k];
            sum[1][j+1][str[1][j]-'A']++;
        }
        printf("%d\n", pd(0,0));
    }
}
