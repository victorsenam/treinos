#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int ber[N];
int n;
vector<int> adj[N];
int res;
int tot;

int dp (int u, int p) {
	ber[u] = (u != p) && (adj[u].size() == 1);
	for (int v : adj[u]) if (v != p) ber[u] += dp(v,u);

	if (u != p) {
		res = max(res, min(ber[u], tot-ber[u]));
	}

	return ber[u];
}

int main () {
	scanf("%d", &n);
	for (int  i= 0 ;i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	for (int i = 1; i < n; i++) if (adj[i].size() == 1) tot++;
	dp(0,0);
	printf("%d\n", res);
}
