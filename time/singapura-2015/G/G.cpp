#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

const int N = 3007;

ll memo[N][N];
int visi[N][N], turn;
ll v[N];
ll pr[N];
int n;

ll pd (int i, int j) {
	if (i > j) return 0;
	if (i >= n || j >= n) return 0;
	
	ll & me = memo[i][j];
	if (visi[i][j] == turn)
		return me;
	visi[i][j] = turn;

	me = 1;
	me = max(me, pd(i, j+1));

	int k = lower_bound(pr, pr+n+1, pr[j+1]-pr[i]+pr[j+1]) - pr - 1;
	me = max(me, pd(j+1, k)+1);
	//printf("%lld [%d,%d] tem soma %lld, preciso do [%d,%d] %lld\n", me, i, j, pr[j+1]-pr[i], j+1, k, pr[k+1] - pr[j+1]);
	return me;
}

int main () {
	while (scanf("%d", &n) != EOF && ++turn) {
		pr[0] = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld", v+i);
			pr[i+1] = pr[i] + v[i];
		}
		pr[n+1] = 3003l*INT_MAX;

		printf("%lld\n", pd(0, 0));
	}
}
