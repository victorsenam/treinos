#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int n, m;
int k;
ll v[N];
ll memo[2][N];
ll acc[N][N];

ll calc (int a, int b) {
    return acc[b][b] - acc[a][b] - acc[b][a] + acc[a][a];
}

void solve (int a, int b, int l, int r) {
    if (a > b) return;

    int c = (a+b)/2;
    int x = min(l, c-1);

    for (int i = x; i <= r && i < c; i++) {
        ll loc = memo[!(k&1)][i] + calc(i,c);
        if (i == x || loc < memo[k&1][c]) {
            memo[k&1][c] = loc;
            x = i;
        }
    }

    solve(a, c-1, l, x);
    solve(c+1, b, x, r);
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        for (int i = 1; i <= n; i++)
            scanf("%lld", &v[i]);
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                acc[i][j] = acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1];
                if (i > j)
                    acc[i][j] += v[i]*v[j];
            }

        for (int i = 1; i <= n; i++)
            memo[0][i] = calc(0,i);

        for (k = 1; k <= m; k++)
            solve(1, n, 0, n);
        
        printf("%lld\n", memo[(m&1)][n]);
    }
}
