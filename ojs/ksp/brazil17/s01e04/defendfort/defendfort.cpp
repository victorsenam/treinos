#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define k first
#define a second

int main () {
    int n, d, i, a, k;
    scanf("%d %d", &n, &d);
    multiset<pii> s;
    ll tot = 0;
    for(i = 0; i < n; i++) {
        scanf("%d %d", &a, &k);
        s.insert(pii(k, a));
        tot += a;
    }
    while(d > 0 && !s.empty()) {
        pii x = *s.rbegin(); s.erase(s.find(x));
        ll tm = min<ll>(d, x.a / x.k);
        d -= tm;
        x.a -= tm * x.k;
        tot -= tm * x.k;
        if(x.a) s.insert(pii(min(x.a, x.k), x.a));
    }
    printf("%lld\n", tot);
}
