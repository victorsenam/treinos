#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 502;
const int M = 2e4+7;

int n, k;
ll a[N], d[N], c[N];
ll dp[N][M];
ll lvls[30][M];
ll aux[2][M];
ll mx[M];

void add (ll * prev, ll * cur, int i) {
	for (int j = 0; j < M; j++) {
		cur[j] = prev[j];
		if (c[i] <= j && prev[j-c[i]] != LLONG_MAX)
			cur[j] = min(cur[j], prev[j-c[i]] + a[i]*c[i] - (c[i]-1)*c[i]*d[i]/2);
	}
}

void go (int lv, int l, int r, int a, int b) {
	for (int k = a; k <= b; k++) {
		ll * pr = aux[!(k&1)]; ll * nx = aux[k&1];
		if (k == a) pr = lvls[lv-1];
		if (k == b) nx = lvls[lv];
		add(pr,nx,k);
	}
	
	if (l == r) {
		for (int j = 0; j < M; j++) {
			if (j < c[l]) mx[j] = LLONG_MAX;
			dp[l][j] = lvls[lv-1][j];
		}
	} else {
		int md = (l+r)/2;
		go(lv+1, l, md, md+1, r);
		go(lv+1, md+1, r, l, md);
	}
}

int main () {
	scanf("%d %d", &n, &k);
	
	lvls[0][0] = 0;
	for (int i = 1; i < M; i++) lvls[0][i] = LLONG_MAX;

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &a[i], &d[i], &c[i]);
	}

	go(0,i,n-1,0,-1);
}
