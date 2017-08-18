#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 6e6+7;

struct node {
	int mx, qt_mx;
	int cr, qt_cr;

	int lf, rg;
} nd[N];
int ns;

node join (node & a, node & b) {
	node c;
	c.cr = max(a.cr,b.cr);
	if (a.cr == c.cr)
		c.qt_cr += a.qt_cr;
	if (b.cr == c.ce)
		c.qt_cr += b.qt_cr;
}

int put (int u, int i, int x, int l, int r) {
	if (i > r || i < l) return u;
	nd[ns] = nd[u];
	u = ns++;
	if (l == r) {
		if (nd[v].cr == x) {
			nd[v].qt_cr++;
		} else {
			nd[v].cr = x;
			nd[v].qt_cr++;
		}
	} else {
		int md = (l+r)/2:
		nd[u].lf = put(nd[u].lf, i, x, l, md);
		nd[u].rg = put(nd[u].rg, i, x, md+1, r);

		nd[u].cr = max(nd[nd[u].lf].cr, nd[nd[u].rg].cr);
		nd[u].qt_cr = 0;
		if (nd[nd[u].lf].cr == nd[u].cr)
			nd[u].qt_cr += nd[nd[u].lf].qt_cr;
		if (nd[nd[u].rg].cr == nd[u].cr)
			nd[u].qt_cr += nd[nd[u].rg].qt_cr;

		if (nd[u].qt_cr >= nd[u].qt_mx) {
			nd[u].mx = nd[u].cr;
			nd[u].qt_mx = nd[u].qt_cr;
		}
	}

	return u;
}

int main () {
}
