#include <bits/stdc++.h>

using namespace std;

typedef long long int num;
const int N = 307;
const int T = 1e5+7;
const num MOD = 1e9+7;

num mod (num a)
{ return (a%MOD + MOD)%MOD; }

int n, q, t, a, b;
int nx[N], v[N], sum[N];
int visi[N];
num pd[2][T];

int dfs (int u) {
    if (u == 0)
        return 0;
    if (visi[u] == 1) {
        printf("0\n");
        exit(0);
    }
    if (visi[u] == 2)
        return sum[u];

    sum[u] = v[u];
    visi[u] = 1;

    sum[u] += dfs(nx[u]);

    visi[u] = 2;
    return sum[u];
}

int main () {
    scanf("%d %d %d", &n, &q, &t);

    for (int i = 1; i <= n; i++)
        scanf("%d", v+i);

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &b, &a);
        nx[a] = b;
    }

    for (int i = 1; i <= n; i++)
        dfs(i);

    for (int i = 1; i <= n; i++) {
        t -= sum[i] - v[i];
        if (t < 0) {
            printf("0\n");
            return 0;
        }
    }

    pd[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        pd[i&1][0] = 1;
        for (int k = 1; k <= t; k++) {
            pd[i&1][k] = pd[!(i&1)][k];
            if (k >= sum[i])
                pd[i&1][k] = mod(pd[i&1][k] + pd[i&1][k-sum[i]]);
        }
    }

    printf("%d\n", pd[n&1][t]);
}
