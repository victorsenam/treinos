#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct line {
	ll a, b;
	int c;

	inline ll eval (ll x) {
		return a*x + b;
	}

	bool operator < (const line & ot) const { return a > ot.a; }
};

struct envelope {
	deque<line> qu;
	ll lo, hi;
	
	inline ll inter (line & a, line & b) {
		if (b.a == a.a) { 
			if (a.b < b.b) return this->hi+1;
			else return this->lo;
		}
		return (b.b - a.b + a.a - b.a + 1)/(a.a - b.a);
	}

	inline void push_back (line l) {
		assert(qu.empty() || !(l < qu.back()));

		if (!qu.empty() && qu.back().eval(hi) <= l.eval(hi))
			return;

		while (qu.size() > 1) {
			ll x = inter(qu.back(),l);
			if (qu[qu.size()-2].eval(x) <= qu[qu.size()-1].eval(x))
				qu.pop_back();
			else
				break;
		}
		qu.push_back(l);
	}

	inline line get (ll x) {
		assert(!qu.empty() && lo <= x && x <= hi);
		int lo = 0, hi = qu.size() - 1;
		while (lo < hi) {
			int md = lo + (hi-lo)/2;
			if (qu[md].eval(x) <= qu[md+1].eval(x))
				hi = md;
			else
				lo = md+1;
		}
		return qu[lo];
	}
};

const int N = 1e5+7;
const int M = 300;

int n, q;
envelope en[20];
line cb[N];
ll vl[20];
ll ks[M];

template<class T> inline void rd (T & x) {
	char c;
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int main () {
	rd(n); rd(q);

	for (int i = 1; i <= 15; i++) { en[i].lo = 1, en[i].hi = 1e6; }
	for (int i = 0; i < n; i++) {
		rd(cb[i].c); rd(cb[i].b); rd(cb[i].a);
		cb[i].b -= cb[i].a;
	}
	sort(cb, cb+n);
	for (int i = 0; i < n; i++)
		en[cb[i].c].push_back(cb[i]);

	for (int i = 0; i < q; i++) {
		int m, d;
		rd(m); rd(d);

		for (int j = 15; j >= 1; j--) {
			if (j < 15) vl[j] = vl[j+1];
			else vl[j] = LLONG_MAX;

			if (en[j].qu.size()) vl[j] = min(vl[j],en[j].get(d).eval(d));
			//cout << j << ":  " << vl[j] << endl;
		}

		if (m < M) ks[m] = 0;
		for (int j = min(M-1,m-1); j >= 0; j--) {
			ks[j] = LLONG_MAX;
			for (int k = 1; k <= 15; k++) {
				if (vl[k] == LLONG_MAX) continue;
				ks[j] = min(ks[j], ll((m-j+k-1)/k)*vl[k]);
				if (j + k < M && j + k <= m) ks[j] = min(ks[j], vl[k] + ks[j+k]);
			}
		}

		printf("%lld\n", ks[0]);
	}
}
