#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e4;
const int M = 5e3;

int ord[N], os;
int n;
vector<int> adj[N];
int deg[N];
int hd[M], nx[N];
bitset<M> tra[M];
int fr[N], to[N], es;
int memo[N];

int dfs (int u) {
	for (int ed = hd[u]; ed; ed = nx[ed]) {
		ord[os++] = ed;
		deg[to[ed]]--;
		if (deg[to[ed]] == 0)
			dfs(to[ed]);
	}
}

int main () {
	scanf("%d", &n);

	es++;
	for (int i = 0; i < n-1; i++) {
		int k;
		scanf("%d", &k);
		while (k--) {
			int a;
			scanf("%d", &a);
			a--;
			fr[es] = i;
			to[es] = a;
			nx[es] = hd[i]; 
			hd[i] = es++;
			deg[a]++;
		}
		tra[i][i] = 1;
	}

	dfs(0);

	int res = 0;
	for (int _i = os - 1; _i >= 0; _i--) {
		int u = ord[_i];
		tra[fr[u]] |= tra[to[u]];
		int & mx = memo[u];
		mx = 1;
		for (int _j = _i + 1; _j < os; _j++) {
			int i = ord[_j];
			if (!tra[to[u]][fr[i]])
				mx = max(mx, memo[i] + 1);
		}

		res = max(mx, res);
	}
	printf("%d\n", res);
}
