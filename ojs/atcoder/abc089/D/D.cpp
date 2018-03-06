#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 303;

int n, m, d, q;
map<int,pii> mp;
int cst[N*N];

int dist (pii a, pii b) { return abs(a.first-b.first) + abs(a.second-b.second); }

int main () {
	scanf("%d %d %d", &n, &m, &d);
	for (int i = 0; i < n; i++) for (int j = 0, x; j < m; j++) { scanf("%d", &x); mp[x] = pii(i,j); }
	scanf("%d", &q);

	for (int i = 1; i <= n*m; i++) { if (i <= d) cst[i] = 0; else cst[i] = cst[i-d] + dist(mp[i],mp[i-d]); }
	while (q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", cst[r] - cst[l]);
	}
}
