#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int ts;
int n;

const int N = 30;

ll r[N], t[N];
ll d[N], ls[N];

int solve (ll x) {
    for (int i = 0; i < 24; i++)
        ls[i] = d[i] = INT_MAX;
    d[24] = 0;

    bool mud = 0;

    for (int k = 0; k < 26; k++) {
        mud = 0;

        for (int i = 0; i <= 7; i++)
            d[16+i] = min(d[16+i], d[i] - r[i] + x);
        for (int i = 8; i < 24; i++)
            d[i-8] = min(d[i-8], d[i] - r[i]);

        d[0] = min(d[0], d[24] + t[0]);
        for (int i = 1; i < 24; i++)
            d[i] = min(d[i], d[i-1] + t[i]);


        d[23] = min(d[23], d[24] + x);
        d[24] = min(d[24], d[23] - x);

        for (int i = 0; i <= 24; i++) {
            if (ls[i] != d[i])
                mud = 1;
            ls[i] = d[i];
        }
    }

    return (!mud);
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        for (int i = 0; i < 24; i++) {
            scanf("%lld", &r[i]);
            t[i] = 0;
        }
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int a;
            scanf("%d", &a);
            t[a]++;
        }

        int lo = 0;
        int hi = q+1;

        while (lo < hi) {
            int mid = (lo+hi)/2;

            if (solve(mid))
                hi = mid;
            else
                lo = mid+1;
        }

        if (lo > q)
            printf("No Solution\n");
        else
            printf("%d\n", lo);
    }
}
