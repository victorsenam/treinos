#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;
ll a[N];
int ls[N];
int n, m;
int qr[N][2];
int mx[4*N];
int p[7], ps;
map<ll, vector<int> > mp;
map<ll, vector<int> >::iterator it[(1<<7)];


void factor (ll x) {
	ps = 0;
	for (ll i = 2; i*i <= x; i+= 1 + (i&1)) {
		if (x%i == 0)
			p[ps++] = i;
		while (x%i == 0)
			x /= i;
	}
	if (x != 1)
		p[ps++] = x;
}

ll build (int u, int l, int r) {
	if (l == r) {
		return mx[u] = ls[l];
	} else {
		int md = (l+r)/2;
		return mx[u] = max(build(u+u, l, md), build(u+u+1, md+1, r));
	}
}

ll get (int u, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) return 0;
	if (ql <= l && r <= qr) return mx[u];
	int md = (l+r)/2;
	return max(get(u+u, l, md, ql, qr), get(u+u+1, md+1, r, ql, qr));
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		factor(a[i]);

		for (int ms = 1; ms < (1<<(ps)); ms++) {
			ll x = 1;
			for (int i = 0; i < ps; i++)
				if (ms&(1<<i))
					x *= p[i];
			mp[x].pb(i);
			it[ms] = mp.find(x);
		}

		int lo = 0, hi = i-1;
		while (lo < hi) {
			int md = (lo+hi)/2;
			
			ll qt = i - md;
			for (int ms = 1; ms < (1<<(ps)); ms++) {
				ll x = 1;
				for (int i = 0; i < ps; i++)
					if (ms&(1<<i))
						x *= p[i];
				vector<int> & v = it[ms]->second;
				ll s = v.end() - upper_bound(v.begin(), v.end(), md);

				if (__builtin_popcount(ms)&1)
					qt -= s;
				else
					qt += s;
			}

			if (qt)
				lo = md + 1;
			else
				hi = md;
		}

		ls[i] = lo;
		cout << lo << " ";
	}
	cout << endl;

	build(1, 0, n);

	for (int i = 0; i < m; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		if (get(1, 0, n, l, r) >= l)
			printf("S\n");
		else
			printf("N\n");
	}
}
