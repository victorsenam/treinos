#include <queue>
#include <cstdio>
#include <cassert>
#include <cctype>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num; const num eps = 0; num INF = 1e17;
// XXX double: indicates operations specific to integers (+1,lo<hi,...), non precision-related
template<typename line> struct envelope { // if line is used, the template tag can be simply removed
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {}
	void push_back (line l) { assert(q.empty() || !(l<q.back())); // l is best at hi or never
		if (!q.empty() && q.back()(hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:min(max(lo,next(q.rbegin())->inter(q.back())),hi+1));
			if (l(x) >= q.back()(x)) break;
		}
		q.push_back(l);
	}
	line get (num x) {
		int lo = 0, hi = q.size()-1;
		while (lo < hi) { int md = (lo+hi)/2;
			if (q[md](x) > q[md+1](x)) lo = md+1;
			else hi = md;
		}
		return q[lo];
	}
};
struct line { // change only parameters and () for any viable functions, env operations in amort. O(lg(hi-lo))
	num a,c; envelope<line> * env; num operator () (num x) const { return a*x*x + (a+a)*x + c; }
	line (num _a, num _c, envelope<line> * _env) : a(_a), c(_c), env(_env) {}
	inline bool operator < (const line & ot) const { return (*this)(env->lo) < ot(env->lo) && (*this)(env->hi) > ot(env->hi); } // first element is best at lo
	num inter (line o) { assert(!(o<(*this)));
		num lo = env->lo, hi = env->hi + 1;
		while (lo < hi) {
			num md = lo+(hi-lo)/2;
			if ((*this)(md)<=o(md)) lo = md+1;
			else hi = md;
		}
		return lo;
	}
};
template<typename T> inline T prev (T it) { return --it; }
template<typename T> inline T next (T it) { return ++it; }
template<typename line> struct full_envelope {
	deque<envelope<line> > v; full_envelope(envelope<line> c) {v.pb(c);}
	void add (line l) { // amort. O(lg(n)*inter)
		v.push_back(envelope<line>(v[0].lo,v[0].hi)); v.back().push_back(l);
		while (v.size() > 1 && prev(prev(v.end()))->q.size() <= prev(v.end())->q.size()) {
			deque<line> aux; swap(aux,prev(prev(v.end()))->q);
			typename deque<line>::iterator it = aux.begin();
			typename deque<envelope<line> >::iterator r = prev(prev(v.end()));
			for (unsigned int i = 0; i < v.back().q.size(); i++) { line l = v.back().q[i];
				while (it != aux.end() && *it < l) r->push_back(*(it++));
				r->push_back(l);
			}
			while (it != aux.end()) r->push_back(*(it++));
			v.pop_back();
		}
	}
	line get (num x) { // O(lg(n)^2) use pop_back/pop_front for better time
		line b = v.front().get(x);
		for (int i = 1; i < (int) v.size(); i++) {
			line c = v[i].get(x);
			if (c(x)<b(x)) b = c;
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

	full_envelope<line> low(envelope<line>(-1e6,-1)), high(envelope<line>(0,1e6));
	for (int i = 0; i < n; i++) {
		char q;
		rd(q);
		if (q == 'I') {
			ll a, b, c;
			rd(a); rd(b); rd(c);
			low.add(line(a,c,&low.v[0]));
			high.add(line(a,c,&high.v[0]));
		} else {
			ll x;
			rd(x);
			if (x < 0) printf("%lld\n", low.get(x)(x));
			else printf("%lld\n", high.get(x)(x));
		}
	}
}
