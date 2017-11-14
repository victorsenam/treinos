#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;
const ll MOD = 1e9+7;

int n, k;
ll dp[N];
ll fat[N], ift[N];

inline ll mod (ll x) {
	return x%MOD;
}

ll fexp (ll a, int e) {
	ll r = 1;
	while (e) {
		if (e&1) r = mod(r*a);
		a = mod(a*a);
		e >>= 1;
	}
	return r;
}

ll inv (ll a) {
	return fexp(a,MOD-2);
}

int main () {
	fat[0] = 1;
	for (ll i = 1; i < N; i++)
		fat[i] = mod(fat[i-1]*i);
	ift[N-1] = inv(fat[N-1]);
	for (ll i = N-2; i >= 0; i--) {
		ift[i] = mod(ift[i+1]*(i+1));
		assert(mod(ift[i+1]*fat[i+1]) == 1);
	}
	
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= k; i++) {
		dp[i] = 0;
	}
	ll s = 0;
	ll r = 0;
	for (int i = k+1; i <= n; i++) {
		dp[i] = mod(i-k+s);
		dp[i] = mod(fat[i-2]*dp[i]);
		//cout << mod(fat[i-2] * (i-k)) << " + " << mod(s*fat[i-2]) << " = " << dp[i] << endl;
		s = mod(s + mod(dp[i]*ift[i-1]));
		s = mod(mod(s - mod(dp[i-k+1]*ift[i-k])) + MOD);

		r = mod(r + mod(mod(fat[n-1]*ift[n-i])*dp[i]));
	}

	printf("%lld\n", r);
}
