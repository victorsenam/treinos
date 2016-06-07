#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

map<pair<ll, ll>, bool> mp;

bool pd (ll a, ll b) {
    if (a > b) swap(a,b);
    if (a == 0) return 0;
    pair<ll, ll> pp(a,b);
    if (mp.find(pp) != mp.end())
        return mp[pp];

    int me = 0;
    if (!pd(a, b%a)) me = 1;
    ll r = a;

    if (!me) {
        if (r <= b)
            me = !pd(a, b-r);
        while (r*a <= b) r *= a;
        if (r <= b)
            me = !pd(a, b-r);
    }

    mp[pp] = me;
    return me;
}

int main () {
    int t;
    scanf("%d", &t);
    while (t--) {
        ll a, b;
        scanf(LLD LLD, &a, &b);
        printf("%d : %lld : %lld %lld\n", pd(a, b), b%a, a, b);
    }
}
