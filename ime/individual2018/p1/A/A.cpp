#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 30123;
int n; ll t;
ll v[N];

int main () {
	int ts =0;
	while (scanf("%d %lld", &n, &t) != EOF ){
		if (!n) break;
		for (int i = 0; i < n; i++)
			scanf("%lld", &v[i]);
		bool sw = 0;
		if (t < 0) {
			t = -t - 1;
			sw = 1;
			for (int i = 0; i < n; i++) v[i] = -v[i];
		}
		sort(v, v+n);
		int lm = 0;
		while (lm < n && v[lm] < 0) lm++;

		ll q = n*n;
		ll p = 0;
		for (int i = 0; i < n; i++) {
			ll x = v[i];
			if (sw) x = -x;
			if (x < 0) {
				int lo = 0, hi = lm;
				while (lo < hi) {
					int md = (lo + hi)/2;
					if (x*v[md] <= t) hi = md;
					else lo = md + 1;
				}
				p += lo;
			} else {
				int lo = lm, hi = n;
				while (lo < hi) {
					int md = (lo + hi)/2;
					if (x*v[md] <= t) lo = md+1;
					else hi = md;
				}
				p += n - hi;
			}
		}
		if (sw) p = q-p;

		ll g = __gcd(p,q);
		printf("Case %d: %lld/%lld\n", ++ts, p/g, q/g);
	}
}
