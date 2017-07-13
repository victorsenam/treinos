#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define fst first
#define snd second
#define pb push_back
typedef long double ld;

const int NN = 1123456;
ll N;
vector<ll> dvs[NN];
vector<int> even[NN];
ll dv[NN];

ll leq(ll a, ll b, ld d) {
    ll tot = 0;
    for(int n = 1; n <= N; n++) {
        ll k;
        if(a != -1) k = ll((n * a) / b);
        else k = ll(d * n);
        tot += k;
        for(int i = 0; i < dvs[n].size(); i++)
            if(even[n][i])
                tot += ll(k / dvs[n][i]);
            else
                tot -= ll(k / dvs[n][i]);
    }
    return tot;
}

pii which(ll k) {
    ld l = 0, r = 1;
    for(int bb = 0; bb < 30; bb++) {
        ld m = (l + r) / 2.;
        if(leq(-1, -1, m) >= k) r = m;
        else l = m;
    }
    vector<pair<ld, pii>> pos;
    for(int n = 1; n <= N; n++) {
        ll k = ll(l * n);
        for(int g = k - 1; g <= k + 1; g++)
            if(g > 0 && g <= n)
                pos.pb(make_pair(abs(ld(g) / n - l), pii(g, n)));
    }
    sort(pos.begin(), pos.end());
    for(int i = 0; ; i++) {
        pii pq = pos[i].snd;
        if(leq(pq.fst, pq.snd, 0) == k)
            return pq;
    }
}

ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}

int main () {
    int op;
    for(ll i = 2; i < NN; i++)
        if(dv[i] == 0)
            for(ll j = i; j < NN; j += i)
                dv[j] = i;
    for(ll i = 2; i < NN; i++) {
        ll x = i;
        vector<int> ps;
        while(x != 1) {
            assert(dv[x]);
            ps.pb(dv[x]);
            ll dx = dv[x];
            while(x != 1 && !(x % dx)) x = x / dx;
        }
        int n = ps.size();
        for(int j = 0; j < (1 << n); j++) {
            ll v = 1;
            for(int k = 0; k < n; k++)
                if((j >> k) & 1)
                    v = v * ps[k];
            dvs[i].pb(v);
            even[i].pb((__builtin_popcount(j) & 1) == 0);
        }
    }
    while(true) {
        scanf("%d", &op);
        if(op == 2) break;
        ll n, a, b;
        ll x;
        if(op == 1) {
            scanf("%lld %lld %lld", &n, &a, &b);
            ll g = gcd(a, b);
            a /= g;
            b /= g;
            if(b > n || a > b) { puts("fail"); continue; }
            N = n;
            printf("%lld\n", leq(a, b, -1));
        } else {
            scanf("%lld %lld", &n, &x);
            N = n;
            if(leq(1, 1, -1) < x) { puts("fail"); continue; }
            pii pq = which(x);
            printf("%lld/%lld\n", pq.fst, pq.snd);
        }
    }
}
