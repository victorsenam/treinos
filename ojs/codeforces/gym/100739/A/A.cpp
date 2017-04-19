#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 5e5+7;

int n, m;
ll a, b, t;
ll seg[N][2][11]; // 0: suff, 1: prefi
ll sum[N];
ll res[N];
ll lm[N][2];

vector<int> qr;

void printa (int u) {
    debug("%lld[%lld,%lld] : sum %lld, res %lld", u, lm[u][0], lm[u][1], sum[u], res[u]);
    debug(" suff:");
    for (int i = 0; i < 11; i++)
        debug(" %lld", seg[u][0][i]);
    debug(" pref:");
    for (int i = 0; i < 11; i++)
        debug(" %lld", seg[u][1][i]);
    debug("\n");
}

void build (int u, int l, int r) {
    lm[u][0] = l; lm[u][1] = r;
    if (l == r) return;
    int md = (l+r)/2;
    build(2*u, l, md);
    build(2*u+1, md+1, r);
}

void join (int u, int a, int b) {
    sum[u] = (sum[a] ^ sum[b]);
    res[u] = res[a] + res[b];
    lm[u][0] = lm[a][0];
    lm[u][1] = lm[b][1];

    for (int i = 0; i < 11; i++) {
        seg[u][0][i] = seg[b][0][i];
        if (sum[b]&(1u<<i))
            seg[u][0][i] += (lm[a][1] - lm[a][0] + 1) - seg[a][0][i];
        else
            seg[u][0][i] += seg[a][0][i];

        seg[u][1][i] = seg[a][1][i];
        if (sum[a]&(1u<<i))
            seg[u][1][i] += (lm[b][1] - lm[b][0] + 1) - seg[b][1][i];
        else
            seg[u][1][i] += seg[b][1][i];

        res[u] += (lm[a][1] - lm[a][0] + 1 - seg[a][0][i])*seg[b][1][i]*ll(1ll<<i);
        res[u] += (lm[b][1] - lm[b][0] + 1 - seg[b][1][i])*seg[a][0][i]*ll(1ll<<i);
    }
}

void get (int u, int l, int r) {
    if (l <= lm[u][0] && lm[u][1] <= r) {
        qr.push_back(u);
    } else if (l > lm[u][1] || r < lm[u][0]) {
        return;
    } else {
        get(2*u, l, r);
        get(2*u+1, l, r);
    }
}

ll get (int l, int r) {
    qr.clear();
    get(1, l, r);

    //debug("Query [%lld,%lld]\n", l, r);
    //for (int i : qr)
        //printa(i);

    if (qr.size() <= 1)
        return res[qr[0]];

    join(N-1, qr[0], qr[1]);
    for (int i = 2; i < qr.size(); i++)
        join(N-1-!(i&1), N-1-(i&1), qr[i]);
    return res[N-1-(qr.size()&1)];
}

ll put (int u, int p, int x) {
    if (lm[u][0] == p && lm[u][0] == lm[u][1]) {
        sum[u] = x;
        res[u] = x;
        for (int i = 0; i < 11; i++)
            seg[u][0][i] = seg[u][1][i] = !!(x&(1u<<i));
    } else if (lm[u][0] <= p && p <= lm[u][1]) {
        put(2*u, p, x);
        put(2*u+1, p, x);
        join(u, 2*u, 2*u+1);
    }

    return sum[u];
}

int main () {
    scanf("%d %d", &n, &m);

    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        ll v;
        scanf("%lld", &v);
        put(1, i, v);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lld %lld %lld", &t, &a, &b);

        if (t == 1)
            put(1, a, b);
        else
            printf("%lld\n", get(a, b)%4001);
    }
}
