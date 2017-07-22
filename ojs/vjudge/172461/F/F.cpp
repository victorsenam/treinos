#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll a[112345];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll h, i, n;
    cin >> n >> h;
    for(i = 0; i < n; i++)
        cin >> a[i];
    ll des = h;
    ll has = 0;
    for(i = 0; i < n; i++) {
        has += a[i % n];
        des -= ll(i + 1);
        if(has >= des) {
            cout << (i + 1) << '\n';
            return 0;
        }
    }
    ll sum = accumulate(a, a + n, 0ll);
    ll pre = 0;
    ll mn = LLONG_MAX;
    for(i = 0; i < n; i++) {
        pre += a[i];
        ll l = 1, r = ll(2.5e9) / ll(n);
        while(l < r) {
            ll k = (l + r) / 2;
            has = pre + sum * k;
            des = h - ((i + k * n + 1ll) * (i + k * n + 2ll)) / 2ll;
            if(has >= des) r = k;
            else l = k + 1;
        }
        mn = min(mn, i + 1ll + l * n);
    }
    cout << mn << '\n';
}
