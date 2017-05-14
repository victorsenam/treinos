#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, a;

ll solve (ll x) {
    ll s = 0;
    ll ra = x;
    ll rb = n - x;
    if (ra%500)
        s += 500 - (ra%500);
    if (rb%500)
        s += 500 - (rb%500);
    return s;
}

int main () {
    scanf("%lld %lld", &n, &a);

    ll s = 0;
    for (ll x = a; x + a <= n && x <= a + 1000; x++)
        s = max(s, solve(x));
    printf("%lld\n", s);
}
