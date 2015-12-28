// JEITO NOOB PROVAVELMENTE CERTO

#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const int P = 102;

int n, m, p;
num d[N];
num t[N];
num dp[N][P];
num pre[N];

int main () {
    scanf("%d %d %d", &n, &m, &p);

    d[0] = 0;
    for (int i = 1; i < n; i++) {
        scanf("%lld", d+i);
        d[i] += d[i-1];
    }

    pre[0] = 0;
    for (int i = 0; i < m; i++) {
        int h;
        scanf("%d %lld", &h, t+i);
        t[i] -= d[h-1];
    }

    sort(t, t+m);

    for (int i = 0; i < m; i++) {
        pre[i] = pre[i-!!i] + t[i];
        dp[i][1] = t[i]*num(i+1) - pre[i];

        printf("%lld ", dp[i][1]);
    }
    printf("\n");

    for (int i = 0; i < m; i++) {
        for (int k = 2; k <= p; k++) {
            dp[i][k] = dp[i][k-1];

            for (int j = 0; j < i; j++) {
                dp[i][k] = min(dp[i][k], dp[j][k-1] + t[i]*num(i-j) - pre[i] + pre[j-!!j]);
            }
        }
    }

   printf("%lld\n", dp[m-1][p]);
}
