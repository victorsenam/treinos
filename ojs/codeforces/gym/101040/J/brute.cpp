#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 6e5;

ll n, k;
vector<int> ch[N];
ll pr[N], wg[N], dh[N];

int dfs (int u) {
    for (int v : ch[u]) {
        dh[v] = dh[u]+1;
        dfs(v);
    }
}

ll res (int u, int v) {
    ll d = 0;
    ll r = 0;

    while (u != v) {
        if (dh[u] >= dh[v]) {
            d++;
            r += wg[u];
            u = pr[u];
        } else if (dh[v] >= dh[u]) {
            d++;
            r += wg[v];
            v = pr[v];
        }
    }

    if (d == k) return r;
    return LLONG_MAX;
}

int main () {
    scanf("%lld %lld", &n, &k);

    for (int i = 1; i < n; i++) {
        scanf("%lld %lld", pr+i, wg+i);
        pr[i]--;
        ch[pr[i]].push_back(i);
    }

    dh[0] = 0;
    dfs(0);

    ll ans = LLONG_MAX;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans = min(ans, res(i,j));

    if (ans == LLONG_MAX) ans = -1;
    printf("%lld\n", ans);

}
