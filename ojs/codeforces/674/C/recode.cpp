#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;

double v[N];
double t[N];
double s[N];
double f[N];
double memo[2][N];
int n, k;
int w;

double calc (int i, int j) {
    return (t[j] - t[i]) - (s[i])*(f[j]-f[i]);
}

void solve (int a, int b, int l, int r) {
    if (a > b) return;

    int c = (a+b)/2;
    int x = min(l, c-1);

    memo[w&1][c] = memo[(!w&1)][c];
    for (int i = x; i <= r && i < c; i++) {
        double loc = memo[!(w&1)][i] + calc(i,c);
        if (i == x || loc < memo[w&1][c]) {
            memo[w&1][c] = loc;
            x = i;
        }
    }

    solve(a, c-1, l, x);
    solve(c+1, b, x, r);
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%lf", &v[i]);
        s[i] = s[i-1] + v[i];
        f[i] = f[i-1] + 1./v[i];
        t[i] = t[i-1] + s[i]/v[i];
    }

    for (int i = 1; i <= n; i++) {
        memo[0][i] = t[i];
    }

    for (w = 1; w < k; w++) {
        solve(1, n, 0, n);
    }

    printf("%.20f\n", memo[!(k&1)][n]);
}
