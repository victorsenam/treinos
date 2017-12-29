#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 704;
const ll MOD = 1e9+7;

int pos;
char num[N];
int qt[N];
ll ten[N];
ll fat[N], ifat[N];
int visi[2][11][N][2];
ll memo[2][11][N][2];

inline ll mod (ll x) {
	return x%MOD;
}

inline ll fexp (ll a, ll e) {
	ll r = 1;
	while (e) {
		if (e&1) r = mod(r*a);
		a = mod(a*a);
		e >>= 1;
	}
	return r;
}

inline ll inv (ll a) {
	return fexp(a, MOD-2);
}

ll choose (ll k, ll n) {
	return mod(fat[n]*mod(ifat[k]*ifat[n-k]));
}

ll qtd (int val, int avail, int small) {
	if (avail < 0) return 0;
	if (val == -1) return !avail && small;

	ll & me = memo[0][val][avail][small];
	if (visi[0][val][avail][small])
		return me;
	visi[0][val][avail][small] = 1;

	ll res = 0;

	for (int i = 0; i <= avail; i++) {
		res = mod(res + mod(choose(i,avail)*qtd(val-1, avail - i, small)));
		if (!small && num[pos] > val)
			res = mod(res + mod(choose(i,avail)*qtd(val-1, avail - i, 1)));
	}

	return me = res;
}

ll pd (int val, int avail, int small, ll pot) {
	if (avail < 0 || val < 0) return 0;

	ll & me = memo[1][val][avail][small];
	if (visi[1][val][avail][small])
		return me;
	visi[1][val][avail][small] = 1;

	ll res = 0;
	ll sum = 0;
	for (int i = 0; i < qt[val]; i++) {
		sum = mod(sum + pot*val);
		pot = mod(pot*10);
	}

	for (int i = 0; i <= avail; i++) {
	    ll th = 0;
		th = mod(th + mod(qtd(val-1, avail - i, small)*sum) + pd(val-1, avail-i, small, pot));
		if (!small && num[pos] > val)
			th = mod(th + mod(qtd(val-1, avail - i, 1)*mod(sum + pot*val)) + pd(val-1, avail-i, 1, mod(pot*10)));
		res = mod(res + mod(th * choose(i,avail)));

		sum = mod(sum + pot*val);
		pot = mod(pot*10);
	}

	return me = res;
}

int main () {
	fat[0] = 1;
	for (int i = 1; i < N; i++)
		fat[i] = mod(fat[i-1] * i);
	ifat[N-1] = inv(fat[N-1]);
	for (int i = N-2; i >= 0; i--)
		ifat[i] = mod(ifat[i+1]*(i+1));

	scanf(" %s", num);
	int n = 0;
	for (int i = 0; num[i]; i++) {
		num[i] -= '0';
		n++;
	}

	ll res = 0;
	for (int i = 0; i < n; i++) {
		pos = i;
		res = mod(res + pd(9, n - i - 1, 0, 1));
		qt[num[i]]++;
		memset(visi, sizeof visi, 0);
	}
	res = mod(res + pd(9, 0, 1, 1));
	printf("%lld\n", res);
}
