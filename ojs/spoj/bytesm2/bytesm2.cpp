#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100

int mat[N][N];
int memo[N][N];
int n, m, t;

int pd (int i, int j) {
    if (i < 0 || i >= n) return 0;
    if (j < 0 || j >= m) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    int a = 0;
    for (int k = -1; k <= 1; k++)
        a = max(a, pd(i+1, j+k));

    return memo[i][j] = a + mat[i][j];
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &mat[i][j]);
                memo[i][j] = -1;
            }
        }
        
        int a = 0;
        for (int i = 0; i < m; i++)
            a = max(pd(0, i), a);
        
        printf("%d\n", a);
    }
}
