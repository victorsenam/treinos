#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

// const int N = 1e5+7;
const int N = 1e5+7;

int t;
ll n;
ll phi[N];
ll res[N];

int main () {
    phi[1] = 1;
    res[1] = 1;
    bool pri;
    for (ll i = 2; i < N; i++) {
        pri = 0;
        if (phi[i] == 0) {
            phi[i] = i-1;
            pri = 1;
        }
        res[i] = res[i-1] + phi[i];
        if (!pri) continue;
        for (ll j = i; j < N; j += i) {
            if (phi[j] == 0) 
                phi[j] = j;
            phi[j] -= phi[j]/i;
        }
    }

    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++) {
        scanf("%lld", &n);

        printf("Case %d: %lld\n", tc, n*(n+1)/2 - res[n]);
    }

}
