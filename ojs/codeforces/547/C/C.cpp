#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 5e5 + 7;

int sieve[N];
int rr[8], rs;
int n, qs;
int q[N];
int v[N];
int b[N];

int main () {
    for (ll i = 2; i < N; i++) {
        if (sieve[i]) continue;
        for (ll j = i; j < N; j += i)
            sieve[j] = i;
    }

    scanf("%d %d", &n, &qs);

    ll res = 0;
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    for (int i = 0; i < qs; i++) {
        int j;
        scanf("%d", &j);
        j--;
        
        int a = v[j];

        rs = 0;
        while (a > 1) {
            if (!rs || rr[rs-1] != sieve[a]) {
                rr[rs++] = sieve[a];
            }
            a /= sieve[a];
        }
        
        for (int msk = 0; msk < (1 << rs); msk++) {
            ll vl = 1;
            for (int k = 0; k < rs; k++)
                if (msk&(1<<k))
                    vl *= rr[k];


            if (b[j]) {
                q[vl]--;
            }

            ll s = q[vl];
            if (b[j] ^ (__builtin_popcount(msk)&1)) {
                s = -s;
            }

            if (!b[j]) {
                q[vl]++;
            }
            res += s;
        }

        b[j] = !b[j];

        printf("%lld\n", res);
    }
}
