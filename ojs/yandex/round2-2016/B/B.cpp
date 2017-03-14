#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

ll l, r;

int main () {
    scanf("%lld %lld", &l, &r);

    ll res = 0;

    for (int i = 0; (1ll<<i) <= r; i++) {
        ll one = 0;

        if (l&(1ll<<i)) {
            one += (1ll<<i) - (l&((1ll<<i)-1));
        } else {
            one += (l&((1ll<<i)-1));
        }

        if (r&(1ll<<i)) {
            one -= (1ll<<i) - (r&((1ll<<i)-1)) - 1;
        } else {
            one -= (r&((1ll<<i)-1)) + 1;
        }
        
        if (one > 0)
            res |= (1ll<<i);
    }

    printf("%lld\n", res);
}
