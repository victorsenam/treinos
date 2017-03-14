#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const ll M = 1e16;

int n;
ll k;

map<ll, ll> mp;

int main () {
    scanf("%d", &n);
    scanf("%lld", &k);

    mp[0] = 1;
    ll acc = 0;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll a;
        scanf("%lld", &a);

        acc += a;

        if (k == 1) {
            res += mp[acc-1];
        } else if (k == -1) {
            res += mp[acc-1] + mp[acc+1];
        } else {
            for (ll pt = 1; pt <= M; pt *= k) {
                res += mp[acc-pt];
            }
        }

        mp[acc]++;
    }

    printf("%lld\n", res);
}
