#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n;
vector<ll> v;

void go (ll n, ll x) {
	if (n < 0 || x <= 0) return;
	if (n == 0) {
		printf("%lld", v[0]);
		for (int i = 1; i < v.size(); i++)
			printf("+%lld", v[i]);
		printf("\n");
	} else {
		v.pb(x);
		go(n-x, x);
		v.pop_back();
		go(n, x-1);
	}
}

int main () {
	scanf("%lld", &n);

	go(n, n);
}
