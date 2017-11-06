#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
const int K = 20;

int n, m;
int cl[N], inp[N];
vector<int> adj[N];
int lca[N][K];
int dept[N];

ll init[N];
ll res[N];
pii dw[N];

void calc_lca (int u, int p, int dp) {
	lca[u][0] = p;
	for (int k = 1; k < K; k++)
		lca[u][k] = lca[lca[u][k-1]][k-1];
	dept[u] = dp;
	for (int v : adj[u]) {
		if (v == p) continue;
		calc_lca(v,u,dp+1);
	}
}

pii dfs (int u, int p) {
	dw[u].first = dw[u].second = 0;
	for (int v : adj[u]) {
		if (v == p) continue;
		pii ret = dfs(v, u);
		dw[u].first += ret.first + ret.second;
		dw[u].second += ret.second;
	}
	dw[u].second += cl[u];
	return dw[u];
}

void go (int u, int p, ll sm, ll qt) {
	res[u] = dw[u].first + sm;
	for (int v : adj[u]) {
		go(v, u, sm + qt + dw[u].first - dw[v].first - dw[v].second, qt + dw[u].second - dw[v].second);
	}
}

int dist (int u, int v) {
	cout << "[" <<  u << " and " << v << " lca = ";
	int res = dept[u] + dept[v];
	if (dept[u] < dept[v]) swap(u,v);

	for (int k = K; k >= 0; k--) {
		if (dept[lca[u][k]] >= dept[v])
			u = lca[u][k];
	}
	for (int k = K; k >= 0; k--) {
		if (lca[u][k] != lca[v][k])
			u = lca[u][k]; v = lca[v][k];
	}
	if (u != v)
		u = lca[u][0];
	cout << u << "]";
	res -= 2*(dept[u] - 1);
	return res;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%d", &inp[i]);
		cl[i] = 1;
	}

	for (int i = 0; i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	for (int i = 0; i < K; i++)
		lca[0][i] = 0;
	calc_lca(0,0,0);
	dfs(0,0); go(0,0,0,0);
	for (int i = 0; i < n; i++) {
		init[i] = res[i];
		cout << init[i] << " ";
		cl[i] = inp[i];
	}
	cout << endl;
	dfs(0,0); go(0,0,0,0);

	set<int> qr;
	for (int i = 0; i < m; i++) {
		int t, v;
		scanf("%d %d", &t, &v);
		v--;
		if (t == 1) {
			if (qr.find(v) == qr.end())
				qr.insert(v);
			else
				qr.erase(v);
		} else {
			if (qr.size() > 100) {
				for (int x : qr)
					cl[x] = !cl[x];
				dfs(0,0); go(0,0,0,0);
				qr.clear();
			}
			
			ll qt = res[v];
			cout << "to whites " << qt;
			for (int x : qr) {
				if (cl[x]) {
					qt -= dist(v,x);
					cout << " -"  << dist(v,x);
				} else {
					qt += dist(v,x);
					cout << " +"  << dist(v,x);
				}
			}
			if ((!cl[v]) ^ (qr.find(v) != qr.end())) {
				cout << " compl " << init[v];
				qt = init[v] - qt;
			}
			cout << endl;
			printf("%lld\n", qt);
		}
	}
}
