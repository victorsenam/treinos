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
	num operator () (num x) const { return a*x + b; }
	bool operator < (const line & ot) const { return a > ot.a; } // decreasing slope, if function ties, the smallest in this order is chosen
};
struct envelope { // min envelope, the first element is the best at the beggining
	deque<line> qu; num lo, hi; envelope (num a, num b) : lo(a), hi(b) {}
	num inter (line a, line b) { assert(!(b<a)); // first point where b beats (properly) a XXX double
		//if (b.a == a.a) return (a.b < b.b)?hi+1:lo;
		//return max(min((b.b - a.b + (b.b-a.b>0)*(a.a-b.a-1))/(a.a - b.a),hi+1),lo);
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
		for (num x; qu.size() && l(x = (qu.size()==1?lo:inter(qu[qu.size()-2],qu.back()))) < qu.back()(x); qu.pop_back()); // XXX double
		/*
		num x;
		while (qu.size()) {
			num x = (qu.size()==1?lo:inter(qu[qu.size()-2],qu.back()));
			if (qu.back()(x) <= l(x)) break;
			qu.pop_back();
		}
		*/
		qu.push_back(l);
	}
	line get (num x) { assert(!qu.empty() && lo <= x + eps && x <= hi + eps); // gets best line at x
		return (*lower_bound(qu.begin(),qu.end()-1,qu[0],[x](line & a, const line & o){ return a(x) > (*((&a)+1))(x); }));
	}
};
struct full_envelope {
	vector<envelope> v; full_envelope(envelope c) {v.pb(c);}; full_envelope() {};
	int siz;
	void add (line l) {
		siz++;
		envelope nw(v[0].lo,v[0].hi); nw.push_back(l);
		while (v.size() && v.back().qu.size() <= nw.qu.size()) {
			envelope aux(nw.lo,nw.hi); auto jt = nw.qu.begin();
			for (line r : v.back().qu) {
				for (; jt != nw.qu.end() && *jt < r; ++jt) aux.pb(*jt);
				aux.push_back(r);
			}
			for (; jt != nw.qu.end(); ++jt) aux.pb(*jt);
			nw = aux; v.pop_back();
		}
		v.push_back(nw);
	}
	line get (num x) { // you can easily use pop_front and pop_back here
		assert(v.size() > 0);
		line b = v.front().get(x);
		for (int i = 1; i < v.size(); i++) {
			line c = v[i].get(x);
			if (c(x)<b(x)) b = c;
		}
		return b;
	}
};

int n;
full_envelope env;
int main () {
	scanf("%d", &n);
	env = full_envelope(envelope(0,1e6));
	env.v.front().hi += 2;
	env.add({0,0});
	for (int i = 1; i <= n; i++) {
		ll a, d;
		scanf("%lld %lld", &a, &d);
		line w = env.get(i);
		ll r = -w(i);
		//printf("%d : %lldx + %lld : %lld : %lld\n", i, -w.a, -w.b, -w.a*(n+1)-w.b, r);
		env.add({d,-a-r-d*ll(i)});
	}
	printf("%lld\n", -env.get(n+1)(n+1));
}
