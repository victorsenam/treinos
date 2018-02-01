#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, m, k;

const int M = 312345 * 4;
ll tr[M];

void add(int i, int l, int r, int ql, int qr, ll x) {
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		tr[i] += x;
		//if(tr[j] > 1.01e9) tr[j] = 1.01e9;
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
}

inline ll get(int i, int l, int r, int x) {
	ll ans = 0;
	while(i) {
		ans += tr[i];
		if(l == r) break;
		int m = (l + r) / 2;
		if(x <= m) i = 2 * i, r = m;
		else i = 2 * i + 1, l = m + 1;
	}
	return ans;

	//if(i == 0) return 0;
	//if(l == r) return tr[i];
	//int m = (l + r) / 2;
	//if(x <= m) return tr[i] + get(L[i], l, m, x);
	//else return tr[i] + get(R[i], m + 1, r, x);
}


char c;
template<typename T> inline void rd(T &x) {
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

const int N = 312345;
vector<int> from[N];

int ans[N], l[N], r[N], a[N], p[N], seg[N];

void solve(int ql, int qr, const vector<int> &v) {
	if(v.empty()) return;
	//printf("solve(%d, %d,", ql, qr);
	//for(int i : v) printf(" %d", i);
	//printf(")\n");
	if(ql == qr) {
		for(int i : v) ans[i] = ql;
		return;
	}
	int qm = (ql + qr) / 2;
	for(int i = ql; i <= qm; i++) {
		if(l[i] <= r[i]) add(1, 1, m, l[i], r[i], a[i]);
		else {
			add(1, 1, m, l[i], m, a[i]);
			add(1, 1, m, 1, r[i], a[i]);
		}
	}
	vector<int> L, R;
	for(int i : v) {
		ll tot = 0;
		for(int j : from[i]) {
			tot += get(1, 1, m, j);
			if(tot >= p[i])
				break;
		}
		if(tot >= p[i]) L.pb(i);
		else {
			R.pb(i);
			p[i] -= tot;
		}
	}
	for(int i = ql; i <= qm; i++) {
		if(l[i] <= r[i]) add(1, 1, m, l[i], r[i], -a[i]);
		else {
			add(1, 1, m, l[i], m, -a[i]);
			add(1, 1, m, 1, r[i], -a[i]);
		}
	}
	solve(ql, qm, L);
	solve(qm + 1, qr, R);
}

int main () {
	int i;
	rd(n); rd(m);
	for(i = 1; i <= m; i++) {
		int x;
		rd(x);
		from[x].pb(i);
	}
	for(i = 1; i <= n; i++)
		rd(p[i]);
	rd(k);
	for(i = 1; i <= k; i++) {
		rd(l[i]); rd(r[i]); rd(a[i]);
	}
	vector<int> all;
	for(i = 1; i <= n; i++) all.pb(i);
	solve(1, k + 1, all);
	for(i = 1; i <= n; i++)
		if(ans[i] == k + 1)
			puts("NIE");
		else
			printf("%d\n", ans[i]);
}
