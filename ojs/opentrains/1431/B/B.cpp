#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

ll x, y;
ll al = 8ll*7ll*9ll*5ll;
const ll mpd[] = {0, 1, 2, 3, 2, 5, 2, 7, 2, 3, 2, 131231};

map<pair<ll, ll>, ll> mp;
pair<ll, ll> aux;
ll ans;

inline ll divi (ll a, ll b) {
    return (a+b-1ll)/b;
}

ll calc (ll s) {
    return divi(al*(y+1ll)-s, al*x);
}

void brute (ll i, ll s, ll curr) {
    if (curr + (al*y - s)/(al*x) > ans)
        return;
    if (s >= al*(y+1ll))
        return;

    if (i > 1) {
       for (ll a = 0; a < mpd[i]; a++)
            brute(i-1, s + (a*x*al)/i, curr + a);
    } else if (i == 1) {
        ll a = calc(s);
        for (ll var = -2; var <= 2; var++) {
            if (a+var < 1) continue;
            if (s+(a+var)*x*al < al*y) continue;
            brute(i-1, s + (a+var)*x*al, curr + a+var);
        }
    } else {
        ans = min(ans, curr);
    }
}

int main () {
    ll res;
    while (scanf("%lld %lld", &x, &y) != EOF) {
        //y = rand()%ll(1e9);
        aux = make_pair(x, y);
        ans = 1e15;
        if (mp.count(aux)) res = mp[aux];
        else { 
            brute(x, 0, 0);
            res = ans;
        }
        if (ans == 1e15) printf("-1\n");
        else printf("%lld\n", res+x-2);
        mp[aux] = res;
    }
}
