#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e5+7;
const int K = 21;

struct node {
	int l, r;
	ll v;
	int ch_l, ch_r;
};

vector<node> seg;

int build (int l, int r) {
	int u = seg.size();
	seg.pb(node({ l, r, 0, 0, 0 }));
	if (l < r) {
		int md = (l+r)/2;
		seg[u].ch_l = build(l, md);
		seg[u].ch_r = build(md+1,r);
	}
	return u;
}

ll get (int u, int l, int r) {
	if (r < seg[u].l || seg[u].r < l) return 0;
	if (l <= seg[u].l && seg[u].r <= r) return seg[u].v;
	return get(seg[u].ch_l, l, r) + get(seg[u].ch_r, l, r);
}

int put (int u, int i) {
	if (seg[u].l > i || seg[u].r < i) return u;
	seg.pb(seg[u]);
	u = seg.size() - 1;
	seg[u].v++;
	int ll, rr;
	if (seg[u].l < seg[u].r) {
		seg[u].ch_l = put(seg[u].ch_l, i);
		seg[u].ch_r = put(seg[u].ch_r, i);
	}
	return u;
}

int w[N];
int dpt[N];
int visi[N];
int anc[N][K];
int root[N];
vector<int> adj[N];

void dfs (int u, int su, int p) {
	if (visi[u]) return;
	visi[u] = 1;
	dpt[u] = dpt[p] + 1;
	anc[u][0] = p;
	for (int i = 1; i < K; i++)
		anc[u][i] = anc[anc[u][i-1]][i-1];

	root[u] = put(su, w[u]);
	int x = get(root[u], 1, 5);
	for (int v : adj[u])
		dfs(v, root[u], u);
}

int lca (int u, int v) {
	if (dpt[u] < dpt[v]) swap(u,v);

	for (int k = K-1; k >= 0; k--) {
		if (dpt[anc[u][k]] >= dpt[v])
			u = anc[u][k];
	}

	for (int k = K-1; k >= 0; k--) {
		if (anc[u][k] != anc[v][k]) {
			u = anc[u][k];
			v = anc[v][k];
		}
	}

	if (u == v) return u;
	return anc[u][0];
}

ll solve (int r, int a, int b, int l) {
	ll x = get(root[a], 1, r) + get(root[b], 1, r) - get(root[l], 1, r);
	if (l) x -= get(root[anc[l][0]], 1, r);
	return x;
}

int main () {
	int n, q;
	seg.pb(node({0,0,0,0,0}));
	int rr = build(1, N);

	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++)
		scanf("%d", &w[i]);

	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;

		adj[u].pb(v);
		adj[v].pb(u);
	}

	dpt[0] = 0;
	dfs(0, rr, 0);

	for (int qq = 0; qq < q; qq++) {
		int k, a, b;
		scanf("%d %d %d", &k, &a, &b);
		a--; b--;
	
		int l = lca(a,b);	

		int lo = 1, hi = N;
		while (lo < hi) {
			int md = (lo + hi)/2;

			if (solve(md, a, b, l) >= k)
				hi = md;
			else
				lo = md + 1;
		}

		printf("%d\n", lo);
	}
}
