#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll, ll> pll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

map<pll, ll> mp;
int n;
int t;
ll w;
ll a, b;

bool begeq (ll a, ll b) {
    while ((b^a) > a)
        b /= 2;
    return b == a;
}

int main () {
    scanf("%d", &n);

    while (n--) {
        scanf("%d %lld %lld", &t, &a, &b);
        if (t == 1)
            scanf("%lld", &w);
        else
            w = 0;

        if (a > b) swap(a,b);

        while (!begeq(a, b)) {
            ll nw = a/2;
            
            if (t == 1)
                mp[pll(nw,a)] += w;
            else
                w += mp[pll(nw,a)];

            a = nw;
        }

        while (a != b) {
            ll nw = a*2;
            if (!begeq(nw, b))
                nw++;

            if (t == 1)
                mp[pll(a,nw)] += w;
            else
                w += mp[pll(a,nw)];
            a = nw;
        }
        if (t == 2)
            printf("%lld\n", w);
    }
}
