#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-6; // risky: XXX, untested: TODO
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
	int i;
	lin () {} lin (vec a, cood b) : p(a), c(b) {}
	lin (vec s, vec t, int _i) : p((s-t).rot90()), c(p*s), i(_i) {}
	inline lin parll (vec v) { return lin(p,v*p); }
	inline lin perp () { return lin(p.rot90(),c); }
	inline double inter (lin o) {  cood d = (p^o.p); return double(c*o.p.y - p.y*o.c)/d; }
	bool contains (vec v) { return abs(p*v - c) <= eps; }
	inline double at_x (cood x) { return double(c-p.x*x)/p.y; }
	double sign_dist (vec v) { return double(p*v - c)/p.nr(); }
}; //$
struct cir { // circle
	vec c; cood r;
	cir () {} cir (vec v, cood d) : c(v), r(d) {}
	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; } // border included
	inline bool border (vec w) { return abs(c.sq(w) - sq(r)) <= eps; }
	inline bool has_inter (cir o) { return c.sq(o.c) <= sq(r + o.r) + eps; } // borders included
	inline bool has_border_inter (cir o) { return has_inter(o) && c.sq(o.c) + eps >= sq(r - o.r); }
	inline bool has_inter_lin (vec a, vec b) { return a.sq(b) <= eps ? contains(a) : sq(c.cross(a,b)) <= sq(r)*a.sq(b) + eps; } // borders included XXX overflow
	inline bool has_inter_seg (vec a, vec b) { return has_inter_lin(a,b) && (contains(a) || contains(b) || a.dir(c,b)*b.dir(c,a) != -1); } // borders and tips included XXX overflow
	inline double arc_area (vec a, vec b) { return c.angle(a,b)*r*r/2; } // smallest arc, ccw positive
	inline double arc_len (vec a, vec b) { return c.angle(a,b)*r; } // smallest arc, ccw positive
	pair<vec,vec> tan (vec v) { // XXX low precision
		if (contains(v) && !border(v)) throw 0;
		cood d2 = c.sq(v); double s = sqrt(d2 - r*r); s = (s==s)?s:0;
		double al = atan2(r,s); vec t = (~(c-v));
		return pair<vec,vec>(v + t.rotate(al)*s, v + t.rotate(-al)*s);
	}
	pair<vec,vec> border_inter (cir o) {
		if (!has_border_inter(o) || o.c == (*this).c) throw 0;
		double a = (sq(r) + o.c.sq(c) - sq(o.r))/(2*o.c.nr(c));
		vec v = (o.c - c)/o.c.nr(c); vec m = c + v * a;
		double h = sqrt(sq(r) - sq(a)); h = h!=h?0:h;
		return pair<vec,vec>(m + v.rot90()*h, m - v.rot90()*h);
	}
	pair<vec,vec> border_inter_lin (vec a, vec b) { // first is closest to a than second
		if (a.sq(b) <= eps) { if (border(a)) return pair<vec,vec>(a,a); throw 0; }
		if (a.dir(b,c) == -1) swap(a,b);
		if (!has_inter_lin(a,b)) throw 0;
		double d2 = c.dist2_lin(a,b); vec p = (b-a)/a.nr(b);
		double h = sqrt(r*r - d2); h = h!=h?0:h; 
		double y = sqrt(c.sq(a) - d2); y = y!=y?0:y;
		return pair<vec,vec>(a + p*(y-h), a + p*(y+h));
	}
	double triang_inter (vec a, vec b) { // ccw oriented, this with (c,a,b)
		if (c.sq(a) > c.sq(b)) return -triang_inter(b,a);
		if (contains(b)) return c.cross(a,b)/2;
		if (!has_inter_seg(a,b)) return arc_area(a,b);
		pair<vec,vec> itr = border_inter_lin(b,a); // order important
		if (contains(a)) return c.cross(a,itr.first)/2 + arc_area(itr.first,b);
		return arc_area(a,itr.second) + c.cross(itr.second,itr.first)/2 + arc_area(itr.first,b);
	}
}; //$
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b)) return true;
	return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}
double dist2_seg (vec a, vec b, vec c, vec d){return inter_seg(a,b,c,d)?0.:min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) });}

typedef double num;

const int N = 200123;

template<typename T> struct DQ {
	T * q; int qi, qf; DQ () { }
	int size() { return qf - qi; }
	T operator [] (int i) { return q[qi+i]; }
	void push_back (T x) { q[qf++] = x; }
	void pop_back () { qf--; }
};

template<typename line> struct envelope {
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) { }
	void push_back (line l) { // amort. O(inter) | l is best at hi or never
		if (q.size() && q[q.size()-1](hi - eps) < l(hi - eps) + eps) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:q[q.size()-2].inter(q[q.size()-1],lo,hi));
			if (l(x - eps) > q[q.size()-1](x - eps) + eps) break;
		}
		q.push_back(l);
	}
};
struct line { // inter = O(lg(R))
	vec a, b; lin ln, rev; inline num operator () (num x) const { return lin(ln).at_x(x); }
	inline num inter (line o, num lo, num hi) { // first point where o strictly beats this
		if (vec(0,0).ccw(ln.p,o.ln.p) == 0) return ((*this)(lo)<=o(lo)?hi+1:lo);
		return ln.inter(o.ln);
	}
};


int ts;
int n;
line l[N];

ostream & operator << (ostream & os, vec o) { return os << "(" << o.x << " " << o.y << ")"; }

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &l[i].a.x, &l[i].a.y);
			scanf("%lf %lf", &l[i].b.x, &l[i].b.y);
			if (l[i].a.x > l[i].b.x) swap(l[i].a, l[i].b);
			l[i].ln = lin(l[i].a,l[i].b,i);
			l[i].a.y *= -1; l[i].b.y *= -1;
			l[i].rev = lin(l[i].a,l[i].b,i);
			l[i].a.y *= -1; l[i].b.y *= -1;
		}
		double lo,hi;
		scanf("%lf %lf", &lo, &hi);
		if (hi < lo) swap(lo,hi);
		for (int nn = n, i = n = 0; i < nn; i++) {
			double val = l[i](lo) + l[i](hi);
			if (!isnan(val) && !isinf(val))
				l[n++] = l[i];
		}
		sort(l, l+n, [] (line & a, line & b) { return ((a.b-a.a)^(b.b-b.a)) < -eps; });
		if (n == 0) { printf("0\n"); continue; }
		double lm[2], rs[2];
		for (int k = 0; k < 2; k++) {
			lm[k] = rs[k] = 0;
			if (k) {
				reverse(l, l+n);
				for (int i = 0; i < n; i++) swap(l[i].ln,l[i].rev);
			}
			envelope<line> env(lo,hi);
			for (int i = 0; i < n; i++) { env.push_back(l[i]); }
			lm[k] = min(env.q[0](lo), env.q[env.q.size()-1](hi));
			double ls = lo;
			for (int i = 0; i < env.q.size(); i++) {
				//cout << env.v[0].q[i].ln.i << endl;
				double nx = (i == env.q.size()-1)?hi:env.q[i].inter(env.q[i+1],lo,hi);
				double h = env.q[i]((ls+nx)/2) - lm[k];
				rs[k] += h*(nx-ls);
				ls = nx;
			}
		}
		printf("%.20f\n", (hi-lo)*abs(lm[0]+lm[1]) - rs[0] - rs[1]);
	}
}
