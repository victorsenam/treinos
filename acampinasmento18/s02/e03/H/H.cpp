#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll p_in_fact(ll p, ll n) {
	ll tot = 0;
	for(n /= p; n; n /= p)
		tot += n;
	return tot;
}

ll fexp(ll x, ll e, ll p) {
	ll r = 1 % p;
	for(; e; e >>= 1, x = (x * x) % p)
		if(e & 1)
			r = (r * x) % p;
	return r;
}

inline ll inv(ll x, ll p) { return fexp(x, p - 2, p); }

ll fat[4][11234];

ll fact_mod(ll n, ll p, int pi) {
	if(n < p) return fat[pi][n];
	ll ans = fexp(fat[pi][p - 1], n / p, p);
	ans = (ans * fat[pi][n % p]) % p;
	return (ans * fact_mod(n / p, p, pi)) % p;
}

ll solve(ll p, ll n, ll d, int pi) {
	if(p_in_fact(p, n) > (n / d) * p_in_fact(p, d) + p_in_fact(p, n / d))
		return 0;
	ll ans = fact_mod(n, p, pi);
	ans = (ans * inv(fact_mod(n / d, p, pi), p)) % p;
	ans = (ans * inv(fexp(fact_mod(d, p, pi), n / d, p), p)) % p;
	return ans;
}

int p[] = {2, 13, 5281, 7283};
ll ans[4];
int phi[] = {1, 12, 5280, 7282};
int main () {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int pi = 0; pi < 4; pi++) {
		fat[pi][0] = 1;
		for(ll i = 1; i <= 10000; i++)
			fat[pi][i] = (fat[pi][i - 1] * i) % p[pi];
	}
	for(ll d = 1; d * d <= n; d++) {
		if(n % d) continue;
		for(int pi = 0; pi < 4; pi++) {
			ans[pi] = (ans[pi] + solve(p[pi], n, d, pi)) % p[pi];
			if(d * d != n) ans[pi] = (ans[pi] + solve(p[pi], n, n / d, pi)) % p[pi];
		}
	}
	//for(int pi = 0; pi < 4; pi++)
	//	printf("%lld [mod %d]\n", ans[pi], p[pi]);
	for(int pi = 2; pi >= 0; pi--) {
		ll np = p[pi] * p[pi + 1];
		ans[pi] = (ans[pi] + ((ans[pi + 1] - ans[pi] + np) % np) * fexp(p[pi], phi[pi + 1], np)) % np;
		p[pi] *= p[pi + 1];
		phi[pi] *= phi[pi + 1];
	}
	//printf("%lld [mod %d]\n", ans[0], p[0]);
	printf("%lld\n", fexp(m, ans[0], p[0] + 1));
}
