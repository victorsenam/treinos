#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int t;
int n;
ll k;
ll a[N];

int main () {
	scanf("%d", &t);
	while (t--) {
		ll res = LLONG_MIN, nz = 0;
		ll sm = 0;
		scanf("%d %lld", &n, &k);
		for (int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
			nz += a[i];
			sm += a[i];
			res = max(res, nz);
			nz = max(nz, 0ll);
		}

		ll pr = 0, s = 0;
		for (int i = 0; i < n; i++) {
			s += a[i];
			pr = max(pr, s);
		}
		
		ll sf = 0; s = 0;
		for (int i = n - 1; i >= 0; i--) {
			s += a[i];
			sf = max(sf, s);
		}

		if (k == 1)
			printf("%lld\n", res);
		else if (k == 2)
			printf("%lld\n", max(res, pr+sf));
		else if (k > 2) {
			if (pr + sf > 0) res = max(res, pr+sf);
			printf("%lld\n", max(res, pr+sm*ll(k-2)+sf));
		}
	}
}
