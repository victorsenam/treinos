#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

const int N = 312;

int to[N];

struct graph {
	vector<int> adj[N];
	vector<int> nodes;
	void dfs(int);
};

vector<graph> gs;

int st[N], sn;
int cmp[N];
int low[N], d[N], t, tempo, seen[N];
void graph::dfs(int u) {
	st[sn++] = u;
	low[u] = d[u] = t++;
	seen[u] = tempo;
	for(int e : adj[u])
		if(seen[to[e]] == tempo) {
			low[u] = min(low[u], d[to[e]]);
		} else {
			dfs(to[e]);
			low[u] = min(low[u], low[to[e]]);
		}
	if(low[u] == d[u]) {
		graph g;
		int a = -1;
		while(a != u) {
			a = st[--sn];
			g.nodes.pb(a);
			d[a] = INT_MAX;
			cmp[a] = gs.size();
		}
		gs.pb(g);
	}
}


void solve(const graph &g) {
	for(int u : g.nodes) for(int ed : g.adj[u]) {
		//printf("try edge %d(%d->%d)\n", ed, u, to[ed]);
		graph h = g;
		h.adj[u].erase(search_n(h.adj[u].begin(), h.adj[u].end(), 1, ed));
		tempo++;
		gs.clear();
		h.dfs(to[ed]);
		reverse(gs.begin(), gs.end());
		int gn = gs.size(), i;
		//printf("%d components\n", gn);
		if(gn == 1) {
			printf("wheel 1\n");
			solve(h);
			printf("edge %d\n", ed);
			return;
		}
		vector<int> eds;
		for(i = 0; i < gn; i++) {
			graph &f = gs[i];
			int ed = 0, ct = 0;
			for(int u : f.nodes)
				for(int e : g.adj[u]) {
					if(cmp[to[e]] == cmp[u]) f.adj[u].pb(e);
					else if(cmp[to[e]] == ((cmp[u] + gn - 1) % gn)) ed = e, ct++;
					else ct = 10;
				}
			if(ct != 1) break;
			//printf("ok\n");
			eds.pb(ed);
		}
		if(i < gn) continue;
		printf("wheel %d\n", gn);
		vector<graph> gg = gs;
		for(i = 0; i < gn; i++) {
			solve(gg[i]);
			printf("edge %d\n", eds[i]);
		}
		return;
	}
	printf("vertex %d\n", g.nodes[0] + 1);
}


int main() {
#ifdef ONLINE_JUDGE
	freopen("wheels.in", "r", stdin);
	freopen("wheels.out", "w", stdout);
#endif

	int n, m, i;
	scanf("%d %d", &n, &m);
	graph g;
	for(i = 0; i < n; i++) g.nodes.pb(i);

	for (i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		g.adj[a].pb(i+1);
		to[i+1] = b;
	}

	solve(g);
}
