#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

int t;
ll n, m, a, b;
ll res;
ll qtd;

ll gcd (ll a, ll b) {
    if (a == 0) return b;
    return gcd(b%a, a);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
        n -= a;
        m -= b;
        if (n < 0) n = -n;
        if (m < 0) m = -m;

        printf("%lld\n", gcd(n, m) + 1);
    }
}
