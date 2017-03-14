#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int t;
ll r, c;
ll a[3];

bool go (ll r, ll c, int p) {
    if (p == 3) return (r == 0 || c == 0);
    if (r <= 0 || c <= 0) return 0;

    bool res = 0;
    if (a[p] >= r && a[p]%r == 0)
        res = go(r, c-(a[p]/r), p+1);
    if (!res && a[p] >= c && a[p]%c == 0)
        res = go(r-(a[p]/c), c, p+1);
    return res;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%lld %lld", &r, &c);

        for (int i = 0; i < 3; i++)
            scanf("%lld", a+i);
        sort(a, a+3);

        bool res = 0;
        do {
            res = go(r, c, 0);
        } while (!res && next_permutation(a, a+3));
        if (res)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
