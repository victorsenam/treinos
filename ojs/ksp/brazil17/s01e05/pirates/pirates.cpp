#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

vector<ll> all;
vector<ll> dvs;

void gen(int i, int mx, ll x, ll dv) {
    all.pb(x);
    dvs.pb(dv);
    ll cur = 0;
    while(!(x >= ULLONG_MAX / p[i]) && ++cur <= mx) {
        x *= p[i];
        gen(i + 1, cur, x, dv * (cur + 1ll));
    }
}

int main () {
    int i;
    gen(0, INT_MAX, 1, 1);
    ll n;
    scanf("%llu", &n);
    ll mx = 0;
    for(i = 0; i < int(all.size()); i++)
        if(all[i] <= n)
            mx = max<ll>(mx, dvs[i]);
    ll mn = ULLONG_MAX;
    for(i = 0; i < int(all.size()); i++)
        if(dvs[i] > mx)
            mn = min<ll>(mn, all[i]);
    printf("%llu\n", mn);
}

