#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct Graph {
    int n;
    vector<vector<int> > adj;
    vector<int> sz;

    void centroid (Graph & c) {
        c.adj.resize(n);
        sz.resize(n);

        centroid(c,0,1);
    }

    int getsz (int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v == p || sz[v] < 0) continue;
            sz[u] += getsz(v,u);
        }
        return sz[u];
    }

    int centroid (Graph & c, int u, int dpt) {
        int siz = getsz(u,u);
        while (true) {
            int w = u;
            for (int v : adj[u]) {
                if (sz[v] < 0 || sz[v] >= sz[u]) continue;
                if (w == u || sz[v] > sz[w])
                    w = v;
            }

            if (w == u || sz[w] + sz[w] < siz)
                break;
            u = w;
        }

        sz[u] = -dpt;

        for (int v : adj[u]) {
            if (sz[v] < 0) continue;
            c.adj[u].pb(centroid(c,v, dpt+1));
        }
    }
};

Graph g, c;
int n;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> g.n;
    n = g.n;
    g.adj.resize(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g.adj[a].pb(b);
        g.adj[b].pb(a);
    }

    g.centroid(c);

    for (int i = 0; i < n; i++)
        cout << char('A'-g.sz[i]-1) << " ";
    cout << endl;
}
