#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

int to[N], nx[N], head[N];
int low[N], d[N], tempo;
int n, m;
int es, vis[N], st[N], instack[N], id[N], ps, comp, deg[N];

void dfs (int u) {
	vis[u] = 1;	
	low[u] = d[u] = tempo++;
	st[ps++] = u;
	instack[u] = 1;
	for(int e = head[u]; e; e = nx[e]) {
		int v = to[e];
		if(!vis[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (instack[v]) low[u] = min(low[u], d[v]);
	} 
	if(low[u] == d[u]) {
		int v;
		do {
			v = st[--ps];
			instack[v] = 0;
			id[v] = comp;
		} while (v != u);	
		comp++;
	}
}

int main() {
	es = 2;
	scanf("%d %d",&n, &m);	
	for(int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d",&u, &v); u--; v--;
		to[es] = v; nx[es] = head[u]; head[u] = es++;
	}
	for(int i = 0; i < n; i++) if(!vis[i]) dfs(i);

	for (int u = 0; u < n; u++) {
		for(int e = head[u]; e; e = nx[e]) {
			int v = to[e];	
			if(id[u] != id[v]) deg[id[v]]++;
		}	
	}
	int ans = 0;
	for(int i = 0; i < comp; i++) if(!deg[i]) ans++;
	printf("%d\n",ans);
}
