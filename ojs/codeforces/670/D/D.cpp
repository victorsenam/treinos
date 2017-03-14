#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

ll a[N], b[N], n, k;

int solve (ll qt) {
    ll m= k;
    for (int i = 0; i < n; i++) {
        m -= max(a[i]*qt - b[i], 0ll);    
        if (m < 0) return 0;
    }

    return 1;
}

int main () {
    scanf("%lld %lld", &n, &k);

    for (int i = 0; i< n; i++)
        scanf("%lld", a+i);

    for (int i = 0; i < n; i++)
        scanf("%lld", b+i);

    ll lo = 0;
    ll hi = INT_MAX-10;

    while (lo < hi) {
        ll mid = lo + (hi-lo+1)/2;

        if (solve(mid))
            lo = mid;
        else
            hi = mid-1;
    }

    printf("%lld\n", lo);
}
