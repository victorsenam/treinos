#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

struct obs {
	int i, l;
};

int n, ml[3], t;
int m;
obs x[N];
int memo[N][4][2];
int visi[N];

int dp (int i, int l, bool c) {
	if (i == 0) return 0;

	//cout << "(" << i << " " << l << " " << c << ") is " << x[i].i << endl;
	int & me = memo[i][l][c];
	if (visi[i]&(1<<(l+l+int(c)))) return me;
	visi[i] |= (1<<(l+l+int(c)));

	me = -1;

	if (dp(i-1,l,1) >= 0) {
		int loc = dp(i-1,l,1) + x[i].i - x[i-1].i;
		if (x[i].l&l) { loc -= t; if (loc == 0) loc--; }
		me = max(me, loc);
	}
	if (c && !(x[i].l&l)) {
		int loc = min(dp(i,3-l,0),t);
		me = max(me, loc);
	}

	return me;
}

vector<int> chg;

void build (int i, int l, int c) {
	if (i == 0) { if (l == 2) chg.pb(x[i].i); return; }
	int me = dp(i,l,c);

	if (dp(i-1,l,1) >= 0) {
		int loc = dp(i-1,l,1) + x[i].i - x[i-1].i;
		if (x[i].l&l) { loc -= t; if (loc == 0) loc--; }
		if (loc == me) {
			build(i-1,l,1);
			return;
		}
	}
	if (x[i].i != n+1) chg.pb(x[i].i);
	build(i,3-l,0);
}

set<int> s[4];
vector<pii> shot;

void emul (int i, int lane, int charge) {
	//cout << "At " << i << " " << lane << " " << charge << endl;
	assert(charge >= 0 && charge <= t);
	auto nxo = s[lane].upper_bound(i);
	if (nxo != s[lane].end() && (chg.empty() || chg.back() >= *nxo)) {
		if (charge == t) { s[lane].erase(nxo); shot.pb({i,lane}); emul(i,lane,0); }
		else emul(i+t-charge,lane,t);
	} else if (chg.size()) {
		int to = chg.back(); chg.pop_back();
		emul(to,3-lane,min(charge+to-i,t));
	}
}

int main () {
	scanf("%d %d %d %d", &n, &ml[1], &ml[2], &t);

	for (int k = 1; k <= 2; k++) {
		for (int i = 0; i < ml[k]; i++) {
			scanf("%d", &x[m].i);
			x[m].l = k;
			s[x[m].l].insert(x[m].i);
			m++;
			x[m].i = x[m-1].i+1;
			x[m].l = 0;
			m++;
		}
	}
	x[m].l = 0;
	x[m].i = n+1;
	m++;
	x[m].l = 0;
	x[m].i = 0;
	m++;

	sort(x, x+m, [] (obs a, obs b) { return a.i < b.i; });

	int ss = m;
	m = 0;
	for (int i = 0; i < ss; i++) {
		if (m && x[i].i == x[m-1].i)
			x[m-1].l += x[i].l;
		else
			x[m++] = x[i];
	}

	if (dp(m-1,1,1) >= 0) {
		printf("Yes\n");
		build(m-1,1,1);
		printf("%u\n", chg.size());
		for (int i = chg.size() - 1; i >= 0; i--)
			printf("%d ", chg[i]);
		printf("\n");
		emul(0,1,0);
		printf("%u\n", shot.size());
		for (pii a : shot) printf("%lld %lld\n", a.first, a.second);
	} else {
		printf("No\n");
	}
}
