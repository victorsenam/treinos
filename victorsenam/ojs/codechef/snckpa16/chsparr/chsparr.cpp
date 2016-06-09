#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const ll MOD = 1000000007;
const int N = 100007;
const int M = 32;

ll a[N];
int t, n;
int m;
ll x, y;

ll f[M], q[M];

ll qq(int m) {
    if (m < 0) return 0ll;
    return q[m];
}

ll ff (int m) {
    if (m < 0) return 0ll;
    return f[m];
}

ll solve (ll a, ll b, ll i, ll j, int m) {
    ll ret;
    if (i >= qq(m)-1 || j <= 0)
        ret = 0;
    else if (i <= 0 && j >= qq(m)-1)
        ret = ((ff(m)*(a+b)%MOD)%MOD + a)%MOD;
    else
        ret = (solve(a, (a+b)%MOD, i, j, m-1) + (solve((a+b)%MOD, b, i-qq(m-1)+1, j-qq(m-1)+1, m-1)))%MOD;

    DEBUG("[%lld ... %lld] (%d,%d) #[%d] = %lld :: %lld\n", a, b, i, j, m, qq(m), ret);
    return ret;
}

int main () {
    scanf("%d", &t);

    f[0] = 0;
    q[0] = 2;
    for (int i = 1; i < M; i++) {
        f[i] = (3ll*f[i-1] + 1)%MOD;
        q[i] = 2ll*q[i-1] - 1;
    }

    while (t--) {
        scanf("%d %d %lld %lld", &n, &m, &x, &y);

        x--; y;
        ll res = 0;

        for (int i = 0; i < n; i++)
            scanf("%lld", a+i);

        if (n == 1) {
            printf("%lld\n", a[0]);
            continue;
        }

        int i = 0;
        while (i < n-1) {
            res = (res + solve(a[i], a[i+1], x, y, m))%MOD;
            DEBUG("\n");
            x -= q[m]-1;
            y -= q[m]-1;
            i++;
        }
        if (y == 1)
            res = (res + a[n-1])%MOD;

        printf("%lld\n", res);
    }
}
