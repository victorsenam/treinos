#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n, k;
vector<int> adj[N];
ll cn[N];
int sz[N];

int getsiz (int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || sz[v] == -1)
            continue;
        sz[u] += getsiz(v,u);
    }
    return sz[u];
}

ll dfs (int u, int p, int d) {
    if (d > k) return 0;
    ll rs = cn[k-d];
    for (int v : adj[u]) {
        if (v == p || sz[v] == -1) continue;
        rs += dfs(v, u, d+1);
    }
    return rs;
}

void add (int u, int p, int d) {
    if (d > k) return;
    cn[d]++;
    for (int v : adj[u]) {
        if (v == p || sz[v] == -1) continue;
        add(v, u, d+1);
    }
}

ll cent (int u) {
    ll rs = 0;
    int siz = getsiz(u, u);

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
    for (int i = 0; i <= k; i++)
        cn[i] = 0;
    cn[0]++;

    for (int v : adj[u]) {
        if (sz[v] == -1) continue;
        rs += dfs(v, v, 1);
        add(v, v, 1);
    }

    for (int v : adj[u]) {
        if (sz[v] == -1) continue;
        rs += cent(v);
    }
    
    return rs;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);
    }

    cout << cent(0) << endl;
}
