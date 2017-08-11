#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double num;
const num eps = 1e-8;

struct line {
	ll a, b;

	num eval (num x) {
		return a*x + b;
	}

	bool operator < (line & ot) {
		return a + eps > ot.a; // lines should have decreasing slope
	}
};

struct envelope {
	deque<line> qu;
	num lo, hi;

	// first point where b beats a
	num inter (line a, line b) {
		assert(!(b < a));
		return num(b.b - a.b)/num(a.a - b.a);
	}

	void push_back (line l) {
		assert(qu.empty() || !(l < qu.back()));

		if (!qu.empty() && qu.back().eval(hi) <= l.eval(hi))
			return;

		while (qu.size() > 1) {
			num x = inter(qu.back(), l);
			if (qu[qu.size()-2].eval(x) <= qu[qu.size()-1].eval(x))
				qu.pop_back();
			else
				break;
		}

		qu.push_back(l);
	}

	line get (num x) {
		assert(!qu.empty() && lo <= x + eps && x <= hi + eps);

		int lo = 0, hi = qu.size() - 1;
		while (lo < hi) {
			int md = lo + (hi - lo)/2;
			if (qu[md].eval(x) <= qu[md+1].eval(x))
				hi = md;
			else
				lo = md+1;
		}

		return qu[lo];
	}
};

const int N = 2e5+7;
int n, m;
envelope env;
ll t[N], f[N];

int main () {
	env.lo = -1e4+2;
	env.hi = 1e4+2;

	cin >> n >> m;

	ll sm = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &t[i]);
		env.push_back(line({-sm, -t[i]}));
		sm += t[i];
	}

	ll res = 0;
	ll acc = 0;
	for (int i = 0; i < m; i++) {
		scanf("%lld", &f[i]);

		ll rs = 0;

		if (!i) {
			res = sm*f[i];
		} else {
			line a = env.get(num(f[i-1]-f[i])/num(f[i-1]));
			rs = max(-a.a*(f[i-1]-f[i]) - a.b*f[i-1], rs);
		}

		acc += rs;
		res = acc + sm*f[i];
		//printf("wait %lld takes %lld res %lld\n", rs, sm*f[i], res);
	}

	printf("%lld\n", res);
}
