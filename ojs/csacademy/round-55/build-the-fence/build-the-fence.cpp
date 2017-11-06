#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

ll n, k;
ll a[N];

bool solve (ll x) {
	ll q = 0;
	for (int i = 0; i < n; i++)
		q += a[i]/x;
	return q >= k;
}

int main () {
	scanf("%lld %lld", &n, &k);
	for (int i = 0; i < n; i++) 
		scanf("%lld", &a[i]);

	ll hi = 1e9;
	ll lo = 0;
	while (lo < hi) {
		ll md = (lo + hi + 1)/2;

		if (solve(md))
			lo = md;
		else
			hi = md - 1;
	}
	printf("%lld\n", lo);
}
