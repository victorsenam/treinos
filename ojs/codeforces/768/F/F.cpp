#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const ll MOD = 1e9+7;
const int N = 3e5+7;

ll f, w, h;
ll fat[N], ivf[N];

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r = (r * a)%MOD;
        a = (a * a)%MOD;
        e >>= 1;
    }
    return r;
}

inline ll choose (ll a, ll b) {
    if (b > a || a < 0 || b < 0) return 0ll;
    if (b == 0) return 1ll;
    if (a == 0) return 0ll;

    return (fat[a] * ((ivf[b] * ivf[a-b])%MOD))%MOD;
}

int main () {
    fat[0] = 1;
    for (ll i = 1; i < N; i++)
        fat[i] = (fat[i-1] * i) % MOD;
    ivf[N-1] = fexp(fat[N-1], MOD-2);
    for (ll i = N-2; i >= 0; i--)
        ivf[i] = (ivf[i+1] * (i+1))%MOD;

    scanf("%lld %lld %lld", &f, &w, &h);

    if (f == 0) {
        printf("%d\n", w>h);
        return 0;
    }
    if (w == 0) {
        printf("1\n");
        return 0;
    }

    ll p = 0;
    ll q = 0;
    for (ll s = 0; s <= w; s++) {
        for (ll t = max(s-1,0ll); t <= s+1 && t <= f; t++) {
            ll lp = (choose(f - 1, t - 1) * choose(w - s*h - 1, s - 1)) % MOD;
            ll lq = (choose(f - 1, t - 1) * choose(w - 1, s - 1)) % MOD;

            if (t == s) {
                lp = (lp + lp)%MOD;
                lq = (lq + lq)%MOD;
            }
            
            p = (p + lp)%MOD; q = (q + lq)%MOD;
        }
    }

    //printf("%lld %lld\n", p, q);
    printf("%lld\n", (p * fexp(q, MOD-2))%MOD);
}
