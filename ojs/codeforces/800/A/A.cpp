#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int n; ll p;
ll a[N], b[N];

bool solve (double t) {
	double s = 0;
	for (int i = 0; i < n; i++) 
		s += max(0., a[i] - b[i]/t);
	return (s <= p);
}

int main () {
	scanf("%d %lld", &n, &p);
	ll acc = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &a[i], &b[i]);
		acc += a[i];
	}

	if (acc <= p) {
		printf("-1\n");
		return 0;
	}

	double lo = 0., hi = 1e18;
	int ts = 100;

	while (ts--) {
		double md = (lo+hi)*.5;
		if (solve(md))
			lo = md;
		else
			hi = md;
	}

	printf("%.20f\n", lo);
}
