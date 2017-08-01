#include <bits/stdc++.h>
#define debug if (0)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

struct edge {
    int to, w;
};

vector<edge> adj[N];
int n;
ll m;
ll tot;
ll inv, md;
int sz[N];

ll phi (ll n) {
    ll tot = 1;
    ll x = n;
    for (ll i = 2; i*i <= x; i++) {
        if (x%i == 0)
            tot *= (n - n/i);
        while (x%i == 0)
            x /= i;
    }
    if (x != 1)
        tot *= (n - n/x);
    return tot;
}

ll mod (ll x) {
    return x%m;
}

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r = mod(a*r);
        a = mod(a*a);
        e >>= 1;
    }
    return r;
}

ll c_inv (ll x) {
    return fexp(x,tot-1);
}

void dfs (map<ll,ll> & mp, int u, int p, int x, ll ac, ll ml) {
    debug cout << u << " mp[" << ac << "] += " << x << endl;
    mp[ac] += x;
    
    for (edge ed : adj[u]) {
        if (ed.to == p || sz[ed.to] == -1) continue;
        dfs(mp, ed.to, u, x, mod(ac + ml*ed.w), mod(ml*10));
    }
}

ll go (map<ll,ll> & lc, map<ll,ll> & mp, int u, int p, ll ac, ll ml) {
    ll x = mod((m-ac)*ml);
    debug cout << u << " rs += mp[" << x << "] = " << mp[x] << endl;
    ll rs = mp[x]-lc[x];

    for (edge ed : adj[u]) {
        if (ed.to == p || sz[ed.to] == -1) continue;
        rs += go(lc, mp, ed.to, u, mod(ac*10 + ed.w), mod(ml*inv));
    }

    return rs;
}

int getsz (int u, int p) {
    sz[u] = 1;
    for (edge ed : adj[u]) {
        if (ed.to == p || sz[ed.to] == -1) continue;
        sz[u] += getsz(ed.to, u);
    }
    return sz[u];
}

ll centroid (int u) {
    int siz = getsz(u,u);
    ll rs = 0;
    
    int w = u;
    do {
        u = w;
        for (edge ed : adj[u]) {
            int v = ed.to;
            if (sz[v] == -1 || sz[v] >= sz[u]) continue;
            if (w == u || sz[v] > sz[w])
                w = v;
        }
    } while (w != u && sz[w] + sz[w] >= siz);

    sz[u] = -1;

    debug cout << "==== for node " << u << " ===== " << endl;
    map<ll, ll> mp;
    for (edge ed : adj[u]) {
        if (sz[ed.to] == -1) continue;
        dfs(mp, ed.to, ed.to, 1, ed.w, md);
    }
    rs += mp[0];
    mp[0]++;
    for (edge ed : adj[u]) {
        map<ll,ll> lc;
        int v = ed.to;
        if (sz[v] == -1) continue;
        debug cout << "---- from " << v << " ----- " << endl;
        dfs(lc, v, v, 1, ed.w, md);
        rs += go(lc, mp, v, v, ed.w, inv);
    }
    for (edge ed : adj[u]) {
        if (sz[ed.to] == -1) continue;
        rs += centroid(ed.to);
    }
    return rs;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    tot = phi(m);
    md = mod(10);
    inv = c_inv(10);

    for (int i = 0; i < n-1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        w = mod(w);

        adj[a].pb({b,w});
        adj[b].pb({a,w});
    }

    cout << centroid(0) << endl;
}
