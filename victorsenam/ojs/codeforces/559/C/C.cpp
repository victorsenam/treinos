#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e3+7;
const ll MOD = 1e9+7;
const int M = 2e5+7;

ll h, w;
int n;
ll v[N][2];

ll fat[M], ift[M];

ll memo[N];
int visi[N];

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (r * a)%MOD;
        a = (a * a)%MOD;
        e >>= 1;
    }
    return r;
}

ll ways (ll a, ll b) {
    if (a < 0 || b < 0 || (!a && !b)) return 0;
    return (fat[a+b] * ((ift[a] * ift[b])%MOD))%MOD;
}

ll pd (int i) {
    ll & me = memo[i];
    if (visi[i]) return me;
    visi[i] = 1;

    me = ways(h - v[i][0], w - v[i][1]);
    for (int j = 0; j <= n; j++) {
        ll loc = ways(v[j][0] - v[i][0], v[j][1] - v[i][1]);
        if (!loc) continue;
        loc = (loc * pd(j))%MOD;
        me = ((me-loc)%MOD + MOD)%MOD;
    }

    return me;
}

int main () {
    fat[0] = 1;
    for (ll i = 1; i < M; i++) {
        fat[i] = (fat[i-1] * i)%MOD;
    }
    ift[M-1] = fexp(fat[M-1], MOD-2);
    for (ll i = M-2; i >= 0; i--) {
        ift[i] = (ift[i+1] * (i+1))%MOD;
    }

    scanf("%lld %lld %d", &h, &w, &n);

    v[0][0] = v[0][1] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%lld %lld", &v[i][0], &v[i][1]);

    printf("%lld\n", pd(0));
}
