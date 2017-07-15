#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1123456;
vector<int> adj[N];
ll sz[N], sumd[N], sum[N];
ll ans[N];
int n;

int go(int u, int p) {
    if(u == -1) return 0;
    int mx = 1;
    for(int v : adj[u])
        if(v != p)
            mx = max<ll>(mx, go(v, u) + 1);
    return mx;
}

int back[N];

int dfs(int u, int p) {
    sz[u] = 1;
    int lst = n - 1, mx = -1;
    for(int v : adj[u])
        if(v != p) {
            sz[u] += dfs(v, u);
            lst -= sz[v];
            mx = max<ll>(mx, sz[v]);
            sumd[u] += sumd[v] + sz[v];
        }
    back[u] = lst;
    return sz[u];
}

void dfs2(int u, int p) {
    int mx = -1;
    if(u) sum[u] = sum[p] - sz[u] + back[u];
    else sum[u] = sumd[u];
    for(int v : adj[u])
        if(v != p) {
            dfs2(v, u);
            mx = max<ll>(mx, sz[v]);
        }
    int lst = back[u];
    mx = max(mx, lst);
    if(mx * 2 > n) return;
    ans[u] = 2ll * sum[u];
    if(mx * 2 == n) {
        if(lst * 2 == n) ans[u] -= go(p, u);
        else
            for(int v : adj[u])
                if(v != p && sz[v] == (n - 1) / 2 + 1)
                    ans[u] -= go(v, u);
    } else {
        int mx = 0;
        for(int v : adj[u])
            mx = max<ll>(mx, go(v, u));
        ans[u] -= mx;
    }
}



int main() {
    int i, a, b;
    memset(ans, -1, sizeof ans);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(i = 0; i < n - 1; i++) {
        cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(0, -1);
    dfs2(0, -1);
    for(i = 0; i < n; i++)
        printf("%lld\n", ans[i]);
}

