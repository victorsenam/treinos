#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood; cood eps = 0; // risky: XXX, untested: TODO
const double pi = acos(-1.);
template<typename T> inline T sq(T x) { return x*x; }
struct vec {
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y - o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y + o.y}; }
	inline vec operator * (cood o) { return {x * o, y * o}; }
	inline vec operator / (cood o) { return {x / o, y / o}; }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }
	inline cood cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a||(this)b|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a||(this)b|cos(angle)
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); } //$
	inline vec operator ~ () { return (*this)/nr(); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); } // projects this onto line ab
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)$
	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	double dist2_lin (vec a, vec b) { return a.sq(b) <= eps ? sq(a) : double(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	double dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
	inline bool operator == (const vec & o) const { return abs(x-o.x) <= eps && abs(y-o.y) <= eps; }
	inline bool operator < (const vec & o) const { return (abs(x-o.x)>eps)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle strict compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties, this is the first
	bool compare (vec a, vec b) { 
		if ((*this < a) != (*this < b)) return *this < b;
		int o = ccw(a,b); return o?o>0:((a == *this && !(a == b)) || a.dir(*this,b) < 0);
	}
}; //$
struct lin { // line
	vec p; cood c; // p*(x,y) = c
	lin () {} lin (vec a, cood b) : p(a), c(b) {}
	lin (vec s, vec t) : p((s-t).rot90()), c(p*s) {}
	inline lin parll (vec v) { return lin(p,v*p); }
	inline lin perp () { return lin(p.rot90(),c); }
	vec inter (lin o) { if (vec(0,0).ccw(p,o.p) == 0) throw 1; cood d = (p^o.p); return vec((c*o.p.y - p.y*o.c)/d,(o.c*p.x - o.p.x*c)/d); }
	bool contains (vec v) { return abs(p*v - c) <= eps; }
	vec at_x (cood x) { return vec(x,(c-p.x*x)/p.y); }
	vec at_y (cood y) { return vec((c-y*p.y)/p.x,y); }
	double sign_dist (vec v) { return double(p*v - c)/p.nr(); }
}; //$
typedef double num; num env_eps;
// XXX double: indicates operations specific to integers, not precision related
template<typename line> struct envelope {
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {}
	void push_back (line l) { // amort. O(inter) | l is best at hi or never
		if (q.size() && q.back().inter(l,lo,hi) > hi + env_eps) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:q[q.size()-2].inter(q[q.size()-1],lo,hi));
			if (q.back().inter(l,lo,hi) > x + env_eps) break;
		}
		q.push_back(l);
	}
	line get (num x) { // O(lg(R))
		int lo, hi, md; for (lo = 0, hi = q.size()-1, md = (lo+hi)/2; lo < hi; md = (lo+hi)/2)
			if (q[md](x) > q[md+1](x)) { lo = md+1; }
			else { hi = md; }
		return q[lo];
	}
};
struct segm {
	vec s, t; lin l;
	num operator () (num x) const { return num(l.c-l.p.x*x)/l.p.y; }
	num inter (segm o, num lo, num hi) {
		ll d = (l.p^o.l.p);
		if (d == 0) { if (s.y < o(s.x)) return hi+1; else return lo; }
		return min(hi+1,max(num(l.c*o.l.p.y - l.p.y*o.l.c)/d,lo));
	}
};

const int N = 125123;
int n, k, m;

vec v[N];
int b[N], turn;

ostream & operator << (ostream & os, vec o) { return os << "(" << o.x << " " << o.y << ")"; }
ostream & operator << (ostream & os, segm o) { return os << o.s << o.t; }

int main () {
	int ts;
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &v[i].x, &v[i].y);
		}
		scanf("%d", &k);
		while (k--) {
			scanf("%d", &m);
			envelope<segm> e_lo(INT_MIN+3,INT_MAX-3), e_hi(INT_MIN+3,INT_MAX-3);
			vector<segm> s_lo, s_hi;
			++turn;
			for (int i = 0; i < m; i++) {
				int a, b;
				scanf("%d %d", &a, &b);
				a--; b--;
				::b[a] = ::b[b] = turn;
				segm cur; cur.s = v[a]; cur.t = v[b]; cur.l = lin(cur.s,cur.t);
				if (cur.s.x < cur.t.x)
					s_hi.pb(cur);
				else if (cur.s.x > cur.t.x) {
					cur.s = vec(0,0) - cur.s; cur.t = vec(0,0) - cur.t; cur.l = lin(cur.s,cur.t);
					s_lo.pb(cur);
				}
			}
			sort(s_lo.begin(), s_lo.end(), [] (segm a, segm b) { return ((a.t-a.s)^(b.t-b.s)) < 0; });
			sort(s_hi.begin(), s_hi.end(), [] (segm a, segm b) { return ((a.t-a.s)^(b.t-b.s)) < 0; });

			//cout << "low:";
			for (segm s : s_lo) { e_lo.push_back(s); }
			//cout << endl << "hi:";
			for (segm s : s_hi) { e_hi.push_back(s); }
			//cout << endl;

			for (int i = 0; i < n; i++) {
				if (b[i] == turn) continue;
				double lw = 1./0., hg = 1./0.;
				if (e_hi.q.size()) hg = e_hi.get(v[i].x)(v[i].x);
				if (e_lo.q.size()) lw = e_lo.get(-v[i].x)(-v[i].x);
				//cout << "at " << v[i].x << ": " << -lw << " " << hg << endl;
				if (-lw + env_eps < v[i].y && v[i].y + env_eps < hg) printf("%d\n", i+1);
			}
			printf("0\n");
		}
		//printf("\n");
	}
}
