#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 8e5+7;
const ll MOD = 1e9+7;

int n;
ll v[N], sg[N];
int lm[N][2];
ll pd[N];
ll ac[N];
int pr[N];

ll calc (ll a, ll b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return __gcd(a,b);
}

void build (int u, int l, int r) {
    lm[u][0] = l; lm[u][1] = r;
    if (l == r) 
        sg[u] = v[l];
    else {
        build(2*u, l, (l+r)/2);
        build(2*u+1, (l+r)/2+1, r);
        sg[u] = calc(sg[2*u], sg[2*u+1]);
    }
}

ll get (int u, int l, int r) {
    if (lm[u][0] > r || l > lm[u][1])
        return -1;      
    if (l <= lm[u][0] && lm[u][1] <= r)
        return sg[u];

    return calc(get(2*u, l, r), get(2*u+1, l, r));
}

int main () {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
    }

    build(1, 1, n);

    ll res = 0;
    if (get(1, 1, n) != 1) {
        res = 1;
        for (int i = 1; i <= n; i++)
            res = (res * 2ll)%MOD;
        printf("%lld\n", (res-n+MOD)%MOD);
        return 0;
    }

    while (v[1] != 1) {
        //printf("=== %lld ===\n", v[1]);
        build(1, 1, n);

        int l = 0;
        for (int i = 1; i <= n; i++) {
            while (l < i && get(1, l+1, i) == 1)
                l++;
            pr[i] = l;
            //printf("%d ", pr[i]);
        }
        //printf("\n");

        pd[0] = 0;
        ac[0] = 0;
        //printf("1 ");
        for (int i = 1; i <= n; i++) {
            if (pr[i])
                pd[i] = (ac[i-1] - ac[pr[i]-1] + MOD)%MOD;
            else
                pd[i] = (ac[i-1] + 1)%MOD;
            //printf("%lld ", pd[i]);
            ac[i] = (ac[i-1] + pd[i])%MOD;
        }
        //printf("\n");

        ll ls = v[1];
        while (v[1] != 1 && v[1] == ls) {
            res = (res + pd[n])%MOD;
            v[1] = __gcd(v[1], v[n]);
            n--;
        }
    }

    printf("%lld\n", res);
}
