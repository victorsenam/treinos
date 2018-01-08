#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int ts;
ll n, x;

int mr[N];

inline ll c2 (ll x) {
	return x*(x+1)/2;
}

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%lld %lld", &x, &n);

		ll v = c2(n) - x;
		if (v%2) {
			printf("impossible\n");
			continue;
		}

		for (int i = 0; i <= n; i++)
			mr[i] = 0;
		mr[x] = 2;
		v /= 2;

		ll s = 0, i = 0;
		for (i = 1; i <= n && s < v; i++) {
			if (i == x) continue;
			s += i;
			mr[i] = 1;
		}
		i--;

		ll d = s - v;
		if (d < 0) {
			printf("impossible\n");
			continue;
		} else {
			assert(d <= i);
			if (d != x) {
				mr[d] = 0;
			} else if (x > 2) {
				mr[1] = mr[x-1] = 0;
			} else if (i < n && x+1 != i) {
				mr[x+1] = 0;
				mr[i] = 0;
				mr[i+1] = 1;
			} else {
				assert(n <= 4);
				printf("impossible\n");
				continue;
			}
		}

		for (int i = 1; i <= n; i++)
			printf("%d", mr[i]);
		printf("\n");
	}
}
