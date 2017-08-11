#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;
const ll MOD = 1e9+9;

struct node {
	ll sum, f[2];
	int l, r;
} nd[N];
ll a[N];

// 0 : base
// 1 : resposta
// 2 : auxiliar
ll mat[N][3][3];
ll fib[N];

inline ll mod (ll x) {
	return x%MOD;
}

void mult (int a, int b, int c) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				mat[c][i][j] = mod(mat[c][i][j] + mod(mat[a][i][k] * mat[b][k][j]));
}

ll build (int u, int l, int r) {
	nd[u].l = l; nd[u].r = r;
	nd[u].f[0] = nd[u].f[1] = 0;
	if (l == r) {
		return nd[u].sum = a[l];
	} else {
		int md = l + (r - l)/2;
		return nd[u].sum = mod(build(2*u, l, md) + build(2*u+1, md+1, r));
	}
}

void refresh (int u) {
	if (nd[u].f[0] == 0 && nd[u].f[1] == 0) return;
	
	int c = nd[u].r - nd[u].l + 1;
	nd[u].sum = mod(nd[u].sum + mod(nd[u].f[0] * mat[c][2][0]) + mod(nd[u].f[1] * mat[c][2][1]));

	if (nd[u].l != nd[u].r) {
		nd[u+u].f[0] = mod(nd[u+u].f[0] + nd[u].f[0]);
		nd[u+u].f[1] = mod(nd[u+u].f[1] + nd[u].f[1]);

		int c = nd[u+u].r - nd[u+u].l + 1;
		nd[u+u+1].f[0] = mod(nd[u+u+1].f[0] + mod(nd[u].f[0] * mat[c][0][0]) + mod(nd[u].f[1] * mat[c][0][1]));
		nd[u+u+1].f[1] = mod(nd[u+u+1].f[1] + mod(nd[u].f[0] * mat[c][1][0]) + mod(nd[u].f[1] * mat[c][1][1]));
	}

	nd[u].f[0] = nd[u].f[1] = 0;
}

ll get (int u, int l, int r) {
	refresh(u);
	if (l > nd[u].r || nd[u].l > r)
		return 0;
	if (l <= nd[u].l && nd[u].r <= r)
		return nd[u].sum;
	return mod(get(u+u,l,r) + get(u+u+1,l,r));
}

ll upd (int u, int l, int r) {
	refresh(u);
	if (l > nd[u].r || nd[u].l > r)
		return nd[u].sum;
	if (l <= nd[u].l && nd[u].r <= r) {
		nd[u].f[0] = fib[nd[u].l-l+1]; nd[u].f[1] = fib[nd[u].l-l+2];
		refresh(u);
		return nd[u].sum;
	}

	return nd[u].sum = mod(upd(u+u, l, r) + upd(u+u+1, l, r));
}

int n, m;

int main () {
	fib[0] = 0; fib[1] = 1;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			mat[0][i][j] = (i==j);
			mat[1][i][j] = 0;
		}
	mat[1][0][1] = mat[1][1][0] = mat[1][1][1] = mat[1][2][0] = mat[1][2][2] = 1;

	for (int i = 2; i < N; i++) {
		fib[i] = mod(fib[i-1] + fib[i-2]);
		mult(1,i-1,i);
	}

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);

	build(1, 0, n-1);

	for (int i = 0; i < m; i++) {
		int q, l, r;
		scanf("%d %d %d", &q, &l, &r);
		l--; r--;
		if (q == 1)
			upd(1, l, r);
		else
			printf("%lld\n", get(1, l, r));
	}
}
