#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int M = N*N;

int dist[N][N];
int from[N][N];
int a[M], b[M], w[M];
int n, m;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n != -1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = i==j?0:INT_MAX;
                from[i][j] = i;
            }
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", a+i, b+i, w+i);
            a[i]--; b[i]--;
            dist[a[i]][b[i]] = min(dist[a[i]][b[i]], w[i]);
            dist[b[i]][a[i]] = dist[a[i]][b[i]];
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (max(dist[i][k], dist[k][j]) < INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        from[i][j] = from[k][j];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INT_MAX)
                    printf("-1 ");
                else 
                    printf("%d ", dist[i][j]);
            }
            printf("\n");
        }
        
        int res = INT_MAX;
        for (int k = 0; k < m; k++) {
            for (int i = 0; i < n; i++) {
                if (i == a[k] || i == b[k])
                    continue;
                if (dist[i][a[k]] == INT_MAX || dist[i][b[k]] == INT_MAX)
                    continue;
                res = min(res, dist[i][a[k]]+dist[b[k]][i]+w[k]);
                printf("%d -> %d <- %d = %d\n", a[k]+1, i+1, b[k]+1, dist[i][a[k]]+dist[b[k]][i]+w[k]);
            }
        }
        printf("%d\n", res);
        printf("==\n");
    }
}
