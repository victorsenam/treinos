#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 8e3+7;
const int M = 8e2+7;

int n, m;
ll c[N];
ll memo[2][N];
ll acc[N];
int k;

void solve (int a, int b, int l, int r) {
    if (a > b) return;

    int mid = (a+b)/2;
    int x = l;
    memo[k&1][mid] = (acc[mid] - acc[x])*ll(mid-x) + memo[!(k&1)][x];

    for (int s = x; s <= r && s < mid; s++) {
        ll loc = (acc[mid] - acc[s])*ll(mid-s) + memo[!(k&1)][s];
        if (loc <= memo[k&1][mid]) {
            memo[k&1][mid] = loc;
            x = s;
        }
    }

    solve(a, mid-1, l, x);
    solve(mid+1, b, x, r);
}

int main () {
    scanf("%d %d", &n, &m);

    acc[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
        acc[i] = acc[i-1] + c[i];
    }

    memo[0][0] = 0;
    for (int i = 1; i <= n; i++)
        memo[0][i] = acc[i] * ll(i);

    for (k = 1; k < m; k++)
        solve(1, n, 0, n);

    printf("%lld\n", memo[!(m&1)][n]);
}
