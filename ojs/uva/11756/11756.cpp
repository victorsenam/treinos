#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8; cood inf = 1./0.; // risky: XXX, untested: TODO
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

typedef double num; num INF = 1./0.;
// XXX double: indicates operations specific to integers (+1,lo<hi,...), non precision-related
template<typename line> struct envelope { // if line is used, the template tag can be simply removed
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {} envelope () {}
	void push_front (line l) { assert(q.empty() || !(q.front()<l)); // l is best at lo or never
		if (!q.empty() && q.front()(lo) < l(lo)) return;
		for (num x; q.size(); q.pop_front()) {
			x = (q.size()<=1?hi:min(max(lo,q.front().inter(*next(q.begin()))-1),hi+1));
			if (l(x) > q.front()(x)) break;
		}
		q.push_front(l);
	}
	void push_back (line l) { assert(q.empty() || !(l<q.back())); // l is best at hi or never
		if (!q.empty() && q.back()(hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:min(max(lo,next(q.rbegin())->inter(q.back())),hi+1));
			if (l(x) >= q.back()(x)) break;
		}
		q.push_back(l);
	}
	void pop_front (num _lo) { assert(lo<=_lo+eps); for(lo=_lo;q.size()>1&&q.front()(lo)>(*next(q.begin()))(lo);q.pop_front()); } // always amort. O(1)
	void pop_back (num _hi) { assert(hi>=_hi-eps); for(hi=_hi;q.size()>1&&(*next(q.rbegin()))(hi)<=q.back()(hi);q.pop_back()); } // always amort. O(1)
	line get (num x) {
		int lo = 0, hi = q.size()-1;
		while (lo < hi) { int md = (lo+hi)/2;
			if (q[md](x) > q[md+1](x)) lo = md+1;
			else hi = md;
		}
		return q[lo];
	}
};
struct generic_line { // change only parameters and () for any viable functions, env operations in amort. O(lg(hi-lo))
	lin l; int i; envelope<generic_line> * env; num operator () (num x) const { return lin(l).at_x(x).y; }
	bool operator < (const generic_line & ot) const { return i < ot.i; } // first element is best at lo
	num inter (generic_line o) { assert(!(o<(*this)));
		if (vec(0,0).ccw(l.p,o.l.p) == 0) return (*this)(env->lo) - eps <= o(env->lo)?env->hi+1:env->lo;
		return l.inter(o.l).x;
	}
};

const int N = 100123;

int ts;
int n;
generic_line ln[N];
vector<vec> v[N];
envelope<generic_line> env;

ostream & operator << (ostream & os, vec o) { return os << "(" << o.x << " " << o.y << ")"; }
ostream & operator << (ostream & os, lin o) { return os << "[" << o.p.x << "x + " << o.p.y << "y = " << o.c << "]"; }

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			v[i] = vector<vec>(2);
			for (int k = 0; k < 2; k++)
				scanf("%lf %lf", &v[i][k].x, &v[i][k].y);
			if (abs(v[i][0].x-v[i][1].x) <= eps) {
				i--; n--;
				continue;
			} else if (v[i][0].x > v[i][1].x) swap(v[i][0],v[i][1]);
		}
		sort(v, v+n, [] (vector<vec> a, vector<vec> b) { return ((a[1]-a[0])^(b[1]-b[0])) < -eps; });
		for (int i = 0; i < n; i++) {
			ln[i].env = &env;
			ln[i].l = lin(v[i][0],v[i][1]);
			//cout << ln[i].l << ": " << v[i][0] << " " << v[i][1] << endl;
			ln[i].i = i;
		}
		if (n == 0) {
			printf("0\n");
			continue;
		}
		scanf("%lf %lf", &env.lo, &env.hi);
		double lm[2], rr[2];
		for (int k = 0; k < 2; k++) {
			lm[k] = rr[k] = 0;
			env.q.clear();
			sort(ln, ln+n);
			for (int i = 0; i < n; i++) env.push_back(ln[i]);

			lm[k] = min(env.q.front()(env.lo),env.q.back()(env.hi));
			//cout << "boundary: " << lm[k] << endl;
			double ls = env.lo;
			for (int i = 0; i < env.q.size(); i++) {
				double x = env.hi;
				if (i + 1 < env.q.size())
					x = env.q[i].inter(env.q[i+1]);
				double h = env.q[i]((x+ls)/2) - lm[k];
				//cout << env.q[i].l << "[" << ls << "," << x << "] height " << h << endl;
				rr[k] += h*(x-ls);
				ls = x;
			}
			
			for (int i = 0; i < n; i++) {
				for (int k = 0; k < 2; k++)
					v[i][k].y = -v[i][k].y;
				ln[i].l = lin(v[i][0],v[i][1]);
				ln[i].i = -ln[i].i;
			}
		}
		
		printf("%.20f\n", -(lm[0]+lm[1])*(env.hi-env.lo) - rr[0] - rr[1]);
	}
}
