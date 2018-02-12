#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int es;
int l[N], r[N];
int ch[N][2];
ll sum[N], lz[N];

void refresh (int u) {
	sum[u] += lz[u]*(r[u] - l[u] + 1);
	if (l[u] != r[u]) {
		if (!ch[u][0]) {
			ch[u][0] = es++; l[ch[u][0]] = l[u]; r[ch[u][0]] = (l[u]+r[u])/2; sum[ch[u][0]] = lz[ch[u][0]] = 0;
			ch[u][1] = es++; l[ch[u][1]] = r[ch[u][0]]+1; r[ch[u][1]] = r[u]; sum[ch[u][1]] = lz[ch[u][1]] = 0;
		}
		lz[ch[u][0]] += lz[u]; lz[ch[u][1]] += lz[u];
	}
	lz[u] = 0;
}

ll add (int u, int ql, int qr, ll x) {
	refresh(u);
	if (r[u] < ql || qr < l[u]) return sum[u];
	if (ql <= l[u] && r[u] <= qr) {
		lz[u] += x;
		refresh(u);
		return sum[u];
	}
	return sum[u] = add(ch[u][0], ql, qr, x) + add(ch[u][1], ql, qr, x);
}

ll get (int u, int ql, int qr) {
	if (!u) return 0;
	refresh(u);
	if (r[u] < ql || qr < l[u]) return 0;
	if (ql <= l[u] && r[u] <= qr) return sum[u];
	return get(ch[u][0], ql, qr) + get(ch[u][1], ql, qr);
}

int main () {
	es = 2;
	int qs, n;
	scanf("%d %d", &n, &qs);
	l[1] = 0; r[1] = n-1;
	while (qs--) {
		int q, l, r;
		scanf("%d %d %d", &q, &l, &r);
		if (q == 0) printf("%lld\n", get(1, l, r));
		else { int x; scanf("%d", &x); add(1, l, r, x); }
	}
}
