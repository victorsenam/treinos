#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 63;
const int K = (1<<10);

int visi[2][2][N][K], turn;
ll memo[2][2][N][K];

ll sv[11][N][10];

int q;
int b;
int vl[N];

ll cnt (int q, int i, int b) {
	if (q < 0 || q > 10)
		return 0;
	if (i == 0)
		return q == 0;

	ll & me = sv[q][i][b-1];
	if (me != -1)
		return me;
	
	return me = q*cnt(q-1, i-1, b) + (b-q)*cnt(q+1, i-1, b);
}

ll pd (int i, int mask, int ld, int free) {
	if (__builtin_popcount(mask) > N-i)
		return 0;
	if (i == N)
		return 1;

	if (free && ld) {
		return cnt(__builtin_popcount(mask), N-i, b);
	}
	
	ll & me = memo[ld][free][i][mask];
	if (visi[ld][free][i][mask] == turn)
		return me;
	visi[ld][free][i][mask] = turn;
	
	me = 0;

	if (!ld)
		me += pd(i+1, 0, 0, free||(0 < vl[i]));
	for (int p = !ld; p < b; p++) {
		if (!free && p > vl[i]) break;
		me += pd(i+1, (mask^(1<<p)), 1, free||(p < vl[i]));
	}

	return me;
}

void write (ll x, int b) {
	for (int i = N-1; i >= 0; i--) {
		vl[i] = x%b;
		x /= b;
	}
}

int main () {
	memset(sv, -1, sizeof sv);
	scanf("%d", &q);

	for (int i = 0; i < q; i++) {
		ll l, r;
		ll rs = 0;
		scanf("%d %lld %lld", &b, &l, &r);

		turn++;
		write(r,b);
		rs = pd(0,0,0,0);
		turn++;
		write(l-1,b);
		rs -= pd(0,0,0,0);
		printf("%lld\n", rs);
	}
}
