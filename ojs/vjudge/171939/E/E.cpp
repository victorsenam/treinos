#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e6;

int n, q;
int c[N];
vector<int> adj[N];
int p[N], d[N];
int pre[N], pos[N], cn;
int rs[N];

void dfs (int u, int w, int dd) {
    p[u] = w;
    d[u] = dd;
    pre[u] = cn++;
    rs[u] ^= c[u];
    for (int v : adj[u]) {
        if (v == w)
            continue;
        dfs(v, u, !dd);

        rs[u] ^= rs[v];
    }
    pos[u] = cn++;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> c[i];
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        adj[a].pb(b);
        adj[b].pb(a);
    }

    cn = 0;
    dfs(0,0,0);

    int acc = 0;
    for (int i = 0; i < n; i++)
        if (d[i] == 1)
            acc ^= c[i];

    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        
        if ((pre[u] <= pre[v] && pos[v] <= pos[u])) {
            cout << "INVALID" << endl;
        } else {
            int cr = acc;
            if (d[u] == d[v])
                cr ^= (rs[u]);
            if (cr)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}
