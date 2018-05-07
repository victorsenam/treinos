#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5;

int n, m;
vector<int> adj[N];
bool visi[N], inPath[N];
int ts;

bool dfs (int u) {
	visi[u] = inPath[u] = true;
	for (int v : adj[u]) {
		if (inPath[v]) return true;
		if (!visi[v] && dfs(v)) return true;
	}
	inPath[u] = false;
	return false;
}

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			visi[i] = false;
			inPath[i] = false;
		}
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--; b--;
			adj[a].pb(b);
		}
		bool ok = false;
		for (int i = 0; !ok && i < n; i++)
			if (dfs(i))
				ok = true;
		printf("%s\n", ok?"SIM":"NAO");
	}
}
