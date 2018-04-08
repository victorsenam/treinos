#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll x, d;
vector<ll> v;
ll cur;

int main () {
	cur = 1;
	scanf("%lld %lld", &x, &d);

	for (ll p = 0; x; p++) if (x&(1<<p)) {
		for (int i = 0; i < p; i++) v.pb(cur);
		x -= (1<<p);
		cur += d;
		v.pb(cur);
		cur += d;
	}

	printf("%d\n", (int) v.size());
	for (ll x : v)
		printf("%lld ", x);
	printf("\n");
}
