#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double dbl;
const dbl eps = 1e-8;

int adj[112][112];
int n;
double p[112];
int t;

dbl memo[1 << 19][20];
bool seen[1 << 19];
dbl* solve(int bm) {
	if(seen[bm >> 1]) return memo[bm >> 1];
	seen[bm >> 1] = 1;
	vector<int> all;
	dbl here = 0;
	for(int i = 0; i < n; i++)
		if((bm >> i) & 1) {
			all.pb(i);
			here += p[i];
		}
	if(here >= 1 - eps) return memo[bm >> 1];
	for(int i = 0; i < n; i++)
		memo[bm >> 1][i] = 1/0.;
	for(int i = 0; i < n; i++)
		if((bm >> i) & 1)
			for(int j = 0; j < n; j++)
				if(!((bm >> j) & 1) && adj[i][j] < 100)
					memo[bm >> 1][i] = min(memo[bm >> 1][i], adj[i][j] + (1 - p[j] / (1 - here)) * solve(bm | (1 << j))[j]);
	sort(all.begin(), all.end(), [bm](int i, int j) { return memo[bm >> 1][i] < memo[bm >> 1][j]; });
	dbl sum = 0;
	int ct = 0;
	for(int i = 0; i < n; i++)
		if(!((bm >> i) & 1))
			ct++, sum += solve(bm | (1 << i))[i] * (1 - p[i] / (1 - here));
	for(int i = 0; i < all.size(); i++) {
		dbl val = dbl(n) / (n - (all.size() - i)) * t + (sum / ct);
		//printf("%d / (%d - %d) * %d + (%.2f / %d)\n", n, n, all.size() - i, t, sum, ct);
		//printf("[%d] i %d all[i] %d val %.5f\n", bm, i, all[i], val);
		if(val <= memo[bm >> 1][all[i]] + eps && (!i || val > memo[bm >> 1][all[i - 1]] - eps)) {
			for(; i < all.size(); i++)
				memo[bm >> 1][all[i]] = val;
		} else {
			ct++;
			sum += memo[bm >> 1][all[i]];
		}
	}
	return memo[bm >> 1];
}

int main () {
	int i, m, j, k;
	scanf("%d %d %d", &n, &m, &t);
	for(i = 0; i < n; i++) scanf("%lf", &p[i]);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			adj[i][j] = (i == j? 0 : 100000);
	for(i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		adj[a][b] = adj[b][a] = 1;
	}
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	printf("%.10f\n", double(solve(1)[0]));
}
