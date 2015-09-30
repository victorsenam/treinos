#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int M = N*N;

int mat[N][N];
int from[N][N];
int a[M], b[M], w[M];
int n, m;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n != -1) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = i==j?0:INT_MAX;

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", a+i, b+i, w+i);
            a[i]--; b[i]--;
            mat[a[i]][b[i]] = min(mat[a[i]][b[i]], w[i]);
            mat[b[i]][a[i]] = mat[a[i]][b[i]];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    mat[i][j] = min(mat[i][j], max(max(mat[i][k], mat[k][j]), mat[i][k]+mat[k][j]));
                    if (mat[i][j] != mat[j][i])
                        from[i][j] = from[j][i] = k;
                    mat[j][i] = mat[i][j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == INT_MAX)
                    printf("-1 ");
                else 
                    printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
        
        int res = INT_MAX;
        for (int k = 0; k < m; k++) {
            for (int i = 0; i < n; i++) {
                if (i == a[k] || i == b[k])
                    continue;
                if (mat[i][a[k]] == INT_MAX || mat[i][b[k]] == INT_MAX)
                    continue;
                res = min(res, mat[i][a[k]]+mat[i][b[k]]+w[k]);
                printf("%d -> %d <- %d = %d\n", a[k]+1, i+1, b[k]+1, mat[i][a[k]]+mat[i][b[k]]+w[k]);
            }
        }
        printf("%d\n", res);
        printf("==\n");
    }
}
