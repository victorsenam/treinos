#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;
ll n;
ll a[N];


int main () {
    scanf("%lld", &n);


    for (int i = 0; i < n; i++) {
        scanf("%lld", a+i);
    }

    ll x = 1;
    bool ok = 0;
    while (!ok) {
        x++;
        ok = 1;
        for (int i = 0; ok && i < n; i++)
            ok = !!(a[i]%x);
    }
    printf("%lld\n", x);
}
