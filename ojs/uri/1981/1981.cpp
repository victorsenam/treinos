#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const ll MOD = 1e8+7;
const int N = 1e4+6;

ll f[700];
char str[N];
ll ft[N], ift[N];

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (r * a)%MOD;
        a = (a * a)%MOD;
        e >>= 1;
    }
    return r;
}

int main () {
    ft[0] = 1;
    for (ll i = 1; i < N; i++)
        ft[i] = (ft[i-1]*i)%MOD;
    ift[N-1] = fexp(ft[N-1], MOD-2);
    for (ll i = N-2; i >= 0; i--)
        ift[i] = (ift[i+1]*(i+1))%MOD;

    while (scanf(" %s", str) != EOF) {
        if (str[0] == '0') break;
        for (char c = 'a'; c <= 'z'; c++)
            f[c] = 0;

        int n = 0;
        for (n = 0; str[n]; n++)
            f[str[n]]++;
        
        ll res = ft[n];
        for (char c = 'a'; c <= 'z'; c++)
            if (f[c])
                res = (res * ift[f[c]])%MOD;       
        printf("%lld\n", res);
    }
}
