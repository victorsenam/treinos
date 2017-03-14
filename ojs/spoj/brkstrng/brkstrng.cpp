#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int n;
ll v[N];
ll memo[N][N];
int s[2][N];

int main () {
    while (scanf("%lld %d", &v[0], &n) != EOF) {
        v[n+1] = v[0];
        v[0] = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld", &v[i]);

        for (int i = 0; i <= n; i++) {
            s[1][i] = i;
            memo[0][i] = 0;
        }

        for (int t = 2; t <= n+1; t++) {
            for (int i = 0; i + t <= n+1; i++) {
                memo[i][i+t] = LLONG_MAX;
                for (int x = s[!(t&1)][i]; x <= s[!(t&1)][i+1]; x++) {
                    ll loc = memo[i][x] + memo[x][i+t];
                    if (loc < memo[i][i+t]) {
                        memo[i][i+t] = loc;
                        s[t&1][i] = x;
                    }
                }
                memo[i][i+t] += v[i+t] - v[i];
            }
        }

        printf("%lld\n", memo[0][n+1]);
    }

}
