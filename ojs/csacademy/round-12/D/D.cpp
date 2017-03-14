#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int Q = 1e5+7;
const int N = 70;

bool qr[N];
bool cm[N];
ll a, b, x;
int q;

int visi[N][2], turn;
ll memo[N][2];

void setqr (ll x) {
	for (int i = N-1; i >= 0; i--) {
		qr[i] = (x&1);
		x >>= 1;
	}
}

void setcm (ll x) {
	for (int i = N-1; i >= 0; i--) {
		cm[i] = (x&1);
		x >>= 1;
	}
}

ll pd (int i, bool pr) {
	if (i == N) return 1;
	ll & me = memo[i][pr];
	if (visi[i][pr] == turn) return me;
	visi[i][pr] = turn;

	me = 0;

	if (pr || qr[i])
		me += pd(i+1, pr);
	
	if (!cm[i])
		me += pd(i+1, (pr || qr[i]));

	return me;
}

int main () {
	scanf("%d", &q);

	for (int i = 0; i < q; i++) {
		scanf("%lld %lld %lld", &a, &b, &x);

		turn++;
		setcm(x);
		setqr(b);
		ll res = pd(0, 0);

		turn++;
		setqr(a-1);
		res -= pd(0, 0);
		
		printf("%lld\n", res);
	}
}
