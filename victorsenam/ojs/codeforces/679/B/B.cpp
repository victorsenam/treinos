#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const int M = 20;

int cnt;
ll i;
ll m;
ll x;
ll v[N];
int n;

int visi[N][M];
ll memo[N][M];

ll cube (ll x) {
    return x*x*x;
}

ll pd (ll x, int i) {
    if (i == 0)
        return 0;
    if (cube(x) > m)
        return m+1;
    
    ll & me = memo[x][i];
    if (visi[x][i])
        return me;
    visi[x][i] = 1;

    me = 0;
    ll loc = pd(x+1, i);
    if (loc <= m)
        me = max(loc, me);
    
    loc = pd(x, i-1) + cube(x);
    if (loc <= m)
        me = max(loc, me);

    DEBUG("(%lld,%d) = %lld\n", x, i, me);
    return me;
}

ll solve (ll mid, int cnt) {
    ll x = 0;
    ll cur = 0;
    ll ceil = cube(mid+1);
    DEBUG("mid %lld\n", mid);
    while (cnt > 0 && mid > 0) {
        if (mid > 1 && x + cube(mid) > ceil) {
            ceil = min(ceil, cube(mid) + x);
            mid--;
        } else {
            x += cube(mid);
            DEBUG("%lld ", cube(mid));
            cnt--;
        }
    }
    DEBUG("%lld\n", x);
    return x;
}

int main () {
    scanf("%lld", &m);

    x = 0;
    i = 1;
    n = 0;

    while (x + cube(i) <= m) {
        if (cube(i+1) <= x+cube(i)) {
            i++;
        } else {
            v[n++] = i;
            x += cube(i);
            cnt++;
        }
    }

    printf("%d ", cnt);

    ll part = x;

    for (int i = n-1; i >= 0; i--) {
        part -= cube(v[i]);
        if (x - cube(v[i]) + cube(v[i]+1) <= m && part + cube(v[i]+1)  <= cube(v[i]+2)) {
            x += cube(v[i]+1) - cube(v[i]);
            v[i]++;
            i++;
            part += cube(v[i]+1);
        }
    }

    printf("%lld\n", x);
}
