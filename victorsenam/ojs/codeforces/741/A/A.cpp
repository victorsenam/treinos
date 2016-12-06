#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 104;

int visi[N];
int n, m;
ll res;
int p[N];
int i;

void fail (){ 
    printf("-1\n");
    exit(0);
}

ll dfs (int u) {
    if (visi[u] == 2) fail();
    if (visi[u] == 1) {
        if (i == u) return 0;
        fail();
    }

    visi[u] = 1;

    ll ret = dfs(p[u])+1;

    visi[u] = 2;
    return ret;
}

ll gcd (ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

ll upd (ll a, ll b) {
    if (b%2 == 0) b /= 2;
    ll loc = gcd(a,b);
    return (a*b)/gcd(a,b);
}

int main () {
    scanf("%d", &n);

    res = 1;

    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }

    for (i = 0; i < n; i++) {
        if (visi[i] == 2) continue;
        ll loc = dfs(i);
        res = upd(res, loc);
    }

    printf("%lld\n", res);
}
