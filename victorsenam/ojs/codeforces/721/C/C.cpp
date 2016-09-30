#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 5e3+7;

int hd[N], to[N], nx[N], es;
ll wg[N];
int n, m, t;
ll memo[N][N];

ll pd (int u, int lf) {
	if (lf == 0 && u == n - 1) {
		return 0;
	} else if (lf == 0)
		return t+1;

	ll & me = memo[u][lf];
	if (me != -1)
		return me;

	me = t+1;

	for (int ed = hd[u]; ed; ed = nx[ed]) {
		me = min(me, pd(to[ed], lf-1) + wg[ed]);
	}

	return me;
}

void build (int u, int lf) {
	if (lf == 0 || u == n - 1)
		return;

	ll me = pd(u, lf);

	printf("%d ", u+1);

	for (int ed = hd[u]; ed; ed = nx[ed]) {
		if (me == pd(to[ed], lf-1) + wg[ed]) {
			build(to[ed], lf-1);
			return;
		}
	}

}

int main () {
	memset(memo, -1, sizeof memo);
	scanf("%d %d %d", &n, &m, &t);

	es = 1;

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d %lld", &a, &b, &wg[es]);
		a--; b--;

		to[es] = b; nx[es] = hd[a]; hd[a] = es++;
	}

	int i;
	for (i = n; i >= 0 && pd(0, i) > t; i--);
	i++;

	printf("%d\n", i);
	build(0, i-1);
	printf("%d\n", n);
}
