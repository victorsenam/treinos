#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e4+7;

int n;
vector<int> adj[N];
int qt;
vector<int> res;
int visi[N];

void dfs (int u) {
	while (!adj[u].empty()) {
		int v = adj[u].back();
		adj[u].pop_back();
		dfs(v);
		res.pb(u);
	}
}

int main () {
	scanf("%d", &n);

	qt = 0;
	for (int i = 0; i < n; i++) {
		int m;
		scanf("%d", &m);
		qt += m;

		int ls, a;
		scanf("%d", &ls);
		ls--;
		for (int j = 0; j < m; j++) {
			scanf("%d", &a);
			a--;
			adj[ls].pb(a);
			ls = a;
		}
	}

	dfs(0);

	if (res.size() != qt)
		res.clear();

	printf("%d\n", (int) res.size());
	reverse(res.begin(), res.end());
	for (int u : res)
		printf("%d ", u+1);
	printf("1\n");
}
