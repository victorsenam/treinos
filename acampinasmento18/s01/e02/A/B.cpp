#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }

struct vec {
	cood x, y;
	vec () : x(0),y(0) {} vec(cood a, cood b) : x(a),y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y-o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y+o.y}; }
	inline vec operator * (cood o) { return {x*o, y*o}; }
	inline vec operator / (cood o) { return {x/o, y/o}; }
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }

	inline cood cross(vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner(vec a, vec b) { return ((*this)-a)*((*this)-b); }
	inline double angle(vec a, vec b) { return atan2(cross(a, b), inner(a, b)); }


	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline vec rot90 () { return vec(-y,x); }

	inline bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; }
};
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c,d) || b.in_seg(c,d) || c.in_seg(a,b) || d.in_seg(a,b)) return true;
	return (c.ccw(a,b) * d.ccw(a,b) == -1 && a.ccw(c,d) * b.ccw(c,d) == -1);
}

struct lin {
	cood a, b, c;
	lin () {} lin(cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a*s.x + b*s.y) {}

	vec inter (lin o) {
		cood d = a*o.b - o.a*b;
		if (-eps <= d && d <= eps) throw 1;
		return vec((o.b*c - b*o.c)/d, (a*o.c - o.a*c)/d);
	}
};

struct cir {
	vec c; cood r;
	cir () {} cir(vec v, cood d) : c(v), r(d) {}
	cir (vec u, vec v, vec w) {
		vec mv = (u+v)/2; lin s(mv, mv+(v-u).rot90());
		vec mw = (u+w)/2; lin t(mw, mw+(w-u).rot90());
		c = s.inter(t); r = c.nr(u);
	}

	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; }
	inline double arc_len(vec a, vec b) { return c.angle(a, b) * r; }
};

cir min_spanning_circle (vec * v, int n) {
	srand(time(NULL)); random_shuffle(v, v+n); cir c(vec(),0);
	for (int i = 0; i < n; i++) if (!c.contains(v[i])) {
		c = cir(v[i],0);
		for (int j = 0; j < i; j++) if (!c.contains(v[j])) {
			c = cir((v[i]+v[j])/2, v[i].nr(v[j])/2);
			for (int k = 0; k < j; k++) if (!c.contains(v[k])) {
				c = cir(v[i],v[j],v[k]);
			}
		}
	}
	return c;
}

vec a, b, c, d, s;

bool inside (double t, vec c) {
	int d = c.ccw(a,b);
	if (d != c.ccw(b,b+s*t)) return 0;
	if (d != c.ccw(b+s*t,a+s*t)) return 0;
	if (d != c.ccw(a+s*t,a)) return 0;
	return 1;
}
bool solve (double t) {
	if (inter_seg(a,b,c,d) || inter_seg(a,a+s*t,c,d) || inter_seg(b,b+s*t,c,d) || inter_seg(a+s*t,b+s*t,c,d)) return 1;
	if (inside(t,c) || inside(t,d)) return 1;
	return 0;
}

void fail () {
	printf("-1\n");
	exit(0);
}

double ans = 1/0.;

void go(vec v) {
	vec p = v.proj(a, b);
	double ang = a.angle(a + s, b);
	double sa = sin(ang);
	double d = v.nr(p) / sa;
	ans = min(ans, d / s.nr());
}

int main () {
	vec t;
	scanf("%lf %lf", &a.x, &a.y);
	scanf("%lf %lf", &b.x, &b.y);
	scanf("%lf %lf", &c.x, &c.y);
	scanf("%lf %lf", &d.x, &d.y);
	scanf("%lf %lf", &s.x, &s.y);
	scanf("%lf %lf", &t.x, &t.y);
	if (s.sq(t) <= eps) fail();
	s = s - t;

	bool ok = 0;
	for (vec w : {c,d}) {
		if (w.ccw(a,b) == (a+s).ccw(a,b)) {
			if (w.ccw(a,a+s) == 0 || w.ccw(b,b+s) == 0 || w.ccw(a,a+s) == -w.ccw(b,b+s))
				go(w);
		}
	}
	if (inter_seg(a,a+s*3e4,c,d)) go(lin(a, a + s * 3e4).inter(lin(c, d)));
	if (inter_seg(b,b+s*3e4,c,d)) go(lin(b, b + s * 3e4).inter(lin(c, d)));
	if(ans > 1e10) fail();
	printf("%.20f\n", ans);
}
