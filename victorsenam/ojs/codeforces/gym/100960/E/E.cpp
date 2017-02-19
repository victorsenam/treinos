#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const ll MOD = 1e9+7;
ll K, m, l, r, a, b, c;

inline ll get (ll i, ll j, ll k) {
    while (k) {
        if (j >= (1ll<<(k-1))) {
            i = (1ll<<K-k+1) - 1 - i;
            j = (1ll<<k) - 1 - j;
        }
        k--;
    }
    return i;
}

ll res (ll l, ll r) {
    ll ans = 0;
    if (l%2 == 0) {
        ans = (!!((r - l + 1)&2)) * ((1ll<<K) - 1);
        ans ^= (!(r%2)) * get(0,r,K);
    } else {
        ans = ((r - (l + 1) + 1)>>1) * ((1ll<<K) - 1);
        ans += get(0, l, K);
        ans += (!(r%2)) * get(0,r,K);
    }
    return ans;
}

int main () {
    scanf("%lld %lld %lld %lld %lld %lld %lld", &K, &m, &l, &r, &a, &b, &c);

    ll h = 0;

    for (int i = 0; i < m; i++) {
        ll f = res(l,r);
        //debug("[%lld]\n", f);

        ll nh = ((l ^ r ^ h ^ f) + c) % MOD;
        ll nl = ((l ^ a ^ nh) % ((1ll<<K) + 1)) % (1ll<<K);
        ll nr = ((r ^ b ^ nh) % ((1ll<<K) - nl)) + nl;

        l = nl; r = nr; h = nh;
    }

    printf("%lld\n", h);
}
