#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, m, k;

const int M = 4500000;
int tr[M]; int L[M], R[M], en = 1;
inline int cp(int i) {
	tr[en] = tr[i];
	L[en] = L[i];
	R[en] = R[i];
	assert(en < M);
	return en++;
}

int add(int i, int l, int r, int ql, int qr, ll x) {
	if(l > qr || r < ql) return i;
	int j = cp(i);
	if(l >= ql && r <= qr) {
		tr[j] += x;
		if(tr[j] > 1.01e9) tr[j] = 1.01e9;
		return j;
	}
	int m = (l + r) / 2;
	L[j] = add(L[j], l, m, ql, qr, x);
	R[j] = add(R[j], m + 1, r, ql, qr, x);
	return j;
}

inline ll get(int i, int l, int r, int x) {
	ll ans = 0;
	while(i) {
		ans += tr[i];
		if(l == r) break;
		int m = (l + r) / 2;
		if(x <= m) i = L[i], r = m;
		else i = R[i], l = m + 1;
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

const int N = 300009;
const int T = 30;
vector<int> from[N];

int acc[N], l[N], r[N], a[N], p[N], seg[N];

int solve1(int i) {
	memset(acc, 0, sizeof acc);
	for(int j : from[i])
		acc[j] = 1;
	for(int j = 1; j <= m; j++)
		acc[j] += acc[j - 1];
	ll tot = 0;
	for(int q = 1; q <= k; q++) {
		ll oc;
		if(l[q] <= r[q]) oc = acc[r[q]] - acc[l[q] - 1];
		else oc = (acc[m] - acc[l[q] - 1]) + (acc[r[q]] - acc[0]);
		tot += oc * a[q];
		if(tot >= p[i]) return q;
	}
	return -1;
}

inline bool ok(int i, int k) {
	ll tot = 0;
	for(int j : from[i]) {
		tot += get(seg[k], 1, m, j);
		if(tot >= p[i]) return true;
	}
	return false;
}


int solve2(int i) {
	int l = 1, r = k + 1;
	while(l < r) {
		int m = (l + r) / 2;
		if(ok(i, m)) r = m;
		else l = m + 1;
	}
	if(l == k + 1) return -1;
	else return l;
}

inline void aa(int x) {
	if(x == -1) puts("NIE");
	else printf("%d\n", x);
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
	seg[0] = 0;
	for(i = 1; i <= k; i++) {
		rd(l[i]); rd(r[i]); rd(a[i]);
		if(l[i] <= r[i])
			seg[i] = add(seg[i - 1], 1, m, l[i], r[i], a[i]);
		else {
			seg[i] = add(seg[i - 1], 1, m, l[i], m, a[i]);
			seg[i] = add(seg[i], 1, m, 1, r[i], a[i]);
		}
	}
	for(i = 1; i <= n; i++)
		if(from[i].size() > T)
			aa(solve1(i));
		else
			aa(solve2(i));
}
