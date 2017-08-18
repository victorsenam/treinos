#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 4e5+8;

int d[N];
vector<int> adj[N];
int edg[N+N];
int n, m;
vector<int> rs;
int vs[N];

int dfs (int u) {
	vs[u] = 1;

	int lst = (d[u] == 1);
	for (int ed : adj[u]) {
		int v = edg[ed];
		if (vs[v]) continue;
		int rt = dfs(v);

		if (rt) {
			rs.pb(ed/2);
			lst = !lst;
		}
	}

	return lst;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%d", &d[i]);

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		adj[a].pb(i+i);
		edg[i+i] = b;
		adj[b].pb(i+i+1);
		edg[i+i+1] = a;
	}

	if (dfs(0)) {
		bool ok = 0;
		for (int i = 0; i < n; i++) {
			vs[i] = 0;
			if (d[i] == -1 && !ok) {
				d[i] = 1;
				ok = 1;
			}
		}
		if (!ok) {
			printf("-1\n");
			return 0;
		}
		rs.clear();
		dfs(1);
	}

	printf("%d\n", (int) rs.size());
	for (int i : rs)
		printf("%d ", i+1);
	printf("\n");
}
