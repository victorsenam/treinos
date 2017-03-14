#include <bits/stdc++.h>

using namespace std;

#define N 1002

int mat[N][N];
int acc[N][N];
int maxa, n, m;

int main () {
    while (scanf("%d %d", &m, &n) != EOF && n && m) {
        for (int i = 0; i < m; i++) {
            acc[i][n] = 0;
            for (int j = 0; j < n; j++) 
                scanf("%d", &mat[i][j]);
        }
        for (int i = 0; i < n; i++)
            acc[m][i] = 0;
        acc[m][n] = 0;

        for (int i = m-1; i >= 0; i--)
            for (int j = n-1; j >= 0; j--)
                acc[i][j] = acc[i+1][j]+acc[i][j+1]+mat[i][j]-acc[i+1][j+1];

        /*
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                printf("%d ", acc[i][j]);
            }
            printf("\n");
        }
        */

        maxa = 0;
        for (int k = min(n, m); k > 0 && !maxa; k--) {
            if (acc[0][0] < k*k) continue;
            for (int i = 0; i <= m-k && !maxa; i++) {
                for (int j = 0; j <= n-k && !maxa; j++) {
                    if (acc[i][j]-acc[i+k][j]-acc[i][j+k]+acc[i+k][j+k] == k*k)
                        maxa = k;
                }
            }
        }

        printf("%d\n", maxa);
    }
}
