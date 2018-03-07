#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, m;
ll s = 0;
vector<vector<ll> > A;
vector<ll> r[2];

ll get (int a, int b, int c, int d) {
	return 4*s - 2*(r[0][a] + r[0][b] + r[1][c] + r[1][d]) + A[a][c] + A[a][d] + A[b][c] + A[b][d];
}

int main () {
	scanf("%d %d", &n, &m);
	A = vector<vector<ll> >(n, vector<ll>(m));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) { scanf("%lld", &A[i][j]); }

	for (int i = 0; i < n; i++) {
		r[0].pb(0);
		for (int j = 0; j < m; j++) r[0].back() += A[i][j];
		s += r[0].back();
	}
	for (int i = 0; i < m; i++) {
		r[1].pb(0);
		for (int j = 0; j < n; j++) r[1].back() += A[j][i];
	}

	ll res = get(0,n-1,0,m-1);
	for (int i = 1; i < n-1; i++)
		res = max({ res, get(i,n-1,0,m-1), get(0,i,0,m-1) });
	for (int i = 1; i < m-1; i++)
		res = max({ res, get(0,n-1,i,m-1), get(0,n-1,0,i) });

	printf("%lld\n", res);
}
