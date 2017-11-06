#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#define pb push_back
#define sz(a) ((int) (a).size())
using namespace std;
const int N = (int) 3e5;
vector<int> adj[N], who[N], bad[N], path, relax[N];
int n, u, v, root, ans[N], depth[N], h[N], used[N], value[N], it, tlmx[4 * N], trmx[4 * N];

void update(int t, int l, int r, int x, int y) {
	if (l == r - 1)
		tlmx[t] = y, trmx[t] = y + 1;
	else {
		int m = (l + r) / 2;
		if (x < m) update(t * 2 + 1, l, m, x, y);
		else update(t * 2 + 2, m, r, x, y);
		tlmx[t] = max(tlmx[t * 2 + 1], (m - l) + tlmx[t * 2 + 2]);
		trmx[t] = max(trmx[t * 2 + 2], trmx[t * 2 + 1] + (r - m));
	}
}

int get_right(int t, int l, int r, int who, int k) {
	if ((l > who) || (trmx[t] + who - r <= k)) return -1;
	if (l == r - 1) return l;
	int m = (l + r) / 2;
	int rvalue = get_right(t * 2 + 2, m, r, who, k);
	if (rvalue != -1) return rvalue;
	return get_right(t * 2 + 1, l, m, who, k);
}

void get_left(int t, int l, int r, int x, int k, int &lmx, int &res) {
	if (l >= x + 1) return;
	if (r <= x + 1) {
		if (max(tlmx[t], r - l + lmx) < k) {
			lmx = max(tlmx[t], r - l + lmx);
			return;
		} else if (l == r - 1) {
			res = l;
			return;
		}
	}
	int m = (l + r) / 2;
	get_left(t * 2 + 2, m, r, x, k, lmx, res);
	if (res == -1) get_left(t * 2 + 1, l, m, x, k, lmx, res);
}

void set_value(int depth, int nvalue) {
	update(0, 0, h[root] + 1, depth, nvalue);
	value[depth] = nvalue;
}

void update_answer(int k, int who) {
	int marked = get_right(0, 0, h[root] + 1, who, k), lmx = -1, res = -1;
	if (marked == -1) return;
	get_left(0, 0, h[root] + 1, marked, k, lmx, res);
	if (res == -1) res = 0;
	if (value[res] <= k) relax[path[res]].pb(k);
	else bad[path[res]][k] = max(bad[path[res]][k], lmx + 1);
}

void dfs(int v) {
	path.pb(v);
	int mx_u = -1, pre_mx_u = -1;
	for (int i = 0; i < sz(adj[v]); ++i) {
		int u = adj[v][i];
		if ((mx_u == -1) || (h[mx_u] < h[u])) pre_mx_u = mx_u, mx_u = u;
		else if ((pre_mx_u == -1) || (h[pre_mx_u] < h[u])) pre_mx_u = u;
	}
	bad[v] = vector<int>((pre_mx_u == -1) ? 1 : (1 + h[pre_mx_u]), 0);
	for (int i = 0; i < sz(adj[v]); ++i) {
		int u = adj[v][i];
		set_value(depth[v], (u == mx_u) ? ((pre_mx_u == -1) ? 0 : (h[pre_mx_u] + 1)) : (h[mx_u] + 1));
		dfs(u);
	}
	if (mx_u != -1) {
		who[v].swap(who[mx_u]), ++it;
		for (int i = 0; i < sz(adj[v]); ++i) {
			int u = adj[v][i];
			if (mx_u == u) continue;
			used[h[u] + 1] = it;
			for (int k = 0; k <= h[u]; ++k)
				who[v][k] = min(who[v][k], who[u][k]);
		}
		for (int k = 0, mx = 0; k <= ((pre_mx_u == -1) ? -1 : h[pre_mx_u]); ++k) {
			if (used[k] == it) mx = k;
			set_value(depth[v], max(mx, bad[v][k]));
			update_answer(k, who[v][k]);
		}
	}
	who[v].pb(depth[v]);
	set_value(depth[v], 0);
	relax[v].pb(h[v]);
	for (int i = 0; i < sz(relax[v]); ++i) {
		int k = relax[v][i];
		ans[k]++, who[v][k] = depth[v];
		update_answer(k, depth[v]);
	}
	path.pop_back();
}

void calc_h(int v, int p = -1) {
	for (int i = sz(adj[v]) - 1; i >= 0; --i) {
		int u = adj[v][i];
		if (u == p) {
			swap(adj[v][i], adj[v].back());
			adj[v].pop_back();
		} else {
			depth[u] = depth[v] + 1;
			calc_h(u, v);
			h[v] = max(h[v], h[u] + 1);
		}
	}
}

int main() {
	freopen("fulkerson.in", "r", stdin);
	freopen("fulkerson.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i + 1 < n; ++i) {
		scanf("%d%d", &u, &v), --u, --v;
		adj[u].pb(v), adj[v].pb(u);
	}
	root = 0;
	calc_h(root);
	dfs(root);
	for (int d = h[root] + 1; d <= n; ++d)
		ans[d] = 1;
	for (int k = 1, d = n; k <= n; ++k) {
		while ((d > 0) && (ans[d - 1] <= k)) --d;
		printf("%d%c", d, " \n"[k == n]);
	}
	return 0;
}
