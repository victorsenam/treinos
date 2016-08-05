#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 3007;

double pd[N][N];
double sum[N][N];
int n, m, t;
double k;
char str[2][N];

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %lf", &n, &m, &k);
        for (int l = 0; l < 2; l++)
            scanf(" %s", str[l]);

        for (int i = 0; i <= max(n, m)+1; i++) {
            sum[i][m+1] = sum[n+1][i] = 0.;
        }

        for (int i = n; i >= 0; i--) {
            for (int j = m; j >= 0; j--) {
                if (i == n && j == m) {
                    pd[i][j] = 0.; 
                } else if (str[0][i] == str[1][j]) {
                    pd[i][j] = pd[i+1][j+1];
                } else {
                    pd[i][j] = k + sum[i+(i<n)][j+(j<m)]/double((n-i+(i==n))*(m-j+(j==m)));

                    if (i < n)
                        pd[i][j] = min(pd[i][j], 1. + pd[i+1][j]);
                    if (j < m)
                        pd[i][j] = min(pd[i][j], 1. + pd[i][j+1]);
                }
                sum[i][j] = pd[i][j] + sum[i+1][j] + sum[i][j+1] - sum[i+1][j+1];
            }
        }

        printf("%.20f\n", pd[0][0]);
    }
}
