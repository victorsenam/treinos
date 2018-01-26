#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll fib[100];

ll ifib(ll x) {
	int l = 0, r = 73;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(fib[m] <= x) l = m;
		else r = m - 1;
	}
	return l;
}

ll mid(ll x, ll bits) {
	int j = ifib(x);
	int tot = 0;
	for(int i = j; i >= 0 && (j - i + 1) <= bits; i--)
		if(x >= fib[i]) {
			x -= fib[i];
			tot++;
		}
	return tot;
}

map<ll, ll> mp;
ll solve(ll x) {
	if(x <= 1) return x;
	if(mp.count(x)) return mp[x];
	ll &r = mp[x];
	ll f = fib[ifib(x)];
	return r = (x - f + 1) + solve(f - 1) + solve(x - f);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
#endif
	fib[0] = fib[1] = 1;
	for(ll i = 2; fib[i - 1] < 2e15; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	ll l;
	cin >> l;
	if(l == 0) { puts("0"); return 0; }
	if(l == 1) { puts("1"); return 0; }
	ll tot = 0;
	ll i;
	for(i = 1; ; i++) {
		if(tot + i * fib[i - 1] >= l) break;
		tot += i * fib[i - 1];
	}
	ll until = (l - tot) / i + (fib[i] - 1);
	printf("%lld\n", solve(until) + mid(until + 1, (l - tot) % i));
}
