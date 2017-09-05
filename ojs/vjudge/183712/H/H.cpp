#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1e9+7;
const int N = 2e5+7;

inline ll mod (ll x) {
	return x%MOD;
}

inline ll fexp (ll a, ll e) {
	ll r = 1;
	while (e) {
		if (e&1) r = mod(r * a);
		a = mod(a * a);
		e >>= 1;
	}
	return r;
}

inline ll inv (ll a) {
	return fexp(a, MOD-2);
}

struct rs {
	vector<ll> s;
	ll sum;
	ll prd;

	void add (ll x) {
		sum = mod(sum + x);
		s.pb(mod(x * inv(prd)));
	}

	ll get (ll x) {
		return mod(x*prd);
	}

	void prod (ll x) {
		prd = mod(prd * x);
		sum = mod(sum * x);
	}
};

ll res;
int n;
vector<pii> adj[N];
rs r[N];
int cnt;

int dfs (int u, int p) {
	cnt++;
	int a = u;
	r[u].sum = 0;
	r[u].prd = 1;
	r[u].add(1);
	for (pii to : adj[u]) {
		int v = to.first;
		ll w = to.second;
		if (v == p) continue;

		int b = dfs(v, u);

		r[b].prod(w);
		if (r[b].s.size() > r[a].s.size()) {
			swap(a,b);
		}

		for (ll x : r[b].s)
			res = mod(res + mod(r[b].get(x) * r[a].sum));
		
		for (ll x : r[b].s)
			r[a].add(r[b].get(x));
		r[b].s.clear();
	}
	return a;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n - 1; i++) {
		int a, b; ll w;
		scanf("%d %d %lld", &a, &b, &w);
		a--; b--;
		
		adj[a].pb(pii(b,w));
		adj[b].pb(pii(a,w));
	}

	res = 0;
	dfs(0,0);
	assert(cnt == n);
	printf("%lld\n", res);
}
