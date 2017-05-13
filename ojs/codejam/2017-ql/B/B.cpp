#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

int ts;
ll n;

ll go (ll n) {
    ll pot = 1;
    ll r = 0;
    ll bst = 9;
    while (n) {
        bst = min(bst, n%10);
        n /= 10;
        r += bst*pot;
        pot *= 10;
    }
    return r;
}

int main () {
    scanf("%d", &ts);

    for (int tt = 1; tt <= ts; tt++) {
        printf("Case #%d: ", tt);
        scanf("%lld", &n);

        ll pot = 1;
        ll r = go(n);

        while (pot > 0) {
            r = max(r, go(n));

            ll x = (n/pot)%10;
            if (x != 9)
                n -= (x + 1)*pot;
            pot *= 10;
        }

        printf("%lld\n", r);
    }
}

