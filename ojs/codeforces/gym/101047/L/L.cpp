#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

int t;
ll l, d;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%lld %lld", &l, &d);
        if (l == d && !d) printf("0\n");
        else {
            ll res = 1ll;
            for (int i = 0; i < l; i++) res *= 26ll;
            for (int i = 0; i < d; i++) res *= 10ll;
            printf("%lld\n", res);
        }
    }
}
