#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;
const ll MOD = 1e9+7;

inline ll mod (ll x) { return ((x%MOD) + MOD)%MOD; }
//inline ll mod (ll x) { return x; }

int n;
ll x[N];
vector<int> adj[N];
ll cnt[N][2];
ll sum[N][2];
ll res = 0;

void dfs (int u, int p) {
	cnt[u][0] = sum[u][0] = 0;
	cnt[u][1] = 1; sum[u][1] = x[u];
	for (int v : adj[u]) if (v != p) {
		dfs(v,u);
		//cout << u << ": " << cnt[u][0] << "(" << sum[u][0] << ") " << cnt[u][1] << "(" << sum[u][1] << ")" << endl;
		// começa em v, anda par e vai pra outro
		res = mod(res + mod(cnt[v][0]*sum[u][1]) + mod(sum[v][0]*cnt[u][1]));
		// começa em v, anda ímpar e vai pro outro
		res = mod(res + mod(cnt[v][1]*sum[u][0]) + mod(sum[v][1]*cnt[u][0]));
		//cout << "add " << mod(cnt[v][0]*sum[u][1]) + mod(sum[v][0]*cnt[u][1]) << endl;
		//cout << "add " << mod(cnt[v][1]*sum[u][0]) + mod(sum[v][1]*cnt[u][0]) << endl;

		for (int k = 0; k < 2; k++)
			cnt[u][k] = mod(cnt[u][k] + cnt[v][!k]);
		sum[u][0] = mod(sum[u][0] - mod(cnt[v][1]*x[u]) + sum[v][1]);
		sum[u][1] = mod(sum[u][1] + mod(cnt[v][0]*x[u]) + sum[v][0]);
	}
	//cout << u << ": " << cnt[u][0] << "(" << sum[u][0] << ") " << cnt[u][1] << "(" << sum[u][1] << ")" << endl;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) { scanf("%lld", &x[i]); x[i] = mod(x[i]); }
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	res = 0;
	dfs(0,0);
	//cout << res << endl;
	res = mod(res + res);
	//cout << res << endl;
	for (int i = 0; i < n; i++) res = mod(res + x[i]);
	printf("%lld\n", res);
}
