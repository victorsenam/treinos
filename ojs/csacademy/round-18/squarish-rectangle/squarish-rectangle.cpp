#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

ll h, w;

int main () {
    scanf("%lld %lld", &h, &w);

    if (h > w) swap(h,w);

    ll a = h*w;
    ll res = INT_MAX;

    for (ll x = 1; x*x <= a; x++) {
        ll y = a/x;
        if (x*y != a) continue;
        //if (x == h) continue;
        
        //printf("%lld %lld : %lld\n", x, y, 2ll*abs(h+w-x-y));
        res = min(res, y-x);
    }
    printf("%lld\n", res);

}
