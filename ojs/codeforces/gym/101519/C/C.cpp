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

typedef double num;
// XXX double: indicates operations specific to integers, not precision related
template<typename line> struct envelope {
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {}
	void push_back (line l) { // amort. O(inter) | l is best at hi or never
		//if (q.size() && q[q.size()-1].inter(l,lo,hi) > hi + 1e-8) return; // MUDEI
		if (q.size() && q[q.size()-1](hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:q[q.size()-2].inter(q[q.size()-1],lo,hi));
			if (x < q[q.size()-1].inter(l,lo,hi)) break;
		}
		q.push_back(l);
	}
	line get (num x) { // O(lg(R))
		int l, h, md; for (l = 0, h = q.size()-1, md = (l+h)/2; l < h; md = (l+h)/2)
			if (q[md].inter(q[md+1],lo,hi) < x) { l = md+1; } // MUDEI
			//if (q[md](x) > q[md+1](x)) { lo = md+1; }
			else { h = md; }
		return q[l];
	}
};
struct line { // inter = O(1)
	num a,b; num operator () (num x) const { return a*x+b; }
	line () {} line (vec s, vec t) { lin l(s,t); a = num(-l.p.x)/l.p.y; b = num(l.c)/l.p.y; }
	num inter (line o, num lo, num hi) { return min(hi+1,max(lo,floor(num(o.b-b)/num(a-o.a) + 1e-8) + 1)); }
	bool operator < (const line & o) const { return a > o.a; }
};

const int N = 125123;

int n, m, k, ts;
vec v[N];
int seen[N], turn;
line low[N], hig[N];

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)  {
			for (ll * p : {&v[i].x, &v[i].y})
				scanf("%lld", p);
			assert(v[i].y >= 0);
		}
		scanf("%d", &k);
		while (k--) {
			scanf("%d", &m);
			int ls = 0, hs = 0;
			++turn;
			while (m--) {
				int a, b;
				scanf("%d %d", &a, &b);
				a--; b--;
				if (v[a].x < v[b].x) // upper
					hig[hs++] = line(v[a],v[b]);
				else
				{ low[ls++] = line(v[a],v[b]); low[ls-1].a *= -1; low[ls-1].b *= -1; }
			}

			sort(low, low+ls); sort(hig, hig+hs);
			envelope<line> e_low(0, 2e9), e_hig(0, 2e9);
			for (int i = 0; i < ls; i++) e_low.push_back(low[i]);
			for (int i = 0; i < hs; i++) e_hig.push_back(hig[i]);

			for (int i = 0; i < n; i++) {
				double lw = ls?-e_low.get(v[i].x)(v[i].x):-1./0.;
				double hg = hs?e_hig.get(v[i].x)(v[i].x):1./0.;
				//cout << ls << "[" << v[i].y << "]" << hg << ": ";
				if (lw + 1e-6 < v[i].y && v[i].y + 1e-6 < hg)
					printf("%d\n", i+1);
			}
			printf("0\n");
		}
	}
}
