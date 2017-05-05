#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;
const ll MOD = 1e9+7;

char str[N];

inline ll mod (ll x) {
    return ((x%MOD) + MOD)%MOD;
}

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1)
            r = mod(r*a);
        a = mod(a*a);
        e >>= 1;
    }
    return r;
}

ll get (int k, int l, int r) {
    if (l == r) {
        if (k)
            return (str[l] == 'b');
        else
            return (str[l] == 'a');
    }

    ll res = 0;
    if (k) {
        int md = (l+r)/2;

        res = mod(fexp(2ll, get(0,l,md))*get(1,md+1,r));
        res = mod(res + get(1,l,md));
    } else {
        for (int i = l; i <= r; i++)
            res += (str[i] == 'a');
    }
    return mod(res);
}

int main () {
    scanf(" %s", str);

    ll qb = 0;
    int n;
    for (n = 0; str[n]; n++) {
        if (str[n] == 'b')
            qb++;
    }

    printf("%lld\n", mod(get(1, 0, n-1) - qb));
}
