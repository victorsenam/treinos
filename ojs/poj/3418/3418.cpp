//#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cctype>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num; const num eps = 0;
// XXX double warnings means there's some specific integer operation (+1, lo<hi, etc...), not precision-related
struct line {
	num a, c;
	bool hi;
	num operator () (num x) const { return a*x*x + (a+a)*x + c; }
	bool operator < (const line & ot) const { return hi?a>ot.a:a<ot.a; } // decreasing slope, if function ties, the smallest in this order is chosen
};
num glx;
bool compare (line & a, const line & o) { return a(glx) > (*((&a)+1))(glx); }
struct envelope { // min envelope, the first element is the best at the beggining
	deque<line> qu; num lo, hi; envelope (num a, num b) : lo(a), hi(b) {}
	inline num inter (line a, line b) { assert(!(b<a)); // first point where b beats (properly) a XXX double
		if (a.a == b.a) return (a.c<b.c)?hi+1:lo;
		long double c = double(b.c-a.c)/double(a.a-b.a);
		long double delta = sqrt(4.*(1-c));
		if (delta != delta) return a.a<b.a?hi+1:lo;
		num p = ll(-1+(a.hi?ceil(delta/2):-ceil(delta/2)));
		num lo = max(this->lo, p-3);
		num hi = min(this->hi, p+3);
		//if (b.a == a.a) return (a.b < b.b)?hi+1:lo;
		//return max(min((b.b - a.b + (b.b-a.b>0)*(a.a-b.a+1))/(a.a - b.a),hi+1),lo);
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
		qu.push_back(l);
	}
	void push_front (line l) { assert(qu.empty() || !(qu.front() < l)); // insert a line that is best at lo or never
		if (!qu.empty() && qu.front()(lo) < l(lo)) return;
		for (num x; qu.size() && l(x = (qu.size()==1?hi:inter(qu[0],qu[1]))) <= qu.front()(x); qu.pop_front()); // XXX double
		qu.push_front(l);
	}
	line pop_front (num lo) { assert(!qu.empty() && this->lo <= lo + eps); // gets best line at this new lo
		for (this->lo = lo; qu.size() > 1 && qu[0](lo) > qu[1](lo); qu.pop_front());
		return qu.front();
	}
	line pop_back (num hi) { assert(!qu.empty() && this->hi >= hi - eps); // gets best line at this new hi
		for (this->hi = hi; qu.size() > 1 && qu[qu.size()-2](hi) <= qu.back()(hi); qu.pop_back());
		return qu.back();
	}
	line get (num x) { assert(!qu.empty() && lo <= x + eps && x <= hi + eps); // gets best line at x
		glx = x;
		return (*lower_bound(qu.begin(),qu.end()-1,qu[0],compare));
	}
};
struct full_envelope {
	vector<envelope> v; full_envelope(envelope c) { v.pb(c); }
	void add (line l) {
		envelope nw(v[0].lo,v[0].hi); nw.push_back(l);
		while (v.size() && v.back().qu.size() <= nw.qu.size()) {
			envelope aux(nw.lo,nw.hi); deque<line>::iterator jt = nw.qu.begin();
			for (int i = 0; i < v.back().qu.size(); i++) {
				line r = v.back().qu[i];
				while (jt != nw.qu.end() && *jt < r) aux.push_back(*(jt++));
				aux.push_back(r);
			}
			while (jt != nw.qu.end()) aux.push_back(*(jt++));
			nw = aux; v.pop_back();
		}
		v.push_back(nw);
	}
	line get (num x) { // you can easily use pop_front and pop_back here
		line b = v.front().get(x);
		for (int i = 1; i < v.size(); i++) {
			line c = v[i].get(x);
			if (c(x)!=b(x)?c(x)<b(x):c<b) b = c;
		}
		return b;
	}
};

void rd (ll & x) {
	char c; x = 0;
	while (isspace(c = getchar()));
	do { x = (x << 8) + (x << 2) + c - '0'; }
	while (isdigit(c = getchar()));
}

void rd (char & c) { while(isspace(c = getchar())); }

int main () {
	ll n;
	rd(n);

	full_envelope low(envelope(-1e6,-1)), high(envelope(0,1e6));
	for (int i = 0; i < n; i++) {
		char q;
		rd(q);
		if (q == 'I') {
			ll a, b, c;
			rd(a); rd(b); rd(c);
			low.add({a,c,0}); high.add({a,c,1});
		} else {
			ll x;
			rd(x);
			if (x < 0) printf("%lld\n", low.get(x)(x));
			else printf("%lld\n", high.get(x)(x));
		}
	}
}
