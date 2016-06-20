#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

ll a[4];
ll l, r;
ll n;
ll res;

int main () {
    scanf("%lld", &n);
    for (int k = 0; k < 4; k++)
        scanf("%lld", a+k);
    swap(a[2], a[3]);

    l = 1;
    r = 5*n;
    for (int k = 0; k < 4; k++) {
        l = max(l, a[k] + a[(k+1)%4] + 1);
        r = min(r, a[k] + a[(k+1)%4] + n);
    }


    res += max(0ll, r-l+1);

    printf("%lld\n", n*res);
}
