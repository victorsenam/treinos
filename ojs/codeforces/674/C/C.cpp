#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef double num;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 200007;
const int K = 52;

num dp[N][K];
int n, k;
num t[N];
num s[N];
num al[N];
num f[N];

num calc (int i, int j)
{ return f[i] - f[j] - al[j]*(s[i] - s[j]); }

void solve (int i, int j, int l, int r, int k) {
    if (i == j) return;
    int mid = i + (j-i)/2;
    int op = l;

    int ir = min(r, mid);

    dp[mid][k] = 1./0.;

    for (int p = l; p < ir; p++) {
        num loc = calc(p, mid) + dp[p][k-1];
        if (loc < dp[mid][k]) {
            op = p;
            dp[mid][k] = loc;
        }
    }
    

    DEBUG("%d : ótimo foi %d \\in [%d,%d) %.20f\n", mid, op, l, ir, dp[mid][k]);
    solve(i, mid, l, op+1, k);
    solve(mid+1, j, op, r, k);
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%lf", t+i);

    s[n] = 0;
    for (int i = n-1; i >= 0; i--)
        s[i] = s[i+1] + t[i];

    al[n] = 0;
    for (int i = n-1; i >= 0; i--)
        al[i] = al[i+1] + (1./t[i]);

    f[n] = 0;
    for (int i = n-1; i >= 0; i--)
        f[i] = f[i+1] + t[i]*al[i];

    for (int i = 0; i <= n; i++)
        dp[i][1] = calc(0, i);

 /*   for (int q = 2; q <= k; q++) {
        for (int i = 0; i <= n; i++) {
            dp[i][q] = 1./0.;
            for (int j = 0; j < i; j++)
                dp[i][q] = min(dp[i][q], dp[j][q-1] + calc(j, i));
        }
    }*/

    for (int q = 2; q <= k; q++) {
        solve(0, n+1, 0, n, q);
    }

    printf("%.20f\n", dp[n][k]);
}
