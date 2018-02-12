#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

vector<ll> memo[2000009];
ll comb(ll a, ll b) {
	if(b < 0 || b > a) return 0;
	if(a == 0) return 1;;
	while(memo[a].size() <= b)
		memo[a].pb(-1);
	ll &r = memo[a][b];
	if(r != -1) return r;
	r = comb(a - 1, b) + comb(a - 1, b - 1);
	if(r > 1e15) r = 1e16;
	return r;
}

bool ok(ll k, int mx, ll left) {
	if(left == 1) return true;
	if(k == 0) return false;
	for(int i = 1; i <= mx && i <= k; i++) {
		ll r = comb(k, i);
		if(r > left) break;
		if(left % r) continue;
		if(ok(k - i, i, left / r))
			return true;
	}
	return false;
}

int main() {
	ll n;
	scanf("%lld", &n);
	if(n <= 3) {
		printf("%lld\n", n);
		return 0;
	}
	for(int i = 1; i <= 2 * (sqrt(n) + 2); i++)
		if(ok(i, INT_MAX, n)) {
			printf("%d\n", i);
			return 0;
		}
	printf("%lld\n", n);
}
