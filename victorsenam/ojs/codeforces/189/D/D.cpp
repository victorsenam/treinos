#include <bits/stdc++.h>

using namespace std;

const int N = 62;
const int K = 1001;

int adj[N][N][N];
int memo[N][N][K];
int turn;
int n, m, r;
int a, b, k;

int main () {
    scanf("%d %d %d", &n, &m, &r);

    for (int c = 0; c < m; c++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &adj[c][i][j]);
        for (int s = 0; s < n; s++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    adj[c][i][j] = min(adj[c][i][j], adj[c][i][s] + adj[c][s][j]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            memo[i][j][0] = adj[0][i][j];
            for (int c = 1; c < m; c++)
                memo[i][j][0] = min(memo[i][j][0], adj[c][i][j]);
        }
    }
    
    int t;
    for (t = 1; t < K; t++) {
        bool ch = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                memo[i][j][t] = memo[i][0][0] + memo[0][j][t-1];
                for (int s = 1; s < n; s++)
                    memo[i][j][t] = min(memo[i][j][t], memo[i][s][0] + memo[s][j][t-1]);
                if (memo[i][j][t] < memo[i][j][t-1])
                    ch = 1;
            }
        }
        if (!ch)
            break;
    }

    for (int q = 0; q < r; q++) {
        scanf("%d %d %d", &a, &b, &k);
        a--; b--;

        printf("%d\n", memo[a][b][min(k, t)]);
    }
}
