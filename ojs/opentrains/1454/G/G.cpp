#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const ll i2 = (modn + 1ll) / 2ll;

const int N = 512345;
ll mul[N], ct[N], fat[N];
int p[N], seen[N];

int n;
ll memo[N][2];
ll solve(int i, int p) {
	if(i == n + 1) return (p == 0);
	ll &r = memo[i][p];
	if(r != -1) return r;
	//printf("solve(%d, %d)\n", i, p);
	//printf("ct[%d] = %d\n", i, ct[i]);
	r = 0;
	if(ct[i] == 0) {
		r = solve(i + 1, p);
	} else if(!(i & 1) || ct[i] > 1) {
		r = mod(mod(mod(solve(i + 1, p) * mul[i]) * fat[ct[i]]) * i2);
		r = mod(r + mod(mod(mod(solve(i + 1, !p) * mul[i]) * fat[ct[i]]) * i2));
	} else{
		r = mod(mod(solve(i + 1, p) * mul[i]) * fat[ct[i]]);
	}
	//if(ct[i] == 0) {
	//	r = solve(i + 1, p);
	//} else if((i & 1) || (ct[i] == 1)) {
	//	r = mod(mod(solve(i + 1, p) * mul[i]) * fat[ct[i]]);
	//} else {
	//	r = mod(mod(solve(i + 1, p) * fat[ct[i]]) * i2);
	//	r = mod(r + mod(solve(i + 1, !p) * fat[ct[i]]) * i2);
	//	r = mod(r * mul[i]);
	//}
	//printf("solve(%d, %d) = %lld\n", i, p, r);
	return r;
}

int main() {
	scanf("%d", &n);
	fat[0] = 1;
	int i;
	for(i = 1; i <= n; i++) {
		fat[i] = mod(fat[i - 1] * ll(i));
		scanf("%d", &p[i]);
		mul[i] = 1;
	}
	for(i = 1; i <= n; i++) {
		if(seen[i]) continue;
		int sz = 1; seen[i] = 1;
		for(int j = p[i]; j != i; j = p[j], sz++) seen[j] = 1;
		ct[sz]++;
		mul[sz] = mod(mul[sz] * ll(sz));
	}

	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(1, 0));
}
