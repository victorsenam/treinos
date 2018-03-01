#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
int n, m;
vector<int> adj[N];
int fr[N][2];
int vs[N];

int dfs (int u, bool t, int frm) {
	if (fr[u][t] != -1) return -1;
	fr[u][t] = frm;
	if (t && adj[u].empty()) return u;
	for (int v : adj[u]) {
		int w = dfs(v,!t,u);
		if (w != -1) return w;
	}
	return -1;
}

int cic (int u) {
	if (vs[u] == 1) return 1;
	if (vs[u] == 2) return 0;
	vs[u] = 1;
	for (int v : adj[u]) if (cic(v)) return 1;
	vs[u] = 2;
	return 0;
}

int main () {
	memset(fr, -1, sizeof fr);
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		int s;
		scanf("%d", &s);
		while (s--) {
			int a;
			scanf("%d", &a);
			a--;
			adj[i].pb(a);
		}
	}

	int st;
	scanf("%d", &st);
	st--;

	int v = dfs(st,0,st);

	if (v != -1) {
		stack<int> res;
		bool t = 1;
		while (v != st) { res.push(v); v = fr[v][t]; t = !t; }
		res.push(st);

		printf("Win\n");
		while (res.size()) { printf("%d ", res.top()+1); res.pop(); }
		printf("\n");
	} else if (cic(st)) {
		printf("Draw\n");
	} else {
		printf("Lose\n");
	}
}
