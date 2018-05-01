#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
const int K = 22;

int ts;
int n, q;
vector<int> adj[N];
char c[N];

struct info {
	int dw, up, sm, p;
};

info concat (info low, info upp) {
	info res;
	res.sm = low.sm + upp.sm;
	res.dw = min(upp.dw, upp.sm + low.dw);
	res.up = min({ upp.up + low.sm, low.up, 0 });
	res.p = upp.p;
	return res;
}

info tb[N][K];
int lv[N];

int get (int u) { return (c[u] == '(') - (c[u] == ')'); }

ostream & operator << (ostream & os, info v) { return os << v.sm << " ^" << v.up << " v" << v.dw << " " << v.p; }

int dfs (int u, int p) {
	lv[u] = lv[p] + 1;
	tb[u][0] = info({ min(0, get(u)), min(0, get(u)), get(u), p });
	for (int k = 1; k < K; k++) tb[u][k] = concat(tb[u][k-1], tb[tb[u][k-1].p][k-1]);
	//cout << u << "===" << endl;
	//for (int k = 0; k < K; k++)
		//cout << tb[u][k] << endl;
	for (int v : adj[u]) if (v != p)
		dfs(v, u);
}

int main () {
	scanf("%d", &ts);

	while (ts--) {
		scanf("%d %d", &n, &q);
		for (int i = 0; i <= n; i++) adj[i].clear();
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			adj[a].pb(b);
			adj[b].pb(a);
		}
		for (int i = 1; i <= n; i++) scanf(" %c", &c[i]);
		for (int k = 0; k < K; k++) tb[0][k] = info({0,0,0,0});
		dfs(1,0);
		for (int i = 0; i < q; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			info x = info({0,0,0,a}), y = info({0,0,0,b});
			
			for (int k = K-1; k >= 0; k--) if (lv[tb[x.p][k].p] >= lv[y.p])
				x = concat(x, tb[x.p][k]);
			for (int k = K-1; k >= 0; k--) if (lv[tb[y.p][k].p] >= lv[x.p])
				y = concat(y, tb[y.p][k]);
			for (int k = K-1; k >= 0; k--) if (tb[x.p][k].p != tb[y.p][k].p) {
				x = concat(x, tb[x.p][k]);
				y = concat(y, tb[y.p][k]);
			}
			if (x.p != y.p) { x = concat(x, tb[x.p][0]); y = concat(y, tb[y.p][0]); }
			assert(x.p == y.p);
			x = concat(x, tb[x.p][0]);
			//cout << x << " | " << y << endl;

			if (x.up >= 0 && x.sm + y.dw >= 0 && x.sm + y.sm == 0) printf("Yes\n");
			else printf("No\n");
		}
	}
}
