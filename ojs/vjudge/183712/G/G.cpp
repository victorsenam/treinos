#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
const ll INF = 1e13;

ll memo[N][2][2];
ll x, y, z;
int visi[N][2][2], turn;

ll pd (ll q, bool o, bool d) {
	if (q <= 2) return -o*x/2;
	ll & me = memo[q][o][d];
	if (visi[q][o][d] == turn)
		return me;
	visi[q][o][d] = turn;
	me = INF;
	
	if (o && d) { 
		for (ll i = 1; i < q; i++) {
			ll loc = max(pd(i, 0, 0), pd(q-i+1, 1, 0));
			me = min(loc, me);
		}
	} else if (!d) {
		if (o)
			me = pd(q,1,1) + z;
		else
			me = pd(q,0,1) + y;
	} else { 
		me = pd(q,1,1) + x;
	}

	return me;
}

int main () {
	int ts;
	scanf("%d", &ts);
	for (int tt = 1; tt <= ts; tt++) {
		++turn;
		ll n;
		scanf("%lld %lld %lld %lld", &n, &x, &y, &z);
		n++;
		printf("Case %d: %lld\n", tt, pd(n, 0, 0));
	}
}
