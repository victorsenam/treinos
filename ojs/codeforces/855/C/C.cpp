#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
const int X = 13;
const ll MOD = 1e9+7;

inline ll mod (ll x) {
	return x%MOD;
}

ll memo[N][X][4];
int hd[N], nx[N], to[N], es;
int n;
vector<int> adj[N];
ll m, k, x;

ll pd (int ed, int x, int can) {
	if (ed == 0)
		return (x == 0);
	
	ll & me = memo[ed][x][can];
	if (me != -1)
		return me;
	
	me = 0;
	for (int c = 0; c <= x; c++) {
		me = mod(me + mod(mod((k-1)*pd(hd[to[ed]], c, 1)) * pd(nx[ed], x-c, can)));
		if (can != 2)
			me = mod(me + mod(mod((m-k)*pd(hd[to[ed]], c, 0)) * pd(nx[ed], x-c, can)));
		if (c && can == 1)
			me = mod(me + mod(pd(hd[to[ed]], c-1, 2) * pd(nx[ed], x-c, can)));
	}
	return me;
}

int dfs (int u, int p) {
	for (int v : adj[u]) {
		if (v != p) {
			nx[es] = hd[u]; to[es] = v; hd[u] = es++;
			dfs(v, u);
		}
	}
}

int main () {
	memset(memo, -1, sizeof memo);
	es = 2;
	scanf("%d %lld", &n, &m);

	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	scanf("%lld %lld", &k, &x);

	dfs(0,0);
	to[1] = 0;
	nx[1] = 0;
	ll res = 0;
	for (int c = 0; c <= x; c++)
		res = mod(res + pd(1,c,1));
	printf("%lld\n", res);
}
