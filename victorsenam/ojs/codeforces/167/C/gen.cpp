#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

int main () {
    ll n;
    scanf(LLD, &n);
    printf(LLD "\n", n*(n+1)/2);
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j++) {
            printf(LLD " " LLD "\n", i, j);
        }
    }
}
