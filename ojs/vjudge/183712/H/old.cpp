#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1000000007ll;
const int N = 2e5+7;

struct rs {
	multiset<ll> s;
	ll sum;
	ll prd;
};

ll res;
int n;
vector<pii> adj[N];
rs r[N];

inline ll mod (ll x) {
	return x%MOD;
}

inline ll fexp (ll a, ll e) {
	ll r = 1;
	while (e) {
		if (e) r = mod(r * a);
		a = mod(a * a);
		e >>= 1;
	}
	return r;
}

inline ll inv (ll a) {
	return fexp(a, MOD-2);
}

void dfs (int u, int p) {
	r[u].sum = 1;
	r[u].prd = 1;
	r[u].s.insert(1);
	for (pii to : adj[u]) {
		int v = to.first;
		ll w = to.second;
		if (v == p) continue;

		dfs(v, u);
		r[v].prd = mod(r[v].prd*w);
		r[v].sum = mod(r[v].sum*w);
		if (r[v].s.size() > r[u].s.size()) {
			swap(r[u].sum, r[v].sum);
			swap(r[u].prd, r[v].prd);
			r[u].s.swap(r[v].s);
		}

		for (ll x : r[v].s) {
			x = mod(x * r[v].prd);
			res = mod(res + mod(x*r[u].sum));
		}
		
		for (ll x : r[v].s) {
			x = mod(x * r[v].prd);
			r[u].sum = mod(r[u].sum + x);
			x = mod(x * inv(r[u].prd));
			r[u].s.insert(x);
		}
	}

	cout << u + 1<< " sum : " << r[u].sum << " prd : " << r[u].prd << endl;
	for (ll x : r[u].s)
		cout << x << " ";
	cout << endl;
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

	dfs(0,0);
	printf("%lld\n", res);
}
