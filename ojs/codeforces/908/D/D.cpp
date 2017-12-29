#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;
const ll MOD = 1e9+7;

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

ll inv (ll a) {
	return fexp(a, MOD-2);
}

ll k, ipa, ipb;
ll i1mpa, i1mpb, pa, pb;
ll memo[N][N];
int visi[N][N];

ll pd (ll qa, ll qf) {
	if (qa + qf >= k)
		return mod(mod(mod((qa + qf)*pb) + pa)*i1mpa);

	ll & me = memo[qa][qf];
	if (visi[qa][qf])
		return me;
	visi[qa][qf] = 1;
	
	return me = mod(mod(pa*pd(qa+1,qf)) + mod(pb*pd(qa,qf+qa)));
}

int main () {
	scanf("%lld %lld %lld", &k, &ipa, &ipb);

	pa = mod(ipa*inv(ipa+ipb));
	pb = mod(ipb*inv(ipa+ipb));
	i1mpa = inv(mod(mod(1-pa)+MOD));
	i1mpb = inv(mod(mod(1-pb)+MOD));

	printf("%lld\n", mod(mod(pd(1,0)*pa)*i1mpb));
}
