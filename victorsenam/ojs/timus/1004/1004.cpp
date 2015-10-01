#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int M = N*N;

int dist[2][N][N];
int from[2][N][N];
int a[2*M], b[2*M], w[2*M];
int n, m;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n != -1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[0][i][j] = dist[1][i][j] = i==j?0:INT_MAX;
                from[0][i][j] = from[1][i][j] = i;
            }
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", a+i, b+i, w+i);
            a[i]--; b[i]--;
            a[i+m] = b[i];
            b[i+m] = a[i];
            w[i+m] = w[i];
            dist[0][a[i]][b[i]] = min(dist[0][a[i]][b[i]], w[i]);
            dist[0][b[i]][a[i]] = dist[0][a[i]][b[i]];
            dist[1][a[i]][b[i]] = dist[0][a[i]][b[i]];
            dist[1][b[i]][a[i]] = dist[0][b[i]][a[i]];
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (max(dist[0][i][k], dist[0][k][j]) < INT_MAX && dist[0][i][j] > dist[0][i][k] + dist[0][k][j]) {
                        dist[0][i][j] = dist[0][i][k] + dist[0][k][j];
                        from[0][i][j] = from[0][k][j];
                    }
                }
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (from[0][i][j] != from[1][k][j] && max(dist[1][i][k], dist[1][k][j]) < INT_MAX && dist[1][i][j] > dist[1][i][k] + dist[1][k][j]) {
                        dist[1][i][j] = dist[1][i][k] + dist[1][k][j];
                        from[1][i][j] = from[1][k][j];
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[0][i][j] == INT_MAX)
                    printf("-1 ");
                else 
                    printf("%d ", dist[0][i][j]);
            }
            printf("\n");
        }
        printf("==\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[1][i][j] == INT_MAX)
                    printf("-1 ");
                else 
                    printf("%d ", dist[1][i][j]);
            }
            printf("\n");
        }
        
        int res = INT_MAX;
        for (int k = 0; k < 2*m; k++) {
            for (int i = 0; i < n; i++) {
                if (i == a[k] || i == b[k])
                    continue;
                if (dist[0][i][a[k]] == INT_MAX || dist[1][b[k]][i] == INT_MAX)
                    continue;
                res = min(res, dist[0][i][a[k]]+dist[1][b[k]][i]+w[k]);
                printf("%d -> %d <- %d = %d\n", a[k]+1, i+1, b[k]+1, dist[0][i][a[k]]+dist[1][b[k]][i]+w[k]);
            }
        }
        printf("%d\n", res);
        printf("==\n");
    }
}
