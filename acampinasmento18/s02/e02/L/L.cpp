#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

ll sum[N];
ll sq[N];
ll siz[N];
vector<int> adj[N];
int n;
ll res;

ll memo[N];

ll dfs (int u, int p) {
	siz[u] = 1;
	for (int v : adj[u]) if (v != p) {
		ll s = dfs(v,u);
		sq[u] += s*s;
		sum[u] += s;
		siz[u] += s;
	}
	return siz[u];
}

ll dp (int u, int p) {
	ll & me = memo[u];
	if (me != -1) return me;
	me = sum[u]*sum[u] - sq[u] + siz[u];
	for (int v : adj[u]) if (v != p) {
		me += dp(v,u);
	}
	return me;
}

void go (int u, int p, ll upw, ll sz) {
	ll cost_ord = (sum[u] + sz)*(sum[u] + sz) - (sq[u] + sz*sz);
	ll cost_rec = upw;
	for (int v : adj[u]) if (v != p) cost_rec += dp(v,u);
	res = min(res, cost_rec + cost_ord);

	for (int v : adj[u]) if (v != p) {
		ll loc = (sum[u] + sz - siz[v])*(sum[u] + sz - siz[v]) - (sq[u] + sz*sz - siz[v]*siz[v]);
		loc += cost_rec - dp(v,u) + siz[u] - siz[v] + sz;
		go(v, u, loc, n - siz[v]);
	}
}

int main () {
	scanf("%d", &n);
	res = LLONG_MAX;
	memset(memo, -1, sizeof memo);

	for (int i = 0; i < n- 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}

	dfs(0,-1);
	go(0,-1,0,0);
	printf("%lld\n", res);
}
