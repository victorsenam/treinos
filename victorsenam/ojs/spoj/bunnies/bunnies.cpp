// talvez a ideia esteja certa e a forma recursiva também... mas é treta.

#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

// const int N = 3007;
const int N = 307;
const num INF = LLONG_MAX - 1000000000ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

num memo[N][N][N];
num dp[N][N][N];
int visi[N][N][N];
int turn;
int k, n, t;
num a[N];

num fdp (int k, int n, int t) {
    t = min(t, n);
    if (k == 0)
        return 0;
    if (n == 0 || t < k)
        return LLONG_MAX - 1000000000ll;

    num & me = memo[k][n][t];
    if (visi[k][n][t] == turn)
        return me;

    me = min(fdp(k - (a[t] == a[n]), n-1, t) + a[t], fdp(k, n, t-1));

    return me;
}

int main () {
    scanf("%d", &t);

    while (t-- && ++turn) {
        scanf("%d %d", &n, &k);

        for (int i = 1; i <= n; i++)
            scanf("%lld", a+i);

        sort(a+1, a+n+1);

        for (int ik = 1; ik <= k; ik++) {
            for (int it = ik; it <= ik; it++)
                dp[ik][ik][it] = dp[ik-1][ik-1][ik-1] + a[ik];

            for (int in = ik+1; in <= n; in++) {
                dp[ik][in][ik] = dp[ik-(a[in]==a[ik])][in-1][ik];
                for (int it = ik+1; it <= in; it++)
                    dp[ik][in][it] = min(dp[ik-(a[it]==a[in])][in-1][it], dp[ik][in][it-1]);
                for (int it = in+1; it <= n; it++)
                    dp[ik][in][it] = dp[ik][in][in];
            }
        }

        printf("%lld\n", fdp(k, n, n));
        printf("%lld\n", dp[k][n][n]);
    }
}
