#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 107;
int n;
const ll MOD = 1e9+7;
ll fat[N];

inline ll mod (ll x) {
	return ((x%MOD) + MOD)%MOD;
}

inline ll c2 (ll i) {
	return mod(i * (i-1) / 2);
}

inline ll c3 (ll i) {
	return mod(i * (i-1) * (i-2) / 6);
}

ll fexp (ll a, ll e) {
	ll r = 1;
	while (e) {
		if (e&1) r = mod(r * a);
		a = mod(a * a);
		e /= 2;
	}
	return r;
}

int main() {
	fat[0] = 1;
	for (int i = 1; i < 103; i++)
		fat[i] = mod(fat[i-1] * i);

	scanf("%d", &n);
	ll a = fexp(2, c2(n) - n + 1);
	a = mod(a * fat[n]);


	ll b = mod( mod(c2(n) * fat[n-2]) * fexp(2, c2(n-2) - max((n - 3),0)) );
	ll s = 0;
	for (ll i = 0; i <= n-2; i++) {
		int a = (i > 0);
		int b = (n - 2 - i > 0);

		s = mod(s + mod(fexp(2,2*(n-2-b-a) + (a&&b))) );
	}
	b = mod(b*s);

	
	ll c = mod( mod(c3(n) * fat[n-3]) * fexp(2, c2(n-3) - max(n - 4,0)) );
	s = 0;
	for (ll i = 0; i <= n-3; i++) {
		int b = (i > 0);
		int a = (n - 3 - i > 0);
		
		s = mod(s + mod(6ll*fexp(2, 3*(n-3) - 2*(a+b) + (a&&b))));
	}
	c = mod(c*s);

	printf("%lld\n%lld\n%lld\n", a, b, c);
}
