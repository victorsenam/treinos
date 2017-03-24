#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+7;
const ll MOD = 1e9+7;

int ts, n;
ll a[N];
ll pr[2][N];
ll mn, mx;

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r = (r * a)%MOD;
        a = (a * a)%MOD;
        e >>= 1;
    }
    return r;
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);

        mn = 1e8;
        mx = 0;

        for (int i = 0; i < n; i++) {
            scanf("%lld ", &a[i]);
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }

        pr[0][n] = pr[1][n] = n;
        for (int i = n-1; i >= 0; i--) {
            for (int j = 0; j < 2; j++)
                pr[j][i] = pr[j][i+1];

            if (a[i] == mn)
                pr[0][i] = i;
            
            if (a[i] == mx)
                pr[1][i] = i;
        }

        ll res = 0;
        for (int i = 0; i < n; i++)
            res = (res + (ll(n - max(pr[0][i], pr[1][i]) + MOD)%MOD) )%MOD;

        printf("%lld ", res % MOD);
        
        res = 0;
        sort(a, a+n);
        if (a[0] == a[n-1]) {
            res = (fexp(2ll, n) + MOD - 1)%MOD;
            printf("%lld\n", res);
        } else {
            int x = 0, y = 0;
            while (a[0] == a[x]) x++;
            while (a[n-1] == a[n-1-y]) y++;
            
            res = fexp(2ll, n-x-y);
            res = (res * ((fexp(2ll, x) + MOD - 1)%MOD))%MOD;
            res = (res * ((fexp(2ll, y) + MOD - 1)%MOD))%MOD;
            printf("%lld\n", res);
        }
    }
}
