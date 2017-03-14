#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;

int t;
ll n;
int k;
ll f;
ll d;

ll gcd (ll a, ll b) {
    if (a == 0) return b;
    return gcd(b%a, a);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%lld", &n);
        scanf("%d", &k);

        for (int i = 0; i < k; i++) {
            scanf("%lld", &f);
            while ((d = gcd(n, f)) > 1)
                n /= d;
        }

        if (n == 1)
            printf("Y\n");
        else
            printf("N\n");
    }
}
