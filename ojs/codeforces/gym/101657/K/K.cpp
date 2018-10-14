#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1500;
const int K = 22;
const ll MOD = 1e9;

ll memo[K][N];
ll res[N];

ll dp (int n, int h) {
	if (n < 0) return 0;
	if (h == -1) return (n == 0);
	if (h < -1) return 0;
	return memo[h][n];
}

int main () {
	ll n;
	for (int n = 0; n < N; n++) res[n] = 0;
	for (int h = 0; h < K; h++) {
		for (int n = 0; n < N; n++) {
			ll & me = memo[h][n];
			me = 0;
			for (int l = 0; l < n; l++) {
				me = (me + dp(l, h-1)*dp(n-l-1,h-1))%MOD;
				me = (me + dp(l, h-1)*dp(n-l-1,h-2))%MOD;
				me = (me + dp(l, h-2)*dp(n-l-1,h-1))%MOD;
			}
			res[n] = (res[n] + me)%MOD;
		}
	}

	while (scanf("%lld", &n) != EOF) {
		printf("%09lld\n", res[n]);
	}
}
