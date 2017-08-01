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
ll tot, rs;
ll inv, md;
int sz[N], vs;
pii v[N];

ll phi (ll n) {
    ll x = n;
    for (ll i = 2; i*i <= x; i++) {
        if (x%i != 0) continue;
        n /= i;
        n *= (i-1);
        while (x%i == 0)
            x /= i;
    }
    if (x != 1) {
        n /= x;
        n *= (x - 1);
    }
    return n;
}

inline ll mod (ll x) {
    return x%m;
}

inline ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r = mod(a*r);
        a = mod(a*a);
        e >>= 1;
    }
    return r;
}

inline ll c_inv (ll x) {
    return fexp(x,tot-1);
}

inline ll get (ll x, int u) {
    rs += upper_bound(v, v+vs, pii(x,N)) - upper_bound(v, v+vs, pii(x,u)) + lower_bound(v, v+vs, pii(x,u)) - lower_bound(v, v+vs, pii(x,0));
}

void dfs (int u, int p, int x, ll ac, ll ml, int root) {
    v[vs++] = pii(ac, root);
    
    for (edge & ed : adj[u]) {
        if (ed.to == p || sz[ed.to] == -1) continue;
        dfs(ed.to, u, x, mod(ac + ml*ed.w), mod(ml*10), root);
    }
}

void go (int u, int p, ll ac, ll ml, int root) {
    ll x = mod((m-ac)*ml);
    get(x, root);

    for (edge & ed : adj[u]) {
        if (ed.to == p || sz[ed.to] == -1) continue;
        go(ed.to, u, mod(ac*10 + ed.w), mod(ml*inv), root);
    }
}

int getsz (int u, int p) {
    sz[u] = 1;
    for (edge & ed : adj[u]) {
        if (ed.to == p || sz[ed.to] == -1) continue;
        sz[u] += getsz(ed.to, u);
    }
    return sz[u];
}

void centroid (int u) {
    int siz = getsz(u,u);
    
    int w = u;
    do {
        u = w;
        for (edge & ed : adj[u]) {
            int v = ed.to;
            if (sz[v] == -1 || sz[v] >= sz[u] || sz[v] + sz[v] <= siz) continue;
            w = v;
            break;
        }
    } while (u != w);

    sz[u] = -1;

    vs = 0;
    for (edge & ed : adj[u]) {
        if (sz[ed.to] == -1) continue;
        dfs(ed.to, ed.to, 1, ed.w, md, ed.to);
    }
    v[vs++] = pii(0,u);
    sort(v,v+vs);

    get(0,u);
    for (edge & ed : adj[u]) {
        int v = ed.to;
        if (sz[v] == -1) continue;
        go(v, v, ed.w, inv, ed.to);
    }
    for (edge & ed : adj[u]) {
        if (sz[ed.to] == -1) continue;
        centroid(ed.to);
    }
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

    centroid(0);
    cout << rs << endl;
}
