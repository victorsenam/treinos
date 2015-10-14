#include <bits/stdc++.h>
using namespace std;
#define pb push_back
vector<int> adj[10009];
int seen[10009], t;
int d[10009], low[10009], tempo;
int st[10009], sn;
bool pos;
void dfs(int u) {
	if(seen[u] == t) return;
	seen[u] = t;
	low[u] = d[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	if(low[u] == d[u]) {
		int x, sz = 0;
		do {
			x = st[--sn];
			low[x] = INT_MAX;
			sz++;
		} while(x != u);
		if(sz == 1) pos = false;
	}
}

int main() {
	int i, a, b, n, m;
	while(scanf("%d %d", &n, &m) != EOF) {
		t++; tempo = 0; sn = 0;
		for(i = 0; i < n; i++)
			adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			adj[a].pb(b);
		}
		pos = true;
		for(i = 0; i < n; i++)
			dfs(i);
		if(pos) puts("YES");
		else puts("NO");
	}
}
