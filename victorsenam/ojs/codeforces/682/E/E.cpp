#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#define lld I64d
#endif

const int N = 5007;

ll x[N], y[N];
int n;
ll s;
int maxi[2];

ll sq (ll x) {
    return x*x;
}

ll dist (int i, int j) {
    return sq(x[j]-x[i]) + sq(y[j]-y[i]);
}

int main () {
    scanf("%d %lld", &n, &s);

    ll gen = 0ll;

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", x+i, y+i);

        for (int j = 0; j < i; j++) {
            ll loc = dist(i, j);
            if (loc > gen) {
                maxi[0] = i;
                maxi[1] = j;
                gen = loc;
            }
        }
    }

    for (int 
}
