#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
const int N = 2000007;
const ll MOD = 1000000007ll;

inline ll mod (ll a) { return a%MOD; }

ll fexp (ll a, int e) {
    ll r;
    for (r = 1ll; e; e >>= 1, a = mod(a*a)) if (e&1) r = mod(r*a);
    return r;
}


ll a[N], fat[N], ifat[N];
ll m, n;
ll res, qt;
ll f, g;
int k;

inline ll choose (ll n, ll p) {
    if (p > n || p < 0) return 0;
    return mod(mod(fat[n]*ifat[p])*ifat[n-p]);
}
inline ll ichoose (ll n, ll p) {
    if (p > n || p < 0) return 0;
    return mod(mod(ifat[n]*fat[p])*fat[n-p]);
}

int main () {
    fat[0] = 1ll;
    for (int i = 1; i < N; i++) {
        fat[i] = mod(fat[i-1]*i);
    }
    ifat[N-1] = fexp(fat[N-1], MOD-2);
    for (int i = N-2; i >= 0; i--)
        ifat[i] = mod(ifat[i+1]*(i+1));

    scanf("%d", &k);
    n = (1ll << k);
    
    for (int i = 1; i <= n; i++)
        scanf("%lld", a+i);

    res = 0ll;
    qt = n;
    for (ll m = 1ll; m <= n; (m<<=1), (qt>>=1)) {
        g = 0;
        for (int i = 2; i <= n; i++) {
            g = mod(g + mod(a[i-1]*mod(choose(n-i+1-m, m-1)*ichoose(n-m, m))));
            f = mod(a[i]*mod(choose(n-i, m-1)*ichoose(n,m)));
            res = mod(res + mod(qt*mod(f*g)));
            /*for (int j = 1; j+m+m-1 <= n && j < i; j++) {
                printf("%lld %lld -> (%lld %lld) %lld (%lld %lld) %lld\n", a[i], a[j], n-i, m-1,  mod(choose(n-i, m-1)*ichoose(n,m)), n-j-m, m-1, mod(choose(n-j-m, m-1)*ichoose(n-m,m)));
                res = mod(res + mod(qt*mod(mod(mod(a[i]*a[j])*mod(choose(n-i, m-1)*ichoose(n,m)))*mod(choose(n-j-m, m-1)*ichoose(n-m,m)))));
            }*/
        }
    }
    printf("%lld\n", res);
}
