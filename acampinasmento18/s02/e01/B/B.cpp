#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 200007;

int n;
vector<int> v[N];
int memo[N][7][5];

int cp (int u, int close, int cur, int p) {
// close: 0 none, 1 one, 2 two, 3 one here, 4 two here
// cur: how many children will I select at least? (0,1,2)
	int & me = memo[u][close][cur];
	if (me != -1) return me;

	if (close == 4) {
		me = 0;
		for (int c : v[u]) if (c != p) {
			me += min(cp(c,3,0,u) + 1, cp(c,2,0,u));
		}
	} else if (close == 3) {
		me = 0;
		for (int c : v[u]) if (c != p) {
			me += min(cp(c,3,0,u) + 1, cp(c,1,0,u));
		}
		me = min(me, cp(u,4,0,p) + 1);
	} else if (close <= 2) {
		me = n+3;
		// escolher todo mundo vazio
		int loc = 0;
		for (int c : v[u]) if (c != p) {
			loc += min(cp(c,0,3,u)+1,cp(c,0,2-close,u));
		}
		if (!cur) me = min(me,loc);

		loc = 0;
		// escolher pelo menos 1
		int a = -1, va;
		for (int c : v[u]) if (c != p) {
			int vc = cp(c,3,0,u) - cp(c,0,max(1-close,0),u);
			if (a == -1 || va > vc) {
				a = c;
				va = vc;
			}
		}
		for (int c : v[u]) if (c != p) {
			if (c == a) loc += cp(c,3,0,u) + 1;
			else loc += min(cp(c,3,0,u)+1, cp(c,0,max(1-close,0),u));
		}
		if (a != -1) me = min(me,loc);

		loc = 0;
		// escolher 2 no mesmo
		a = -1, va;
		for (int c : v[u]) if (c != p) {
			int vc = cp(c,4,0,u) - cp(c,0,0,u);
			if (a == -1 || va > vc) {
				a = c;
				va = vc;
			}
		}
		for (int c : v[u]) if (c != p) {
			if (c == a) loc += cp(c,4,0,u) + 2;
			else loc += min(cp(c,3,0,u)+1, cp(c,0,0,u));
		}
		if (a != -1) me = min(me,loc);

		loc = 0;
		// escolher pelo menos 2
		a = -1, va; int b = -1, vb;
		for (int c : v[u]) if (c != p) {
			int vc = cp(c,3,0,u) - cp(c,0,0,u);
			if (a == -1 || va > vc) {
				b = a; vb = va; a = c; va = vc;
			} else if (b == -1 || vb > vc) {
				a = c; va = vc;
			}
		}
		for (int c : v[u]) if (c != p) {
			if (c == a || c == b) loc += cp(c,3,0,u) + 1;
			else loc += min(cp(c,3,0,u)+1, cp(c,0,0,u));
		}
		if (b != -1) me = min(me,loc);
	}

	return me;
}

int main () {
	scanf("%d", &n);
	memset(memo, -1, sizeof memo);
	for (int i = 0; i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		v[a].pb(b); v[b].pb(a);
	}
	v[0].pb(0);
	printf("%d\n", min(cp(0,0,0,0), cp(0,2,0,0) + 1));
}
