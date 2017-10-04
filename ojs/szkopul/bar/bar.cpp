#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e3+7;

int n, m, k;
vector<int> memo[2*N];
int hd[N], to[2*N], nx[2*N], es;
int sz[N];

int dfs (int u, int p) {
	sz[u] = 1;
	int prev = -1;
	int hh = hd[u], nn;
	hd[u] = 0;
	for (int ed = hh; ed; ed = nn) {
		nn = nx[ed];
		if (to[ed] == p) continue;
		sz[u] += dfs(to[ed], u);
		nx[ed] = hd[u]; hd[u] = ed;
	}

	for (int ed = hd[u]; ed; ed = nx[ed])
		memo[ed] = vector<int>(sz[u]+2, -1);
	return sz[u];
}

int dp (int ed, int k, int acc) {
	if (k < 0) return N;
	if (ed == 0) {
		if (k == 0) return 0;
		return N;
	}
	int & me = memo[ed][k];
	if (me != -1)
		return me;

	acc -= sz[to[ed]];
	me = dp(nx[ed], k, acc) + 1;
	for (int a = max(1, k - acc); a <= k && a <= sz[to[ed]]; a++)
		me = min(me, dp(hd[to[ed]], a - 1, sz[to[ed]]) + dp(nx[ed], k - a, acc));
	return me;
}

int main () {
	es = 2;
	scanf("%d", &n);

	for (int i = 0; i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		nx[es] = hd[a]; to[es] = b; hd[a] = es++;
		nx[es] = hd[b]; to[es] = a; hd[b] = es++;
	}

	dfs(0, 0);

	scanf("%d", &m);
	while (m--) {
		scanf("%d", &k);

		int res = N;
		for (int i = 0; i < n; i++) {
			if (k > sz[i]) continue;
			res = min(res, dp(hd[i], k - 1, sz[i]) + !!i);
		}
		printf("%d\n", res);
	}
}
