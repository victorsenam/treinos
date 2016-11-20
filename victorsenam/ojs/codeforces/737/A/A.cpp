#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;

int n, k;
ll s, t;
ll g[N];
ll ic[N], iv[N];

bool solve (ll c) {
    ll tt = 0;
    for (int i = 1; i <= k; i++) {
        ll d = g[i] - g[i-1];
        ll a = min(d, c - d);

        if (a < 0) return false;
        
        tt += d+d-a;
        if (tt > t) return false;        
    }
    return (tt <= t);
}

int main () {
    scanf("%d %d %lld %lld", &n, &k, &s, &t);

    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &iv[i], &ic[i]);

    for (int i = 1; i <= k ; i++)
        scanf("%lld", &g[i]);
    k++;
    g[k] = s;

    sort(g, g+k+1);
    
    ll lo = 0;
    ll hi = 1e9+3;
    while (lo < hi) {
        ll mid = (lo + hi)/2;

        if (solve(mid))
            hi = mid;
        else
            lo = mid+1;
    }

    ll res = 1e9+3;
    for (int i = 0; i < n; i++) {
        if (ic[i] >= lo)
            res = min(iv[i], res);
    }

    if (res == 1e9+3) res = -1;
    printf("%lld\n", res);
}
