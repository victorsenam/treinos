#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 4e3+7;

int n, m, k;
char str[2*N];
int mat[N][N];
int memo[2][N];

int calc (int a, int b) {
    return mat[b][b] - mat[a][b] - mat[b][a] + mat[a][a];
}

void solve (int a, int b, int l, int r) {
    if (a > b) return;
    int c = (a+b)/2;

    int x = min(l, c-1);
    memo[k&1][c] = INT_MAX;
    for (int i = x; i <= r && i < c; i++) {
        int loc = memo[!(k&1)][i] + calc(i, c);
        if (i == x || loc <= memo[k&1][c]) {
            x = i;
            memo[k&1][c] = loc;
        }
    }

    solve(a, c-1, l, x);
    solve(c+1, b, x, r);
}

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf(" %[0-9 ]", str);
        for (int j = 1; j <= n; j++) {
            mat[i][j] = mat[i-1][j] + mat[i][j-1] - mat[i-1][j-1];
            mat[i][j] += str[2*j-2] - '0';
        }
    }

    for (int i = 1; i <= n; i++)
        memo[0][i] = calc(0, i);

    for (k = 1; k < m; k++) {
        solve(1, n, 0, n);
    }

    printf("%d\n", memo[!(m&1)][n]/2);
}
