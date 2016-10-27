#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;
const int K = 13;

ll mod;
int d, n;
ll fat[K], ift[K];
ll memo[N][K];

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r = (r*a)%mod;
        a = (a*a)%mod;
        e >>= 1;
    }
    return e;
}

ll inv (ll a) {
    return fexp(a, mod-2);
}

ll choose (ll a, ll b) {
    return (fat[a]*(ift[b]*ift[a-b])%mod)%mod;
}

ll pd (int n, int d) {
    if (n == 0)
        return (d==0);
    if (n == 1) 
        return (d==10);

    ll & me = memo[n][d];
    if (me != -1) return me;

    me = 1;

    for (int i = 1; i < n; i++) {
        for (int k = 1; k <= d; k++) {
            if (i%k) continue;

            ll res = (choose(d, k)*pd(n-i,d-k))%mod;
            res = (pd(i/k, ::d)%mod);
            if (k&1)
                me = (me * res)%mod;
            else
                me = (me * inv(res))%mod;
        }
    }

    debug("%d %d : %lld\n", n, d, me);
    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d %d %lld", &n, &d, &mod);
    fat[0] = 1;
    for (ll i = 1; i < K; i++)
        fat[i] = (fat[i-1]*i)%mod;
    ift[K-1] = inv(fat[K-1]);
    for (ll i = K-2; i >= 0; i--)
        ift[i] = (ift[i+1]*i)%mod;

    printf("%lld\n", pd(n, d));
}
