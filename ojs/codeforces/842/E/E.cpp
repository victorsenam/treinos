#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;

int n;
vector<int> adj[N];
int p[N][20];
int op[N], cl[N], ord;
int res;
int lf[4*N], rg[4*N], sg[4*N], lz[4*N];
int dp[N];

int dfs (int u, int dep) {
	op[u] = ord++;
	dp[u] = dep;
	for (int v : adj[u])
		dfs(v, dep+1);
	cl[u] = ord;
}

void build (int u, int l, int r) {
	lf[u] = l; rg[u] = r; sg[u] = 0; lz[u] = 0;
	if (l == r)
		return;
	
	int md = (l+r)/2;
	build(u+u, l, md);
	build(u+u+1, md+1, r);
}

void upd (int u) {
	if (lz[u] == 1) {
		sg[u] = 0;
	}

	if (lf[u] != rg[u]) {
		lz[u+u] = 1;
		lz[u+u+1] = 1;
		lz[u] = 0;
	}
}

void cle (int u, int l, int r) {
	upd(u);
	if (l > rg[u] || r < lf[u])
		return;
	if (l <= lf[u] && rg[u] <= r) {
		res -= sg[u];
		lz[u] = 1;
	}
	cle(u+u, l, r);
	cle(u+u+1, l, r);
}

void add (int u, int i) {
	upd(u);
	if (i < lf[u] || i > rg[u])
		return;
	sg[u]++;
	add(u+u, i);
	add(u+u+1, i);
}

int findlcap (int u, int v) {
	for (int k = 20; k >= 0; k--) {
		if (dp[p[u][k]] > dp[v])
			u = p[u][k];
	}
	if (p[u][0] == v)
		return u;
	u = p[u][0];

	for (int k = 20; k >= 0; k--) {
		if (p[u][k] != p[v][k]) {
			u = p[u][k];
			v = p[v][k];
		}
	}
	return u;
}

int getdist (int u, int v) {
	int d = 0;
	for (int k = 20; k >= 0; k--) {
		if (dp[p[u][k]] >= dp[v]) {
			u = p[u][k];
			d += (1<<k);
		}
	}
	for (int k = 20; k >= 0; k--) {
		if (p[u][k] != p[v][k]) {
			u = p[u][k];
			v = p[v][k];
			d += (1<<(k+1));
		}
	}

	if (u != v)
		d+=2;
	return d;
}

int main () {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i][0]);
		p[i][0]--;
		adj[p[i][0]].pb(i);

		for (int k = 1; k < 20; k++)
			p[i][k] = p[p[i][k-1]][k-1];
	}

	dfs(0,0);
	build(1, 0, cl[0]-1);

	int x = 0;
	int a = 0, b = 0;
	for (int i = 1; i <= n; i++) {
		if (p[i][0] == b) swap(a,b);
		if (p[i][0] == a) {
			int v = findlcap(i,b);
			cle(1, op[v], cl[v]-1);
			add(1, op[i]);
			x = getdist(i,b);
		} else {
			int d = max(getdist(i,a), getdist(i,b));
			if (d == x)
				add(1, op[i]);
		}

		printf("%d\n", sg[1]);
	}
}
