#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num; const num eps = 0;
// XXX double warnings means there's some specific integer operation (+1, lo<hi, etc...), not precision-related
struct line {
	num a, b;
	num eval (num x) const { return -a*x - b; }
	num operator () (num x) const { return a*x + b; }
	bool operator < (const line & ot) const { return a > ot.a; } // decreasing slope, if function ties, the smallest in this order is chosen
};
ostream & operator << (ostream & os, line o) { return os << "[" << o.a << "x + " << o.b << "]"; }
struct envelope { // min envelope, the first element is the best at the beggining
	deque<line> qu; num lo, hi; envelope (num a, num b) : lo(a), hi(b) {}
	num inter (line a, line b) { assert(!(b<a)); // first point where b beats (properly) a XXX double
		//if (b.a == a.a) return (a.b < b.b)?hi+1:lo;
		//return max(min((b.b - a.b + (b.b-a.b>0)*(a.a-b.a+1))/(a.a - b.a),hi+1),lo);
		num lo = this->lo; num hi = this->hi + 1;
		while (lo < hi) {
			num md = lo + (hi - lo)/2;
			if (a(md) <= b(md)) lo = md+1;
			else hi = md;
		}
		return lo;
	}
	void push_back (line l) { assert(qu.empty() || !(l < qu.back())); // insert a line that is best at hi or never
		if (!qu.empty() && qu.back()(hi) <= l(hi)) return;
		while (qu.size()) {
			num x = (qu.size()==1?lo:inter(qu[qu.size()-2],qu.back()));
			if (l(x) < qu.back()(x)) qu.pop_back();
			else break;
		}
		//for (num x; qu.size() && l(x = (qu.size()==1?lo:inter(qu[qu.size()-2],qu.back()))) < qu.back()(x); qu.pop_back()); // XXX double
		qu.push_back(l);
	}
	line get (num x) { assert(!qu.empty() && lo <= x + eps && x <= hi + eps); // gets best line at x
		return (*lower_bound(qu.begin(),qu.end()-1,qu[0],[x](line & a, const line & o){ return a(x) > (*((&a)+1))(x); }));
	}
};
struct full_envelope {
	vector<envelope> v; full_envelope(envelope c) : v({c}) {}
	void add (line l) {
		envelope nw(v[0].lo,v[0].hi); nw.push_back(l);
		while (v.size() && v.back().qu.size() <= nw.qu.size()) {
			envelope aux(nw.lo,nw.hi); auto jt = nw.qu.begin();
			for (line r : v.back().qu) {
				while (jt != nw.qu.end() && *jt < r) aux.push_back(*(jt++));
				aux.push_back(r);
			}
			while (jt != nw.qu.end()) aux.push_back(*(jt++));
			nw = aux; v.pop_back();
		}
		assert(nw.qu.size());
		v.push_back(nw);
		return;
		cout << "=== " << endl;
		for (int i = 0; i < v.size(); i++) {
			cout << "env " << i;
			for (line r : v[i].qu)
				cout << " " << r;
			cout << endl;
		}
	}
	line get (num x) { // you can easily use pop_front and pop_back here
		line b = v.front().get(x);
		for (int i = 1; i < v.size(); i++) {
			line c = v[i].get(x);
			if (c(x)<b(x)) b = c;
		}
		return b;
	}
};

const int N = 1e6+7;

int n;
ll ia[N], id[N];

full_envelope env(envelope(-1e6-2,1e6+2));
int main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &ia[i], &id[i]);
	env.add({-n-1,0});
	for (int i = n; i >= 1; i--) {
		ll r = env.get(-id[i]).eval(-id[i]) + id[i]*i + ia[i];
		//cout << r << " (" << id[i] << " " << ia[i] << ") " << env.get(-id[i]) << endl;
		env.add({-i,-r});
	}
	printf("%lld\n", env.get(0).eval(0));
}

