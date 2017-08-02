#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int n, qs;
int tm[N], sz[N];
vector<int> adj[N];
int rs[N];

struct pareto {
    set<pii> s;
    
    ll get (ll x) {
        auto it = s.lower_bound(pii(x, LLONG_MIN));
        if (it == s.end())
            return LLONG_MAX;
        return it->second;
    }

    void insert (pii x) {
        if (get(x.first) >= x.second)
            return;

        auto it = s.upper_bound(pii(x, LLONG_MAX));
        while (it != s.begin() && prev(it).second <= x.second)
            s.erase(prev(it));
        s.insert(x);
    }
};

int getsz (int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || sz[v] == -1) continue;
        sz[u] += getsz(v, u);
    }
    return sz[u];
}

void cent (int u) {
    int siz = getsz(u, u);
    int w = u;
    do {
        u = w;
        for (int v : adj[u]) {
            if (sz[v] == -1 || sz[v] >= sz[u] || sz[v] + sz[v] < siz)
                continue;
            w = v;
            break;
        }
    } while (w != u);

    sz[u] = -1;
    
    pareto acc, cur;
    acc.insert(pii(tm[u], 0));
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> qs;

    n = 4;
    for (int i = 1; i < n; i++) {
        adj[0].pb(i);
        adj[i].pb(0);
    }

    for (int i = 1; i <= qs; i++) {
        int v;
        cin >> v;
        v--;

        tm[n] = tm[n+1] = i;
        adj[n].pb(v);
        adj[v].pb(n);
    }

    cent(0);
}
