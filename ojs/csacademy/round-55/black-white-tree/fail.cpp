#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e4+7;

int n, m;
int cl[N];
vector<int> adj[N];

int cn_sz[N];
int cn_dep[N]; // depth on cent tree
int cn_dist[20][N]; // distance to centroid antecessor with given depth
int cn_par[N];
vector<int> cn_adj[N];

ll cn_sum[2][N];
ll cn_sum_p[2][N];
ll cn_qt[2][N];

int cn_getsz (int u, int p) {
	cn_sz[u] = 1;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_sz[u] += cn_getsz(v,u);
	}
	return cn_sz[u];
}

void cn_setdist (int u, int p, int depth, int dist, int root) {
	cn_dist[depth][u] = dist;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_setdist(v, u, depth, dist+1, root);
	}
}

int cn_build (int u, int depth) {
	int siz = cn_getsz(u,u);
	int w = u;
	do {
		u = w;
		for (int v : adj[u]) {
			if (cn_sz[v] == -1 || cn_sz[v] >= cn_sz[u] || cn_sz[v] + cn_sz[v] < siz)
				continue;
			w = v;
		}
	} while (u != w);

	cn_setdist(u,u,depth,0,u);
	cn_sz[u] = -1;
	cn_dep[u] = depth;

	for (int v : adj[u]) {
		if (cn_sz[v] == -1) continue;
		int w = cn_build(v, depth+1);
		cn_par[w] = u;
	}
	return u;
}

void toggle (int u, int x = -1) {
	if (x == -1)
		x = !cl[u];
	int root = u;
	while (root != -1) {
		if (cl[u]!= -1) {
			cn_sum[cl[u]][root] -= cn_dist[cn_dep[root]][u];
			cn_qt[cl[u]][root]--;
		}

		cn_sum[x][root] += cn_dist[cn_dep[root]][u];
		cn_qt[x][root]++;

		int pr = cn_par[root];
		
		if (pr != -1) {
			if (cl[u] != -1)
				cn_sum_p[cl[u]][root] -= cn_dist[cn_dep[pr]][u];
			cn_sum_p[x][root] += cn_dist[cn_dep[pr]][u];
		}

		root = cn_par[root];
	}
	cl[u] = x;
}

ll get (int u) {
	int root = u;

	ll ls_qt = 0;
	ll ls_sm = 0;
	ll res = 0;
	ll dis = 0;
	
	while (root != -1) {
		dis = cn_dist[cn_dep[root]][u];
		ll cur = cn_sum[cl[u]][root] - ls_sm;
		ll qtd = cn_qt[cl[u]][root] - ls_qt;

		res += cur + qtd*dis;

		ls_sm = cn_sum_p[cl[u]][root];
		ls_qt = qtd;

		root = cn_par[root];
	}

	return res;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%d", &cl[i]);
	}

	for (int i = 0; i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	int rt = cn_build(0,0);
	cn_par[rt] = -1;
	cn_sum_p[0][rt] = cn_sum_p[1][rt] = 0;

	for (int i = 0; i < n; i++) {
		int x = cl[i];
		cl[i] = -1;
		toggle(i, x);
	}

	for (int i = 0; i < m; i++) {
		int t, v;
		scanf("%d %d", &t, &v);
		v--;

		if (t == 1) { // toggle
			toggle(v);		
		} else {
			printf("%lld\n", get(v));
		}
	}
}
