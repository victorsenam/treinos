//#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
#define pb push_back

const int N = 1e5+7;
const int M = 6e5+7;
const int K = 22;

int n, m;
int hd[N], ht[N], nx[M], to[M], es;
int lca[N][K];
int acc[N];
int vs[N];
int pre[N], ord;
int dp[N];
ll res;

int dfs (int u, int p) {
	pre[u] = ord++;
	
	int acc = 0;

	for (int ed = hd[u]; ed; ed = nx[ed]) if (to[ed] != p) {
		int loc = dfs(to[ed],u);
		if (loc == 0) res += m;
		else if (loc == 1) res++;
		acc += loc;
	}

	for (int ed = ht[u]; ed; ed = nx[ed]) {
		int v = to[ed];
		if (pre[v] > pre[u]) acc--;
		else acc++;
	}
	return acc;
}

int buildlca (int u, int p) {
	if (u == 1) { dp[u] = 0; for (int k = 0; k < K; k++) lca[u][k] = u; }
	else { dp[u] = dp[p]+1; for (int k = 0; k < K; k++) lca[u][k] = k?lca[lca[u][k-1]][k-1]:p; }
	for (int ed = hd[u]; ed; ed = nx[ed]) if (to[ed] != p) buildlca(to[ed],u);
}

int getlca (int u, int v) {
	//return u;
	if (dp[u] < dp[v]) swap(u,v);
	for (int k = K-1; k >= 0; k--) if (dp[lca[u][k]] >= dp[v]) u = lca[u][k];
	for (int k = K-1; k >= 0; k--) if (lca[u][k] != lca[v][k]) { u = lca[u][k]; v = lca[v][k]; }
	if (u != v) return lca[u][0];
	return u;
}

int main () {
	scanf("%d %d", &n, &m);

	ord = 2;
	es = 2;
	for (int i = 1; i < n + m; i++) {
		if (i == n) buildlca(1,0);
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == b) continue;
		if (i < n) {
			nx[es] = hd[a]; to[es] = b; hd[a] = es++;
			nx[es] = hd[b]; to[es] = a; hd[b] = es++;
		} else {
			int c = getlca(a,b);
			if (a != c) {
				nx[es] = ht[a]; to[es] = c; ht[a] = es++;
				nx[es] = ht[c]; to[es] = a; ht[c] = es++;
			}
			if (c != b) {
				nx[es] = ht[b]; to[es] = c; ht[b] = es++;
				nx[es] = ht[c]; to[es] = b; ht[c] = es++;
			}
		}
	}

	dfs(1,0);
	printf("%lld\n", res);
}
