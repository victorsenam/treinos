#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define fst first
#define snd second

int main () {
    int i, n, m;
    ll x;
    scanf("%d", &n);
    vector<pii> v;
    for(i = 0; i < n; i++) {
        scanf("%lld", &x);
        ll l = (9ll * x + 9ll) / 10ll;
        ll r = (11ll * x) / 10ll;
        v.pb(pii(l, 1));
        v.pb(pii(r + 1, -1));
    }
    v.push_back(pii(0, 0));
    sort(v.begin(), v.end());
    for(i = 1; i < int(v.size()); i++)
        v[i].snd += v[i - 1].snd;
    scanf("%d", &m);
    for(i = 0; i < m; i++) {
        scanf("%lld", &x);
        printf("%lld\n", prev(upper_bound(v.begin(), v.end(), pii(x, LLONG_MAX)))->snd);
    }
}
