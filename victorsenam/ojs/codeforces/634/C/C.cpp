#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e6+7;

int n, q, k;
ll a[2];

struct bit {
    ll v[N];

    void add (int i, ll x) {
        for (i += 2; i < N; i+=(i&-i))
            v[i] += x;
    }

    ll get (int i) {
        ll x = 0;
        for (i += 2; i > 0; i-=(i&-i))
            x += v[i];
        return x;
    }
} acc[2];

int main () {
    scanf("%d", &n);
    scanf("%d", &k);
    for (int j = 0; j < 2; j++)
        scanf("%lld", &a[j]);
    scanf("%d", &q);

    while (q--) {
        int ty;
        int d;
        ll x;
        scanf("%d %d", &ty, &d);

        if (ty == 1) {
            scanf("%lld", &x);
            for (int j = 0; j < 2; j++) {
                ll val = acc[j].get(d) - acc[j].get(d-1);
                acc[j].add(d, min(x+val, a[j]) - val);
            }
        } else {
            printf("%lld\n", acc[0].get(n) - acc[0].get(d+k-1) + acc[1].get(d-1));
        }
    }
}
