#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e4+7;
const int B = 230;
const ll MOD = 1e9+7;

ll pd[N][B];
ll choose[B][B];

inline ll mod (ll x) {
	return x%MOD;
}

inline ll chs (ll a, ll b) {
	if (b == 0 || b == a) return 1;
	if (b < 0 || a < 0 || b > a) return 0;
	return choose[a][b];
}

inline ll dp (ll n, ll a) {
	if (n < 0 || a < 0 || a > n) return 0;
	if (a == 0) return n == 0;
	//if (a == n) return 1;
	return pd[n][a];
};

int main () {
	for (int i = 0; i < N; i++) {
		for (int a = 0; a <= min(i,B-1); a++)
			pd[i][a] = mod(dp(i-1,a-1) + mod(dp(i-1,a)*ll(i-1)));
	}

	for (int a = 0; a < B; a++) {
		for (int b = 0; b <= a; b++)
			choose[a][b] = mod(chs(a-1,b-1) + chs(a-1,b));
	}
	
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int n, a, b;
		scanf("%d %d %d", &n, &a, &b);
		printf("%lld\n", mod(chs(a+b-2,a-1)*dp(n-1,a+b-2)));
	}
}
