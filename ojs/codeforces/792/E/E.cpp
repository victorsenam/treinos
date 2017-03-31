#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 5e3;

int n;
ll a[N];

ll solve (ll x) {
    if (x < 0) return 1e14;
    ll k = 0;
    if (!x) {
        for (int i = 0; i < n; i++)
            k += a[i];
        return k;
    }
    for (int i = 0; i < n; i++) { 
        ll loc = a[i];
        bool ok = 0;
        ll q = (a[i]+x)/(x+1);
        ll r = q*(x+1) - a[i];
        if (r <= q) {
            ok = 1;
            loc = min(loc, q);
        }

        q = a[i]/x;
        r = a[i] - q*x;
        if (r <= q) {
            ok = 1;
            loc = min(loc, q);
        }

        if (!ok)
            return 1e14;
        k += loc;
    }
    return k;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    ll res = 1e14;
    for (ll x = 1; x <= 1e4; x++)
        res = min(res, solve(x));

    for (ll s = 1; s <= 1e4; s++) {
        res = min(res, solve(a[0]/s - 1));
        res = min(res, solve(a[0]/s));
        res = min(res, solve(a[0]/s + 1));
    }
    
    printf("%lld\n", res);
}
