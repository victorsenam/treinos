#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;
const ll MOD = 1e9+7;

inline ll mod (ll x) {
    return ((x%MOD) + MOD)%MOD;
}

int n;
ll qt;
ll v[N];

int main () {
    scanf("%d", &n);

    for (int i =0 ; i < n; i++)
        scanf("%lld", v+i);
    sort(v, v+n);

    ll res = 0;
    qt = 1;
    for (int i = 0; i < n; i++) {
        res = mod(res + mod(qt*v[i]));
        qt = mod(qt*2ll);
    }

    qt = 1;
    for (int i = n-1; i >= 0; i--) {
        res = mod(res - mod(qt*v[i]));
        qt = mod(qt*2ll);
    }

    printf("%lld\n", res);
}
