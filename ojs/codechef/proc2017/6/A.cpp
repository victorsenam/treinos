#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e4+7;
int n;
ll c;
vector<pii> adj[N];
ll a[N];

ll dfs (int u, ll d, int p, ll lst) {
	ll res = 0;
	for (pii ed : adj[u]) {
		if (ed.first == p) continue;
		res += dfs(ed.first, d + ed.second, u, ed.second);
	}

	res += (a[u]/c)*d;
	a[u] %= c;
	if (u == p) res += d;
	else { res += lst*(a[u] != 0); a[p] += a[u]; }
	return res;
}

int main () {
	scanf("%d %lld", &n, &c);

	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);

	
	for (int i = 0; i < n-1; i++) {
		int x, y; ll l;
		scanf("%d %d %lld", &x, &y, &l);
		x--; y--;
		adj[x].pb(pii(y,l));
		adj[y].pb(pii(x,l));
	}

	printf("%lld\n", 2ll*dfs(0,0,0,0));
}
