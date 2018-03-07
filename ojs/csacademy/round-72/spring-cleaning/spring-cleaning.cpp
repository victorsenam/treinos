#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int vs[N];
int ind[N];
vector<int> adj[N];

void dfs (int u) {
	vs[u] = 1;
	for (int v : adj[u]) { if (!vs[v]) { dfs(v); printf("%d %d\n", u+1,v+1); } }
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int p;
		scanf("%d",&p);
		p--;
		adj[i].pb(p);
		ind[p]++;
	}
	
	for (int i = 0; i < n; i++) if (!vs[i] && ind[i] == 0) dfs(i);
	for (int i = 0; i < n; i++) if (!vs[i]) dfs(i);
}
