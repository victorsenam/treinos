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

        if (n == 0) {
            printf("%lld\n", m);
            continue;
        }
        if (m == 0) {
            printf("%lld\n", n);
            continue;
        }

        res = 0;

/*
        for (ll i = 2; i*i <= n && i*i <= m; i++) {
            qtd = 1;
            while (n%i == 0 && m%i == 0) {
                n /= i;
                m /= i;
                qtd++;
            }
            res *= qtd;
        }
        if (n > 1 && m%n == 0) res++;
        if (m > 1 && n%m == 0) res++;
*/

/*
        a = gcd(n, m);

        for (ll i = 2; i*i <= a; i++) {
            qtd = 1;
            while (a%i == 0) {
                a /= i;
                qtd++;
            }
            res *= qtd;
        }
        if (a > 1) res *= 2ll;
*/
        printf("%lld\n", res);
    }
}
