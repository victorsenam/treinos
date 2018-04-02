#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e2+7;

const ll MOD = 1e9+7;

inline ll mod (ll x) { return x%MOD; }

int t, n, k;
ll c[N];
ll dp[N], pot[N];
int vs[N];
vector<int> adj[N];

int get (int u) {
	if (vs[u]) return u;
	vs[u] = 1;
	return get(c[u]);
}

int gs (int u) {
	vs[u] = 1;
	int res = 1;
	for (int v : adj[u]) res += gs(v);
	return res;
}

int main () {
	scanf("%d", &t);
	t++;
	while (--t) {
		scanf("%d %d", &n, &k);

		dp[0] = k;
		pot[0] = 1;
		for (int i = 1; i < N; i++) {
			dp[i] = 0;
			pot[i] = mod(pot[i-1]*(k-1));
			ll acc = k-1;
			for (int j = i-2; j >= 0; j--) {
				dp[i] = mod(dp[i] + mod(dp[j] * acc));
				acc = mod(acc*ll(k-2));
			}
		}

		for (int i = 0; i < n; i++) {
			scanf("%d", &c[i]);
			adj[i].clear();
		}

		for (int i = 0; i < n; i++) { adj[c[i]].pb(i); vs[i] = 0; }

		ll res = 1;
		for (int i = 0; i < n; i++) {
			if (vs[i]) continue;
			int u = get(i);
			int v = u;
			int sz = 0;
			//cout << "ciclo:";
			do {
				//cout << " " << v;
				vs[v] = 2;
				v = c[v];
				sz++;
			} while (v != u);
			ll loc = dp[sz];
			//cout << " tem tamanho " << sz << " e " << loc << " maneiras" << endl;

			do {
				for (int w : adj[v]) if (vs[w] != 2) {
					int s = gs(w);
					//cout << "pendura " << s << " de " << v << endl;
					loc = mod(loc*pot[gs(w)]);
				}
				v = c[v];
			} while (v != u);

			res = mod(res*loc);
		}
		printf("%lld\n", res);
	}
}
