#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200007;
const ll MOD = 1e9+7;

ll fexp (ll a, ll e) {
    ll r = 1ll;
    while (e) {
        if (e&1) r = (r*a)%MOD;
        a = (a*a)%MOD;
        e >>= 1;
    }
    return r;
}

ll p[N];
ll q[N];
ll acc[2][N];
int n;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%lld", p+i);
    sort(p, p+n);

    int ls = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] != p[i-!!i]) ls++;
        p[ls] = p[i];
        q[ls]++;
    }
    ls++;

    acc[0][0] = 1ll;
    for (int i = 0; i < ls; i++)
        acc[0][i+1] = (acc[0][i]*(q[i]+1))%(MOD-1);

    acc[1][ls] = 1ll;
    for (int i = ls-1; i >= 0; i--)
        acc[1][i] = (acc[1][i+1]*(q[i]+1))%(MOD-1);

    ll res = 1;
    for (int i = 0; i < ls; i++)
        res = (res*fexp(p[i], (((q[i]*(q[i]+1)/2)%(MOD-1))*((acc[0][i]*acc[1][i+1])%(MOD-1)))%(MOD-1)))%MOD;

    printf("%lld\n", res);
}
