#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 8e6+7;
const ll M = 2e18;

int n;
int t; ll l, r;
int sg[N]; // 0 : vazio, 1 : misto, 2 : cheio
int lz[N]; // -1 : nada, 0 : limpa, 1 : inverte, 2 : preenche
ll lf[N], rg[N];
int ch[N][2];
int es;

void create (int & u, ll l, ll r) {
	if (u) return;
	u = ++es;
	lf[u] = l; rg[u] = r;
	sg[u] = 0; lz[u] = -1;
	ch[u][0] = ch[u][1] = 0;
}

void rev (int & u) {
	if (u == -1 || u == 1)
		u = -u;
	else
		u = 2-u;
}

void upd (int u) {
	ll md = lf[u] + (rg[u] - lf[u])/2ll;
	if (lf[u] != rg[u]) { 
		create(ch[u][0], lf[u], md);
		create(ch[u][1], md+1, rg[u]);
	}

	if (lz[u] == 0 || lz[u] == 2) {
		sg[u] = lz[u];
		if (lf[u] != rg[u])
			lz[ch[u][0]] = lz[ch[u][1]] = lz[u];
	} else if (lz[u] == 1) {
		sg[u] = 2 - sg[u];
		if (lf[u] != rg[u]) {
			rev(lz[ch[u][0]]);
			rev(lz[ch[u][1]]);
		}
	}
	lz[u] = -1;
}

void chg (int u, ll l, ll r, int t) {
	upd(u);
	if (r < lf[u] || rg[u] < l) {
		//printf("[%lld,%lld] : %d\n", lf[u], rg[u], sg[u]);
		return;
	} else if (l <= lf[u] && rg[u] <= r) {
		lz[u] = t;
		upd(u);
	} else {
		chg(ch[u][0], l, r, t);
		chg(ch[u][1], l, r, t);
		
		if (sg[ch[u][0]] == sg[ch[u][1]])
			sg[u] = sg[ch[u][0]];
		else
			sg[u] = 1;
	}
	//printf("[%lld,%lld] : %d\n", lf[u], rg[u], sg[u]);
}

ll get (int u) {
	assert(u);
	upd(u);

	//printf("[%lld,%lld] -> %lld\n", lf[u], rg[u], sg[u]);
	if (sg[u] == 0) {
		return lf[u];
	} else if (sg[u] == 2) {
		return M;
	} else {
		ll l = get(ch[u][0]);
		if (l == M) {
			ll r = get(ch[u][1]);
			return r;
		}
		return l;
	}
}

int main () {
	scanf("%d", &n);

	int root = 0;
	create(root, 0, M-1);
	chg(root, 0, 0, 2);
	for (int i = 0; i < n; i++) {
		int t; ll l, r;
		scanf("%d %lld %lld", &t, &l, &r);
		if (t == 1)
			t = 2;
		else if (t == 2)
			t = 0;
		else
			t = 1;
		chg(root, l, r, t);
		printf("%lld\n", get(root));
	}
}
