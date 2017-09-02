#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1e9+7;
const int N = 53;

ll memo[N][N][N][2];

inline ll mod (ll x) {
	return x%MOD;
}

ll fexp (ll a, ll e) {
	ll r = 1;
	while (e) {
		if (e&1) r = mod(r*a);
		a = mod(a*a);
		e >>= 1;
	}
	return r;
}

ll inv (ll q) {
	return fexp(q, MOD-2);
}

ll pd (int n, int m, int nm, int hs) {
	if (m < 0)
		return 0;
	if (n == 0)
		return 1;
	if (nm == 0)
		return 0;

	ll & me = memo[n][m][nm][hs];
	if (me != -1)
		return me;

	me = 0;
	if (!hs) {
		for (int q = 0; q*nm <= n; q++) {
			ll how = pd(nm-1, m-1, nm-1, 1);
			ll qt = 1;
			for (int k = 0; k < q; k++) {
				qt = mod(qt*mod(how+MOD-k));
				qt = mod(qt*inv(k+1));
			}
			me = mod(me + mod(pd(n-q*nm, m, nm-1, 1)*qt));
		}
	} else {
		for (int q = 0; q <= n; q++) {
			me = mod(me + mod(pd(q, m, q, 0)*pd(n-q, 50, n-q, 0)));
			me = mod(me + MOD - mod(pd(q, m, q, 0)*pd(n-q, m, n-q, 0)));
		}
		me = mod(me * inv(2));
	}

	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	int n, m;
	scanf("%d %d", &n, &m);
	ll rs = mod(pd(n, m-1, n, 0) + MOD - pd(n,m-2,n,0));
	rs = mod(rs + rs);
	printf("%lld\n", rs);
}
