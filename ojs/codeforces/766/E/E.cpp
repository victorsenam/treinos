#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n;
vector<int> adj[N];
ll x[N][60], a[N];
ll qt[N];

ll dfs (int u, int p) {
    ll rs = 0;
    for (int i = 0; i < 60; i++)
        rs += x[u][i]*(1ll<<i);
    
    for (int v : adj[u]) {
        if (v == p) continue;
        rs += dfs(v, u);

        for (int i = 0; i < 60; i++) {
            rs += x[u][i]*(qt[v] - x[v][i])*(1ll<<i);
            rs += x[v][i]*(qt[u] - x[u][i])*(1ll<<i);

            if (a[u]&(1ll<<i))
                x[u][i] += qt[v] - x[v][i];
            else
                x[u][i] += x[v][i];
        }

        qt[u] += qt[v];
    }

    return rs;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < 60; j++)
            x[i][j] = !!(a[i]&(1ll<<j));
        qt[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);
    }
    
    cout << dfs(0,0) << endl;
}
