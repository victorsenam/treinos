#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 312345;
int sz[N];
vector<int> adj[N];
int getsz(int u, int p) {
	sz[u] = 1;
	for(int v : adj[u]) {
		if(p == v || sz[v] == -1) continue;
		sz[u] += getsz(v, u);
	}
	return sz[u];
}

ll subtree(int u, int p) {
	ll ans = 0;
	sz[u] = 1;
	for(int v : adj[u]) {
		if(v == p) continue;
		ans += subtree(v, u);
		sz[u] += sz[v];
		ans += sz[v];
	}
	//printf("subtree(%d, %d) = %lld\n", u, p, ans);
	return ans;
}

int freq[N];

int dp[2][312345];

ll mx;
void go(int u) {
	ll base = 0;
	memset(freq, 0, sizeof freq);
	vector<int> gs;
	sz[u] = 1;
	for(int v : adj[u]) {
		base += subtree(v, u);
		freq[sz[v]]++;
		gs.pb(sz[v]);
		sz[u] += sz[v];
	}
	sort(gs.begin(), gs.end());
	gs.erase(unique(gs.begin(), gs.end()), gs.end());
	int gn = gs.size();
	dp[gn & 1][0] = 0;
	for(int i = 1; i <= sz[u]; i++)
		dp[gn & 1][i] = -1;
	for(int i = gn - 1; i >= 0; i--)
		for(int S = 1; S <= sz[u]; S++) {
			if(dp[!(gn & 1)][S] != -1)
				dp[gn & 1][S] = 0;
			else if(S >= gs[i] && dp[gn & 1][S - gs[i]] != -1 && dp[gn & 1][S - gs[i]] < freq[gs[i]])
				dp[gn & 1][S] = dp[gn & 1][S - gs[i]] + 1;
			else
				dp[gn & 1][S] = -1;
		}
	int i;
	for(i = sz[u]; i >= 0; i--)
		if(dp[0][i] != -1)
			mx = max(mx, base + ll(i + 1) * ll(sz[u] - i - 1) + i);
}

int main () {
	int i, n, v;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		int u;
		scanf("%d %d", &u, &v); u--; v--;
		//printf("(%d, %d)\n", u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	int siz = getsz(0, 0);
	int w = 0, u;
	do {
		u = w;
		for(int v : adj[u]) {
			if(sz[v] >= sz[u] || 2 * sz[v] <= siz)
				continue;
			w = v;
		}
	} while(u != w);
	int u2 = -1;
	for(int v : adj[u])
		if(sz[v] * 2 == siz)
			u2 = v;
	go(u);
	if(u2 != -1) go(u2);
	printf("%d %lld\n", n - 1, mx);
}
