#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

// const int N = 1e5+7;
const int N = 10;

int t;
ll n;
ll res;
ll phi[N];


int main () {
    for (ll i = 2; i < N; i++) {
        if (phi[i] != 0) {
            DEBUG("%lld -> %lld\n", i, phi[i]);
            continue;
        }
        phi[i] = i-1;
        DEBUG("%lld -> %lld\n", i, phi[i]);
        ll ls = 1;
        ll a = i;
        for (ll j = i; j < N; j += i) {
            if (phi[j] == 0) phi[j] = 1;
            if (j%(a*i) == 0) {
                ls = a;
                a *= i;
            }
            phi[j] *= (a-ls);
        }

    }

    scanf("%d", &t);

    while (t--) {
        scanf("%lld", &n);

        res = n*n;
        for (int i = 2; i <= n; i++)
            res -= phi[i];
    }

}
