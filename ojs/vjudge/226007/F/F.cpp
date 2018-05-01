#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;
const int K = 22;

struct edge {
	int u, v; ll w; int i;
	bool operator < (const edge & o) const { return (w != o.w)?w < o.w:i < o.i; }
} ed[N];

ostream & operator << (ostream & os, edge o) { cout << "(" << o.u << " " << o.v << "| " << o.w << " " << o.i << ")"; }

int ts, n, m;
vector<int> adj[N];
vector<int> ins[N], rem[N];
int lv[N], pr[N][K];
ll res[N];
int uf[N];
bool usd[N];
set<edge> s;
ll cost;

int find (int u) {
	if (uf[u] > 0) return u;
	return -(uf[u] = -find(-uf[u]));
}

bool join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) return false;
	if (uf[u] < uf[v]) swap(u,v);
	uf[u] += uf[v];
	uf[v] = -u;
	return true;
}

int dfs (int u, int p) {
	lv[u] = lv[p] + 1;
	pr[u][0] = p;
	for (int k = 1; k < K; k++) pr[u][k] = pr[pr[u][k-1]][k-1];
	for (int e : adj[u]) for (int v : {ed[e].u, ed[e].v}) if (v != p && v != u)
		dfs(v,u);
}

void go (int u, int p) {
	for (int e : rem[u]) { s.erase(ed[e]); }
	for (int e : adj[u]) for (int v : {ed[e].u, ed[e].v}) if (v != p && v != u) {
		for (int t : ins[v]) { s.insert(ed[t]); }
		if (s.size()) res[e] = cost - ed[e].w + s.begin()->w;
		go(v, u);
	}
}

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d %d", &n, &m);

		for (int i = 0; i <= n; i++) {
			uf[i] = 1;
			adj[i].clear();
			ins[i].clear();
			rem[i].clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d %lld", &ed[i].u, &ed[i].v, &ed[i].w);
			ed[i].i = i;
		}
		sort(ed, ed+m);
		cost = 0;
		for (int i = 0; i < m; i++) {
			if (usd[ed[i].i] = join(ed[i].u, ed[i].v)) {
				cost += ed[i].w;
				adj[ed[i].u].pb(ed[i].i);
				adj[ed[i].v].pb(ed[i].i);
			}
		}
		dfs(1,0);
		for (int i = 0; i < m; i++) {
			if (usd[ed[i].i]) res[ed[i].i] = -1;
			else {
				int a = ed[i].u, b = ed[i].v;
				if (lv[a] < lv[b]) swap(a,b);
				for (int k = K-1; k >= 0; k--) if (lv[pr[a][k]] > lv[b])
					a = pr[a][k];
				assert(a != b);
				if (pr[a][0] == b) {
					ins[a].pb(ed[i].i);
					if (b != ed[i].u) rem[ed[i].u].pb(ed[i].i);
					if (b != ed[i].v) rem[ed[i].v].pb(ed[i].i);
					continue;
				}
				if (lv[a] > lv[b]) a = pr[a][0];
				for (int k = K-1; k >= 0; k--) if (pr[a][k] != pr[b][k])
				{ a = pr[a][k]; b = pr[b][k]; }
				ins[a].pb(ed[i].i);
				ins[b].pb(ed[i].i);
				rem[ed[i].u].pb(ed[i].i);
				rem[ed[i].v].pb(ed[i].i);
			}
		}
		s.clear();
		go(1,0);
		for (int i = 0; i < m; i++) {
			if (usd[i]) printf("%lld\n", res[i]);
			else printf("%lld\n", cost);
		}
	}
}
