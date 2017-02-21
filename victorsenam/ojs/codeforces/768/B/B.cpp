#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

ll sz[52][2];
ll memo[52];

ll siz (ll x, int k, int v) {
    if (x <= 1) return (x == v);
    if (sz[k][v] != -1)
        return sz[k][v];
    
    sz[k][v] = 2ll*(siz(x/2, k+1, v)) + ((x%2) == v);
    return sz[k][v];
}

ll get (ll x, int k, ll l, ll r) {
    ll ss = siz(x, k, 0) + siz(x, k, 1);
    if (l <= 0 && r+1 >= ss) {
        return siz(x, k, 1);
    }
    if (l >= ss || r < 0) {
        return 0;
    }
    if (x <= 1) {
        return (l <= 0) && (x == 1);
    }

    ll val = get(x/2, k+1, l, r);
    val += get(x/2, k+1, l-ss/2-1, r-ss/2-1);
    if (l <= ss/2 && r >= ss/2) {
        val += (x%2);
    }

    return val;
}

int main () {
    memset(sz, -1, sizeof sz);
    memset(memo, -1, sizeof memo);

    ll n;
    ll l, r;
    scanf("%lld %lld %lld", &n, &l, &r);


    printf("%lld\n", get(n, 0, l-1, r-1));
}
