#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-6;
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

	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline vec rot90 () { return vec(-y,x); }

	inline double angle(vec a, vec b) { return atan2(cross(a, b), inner(a, b)); }
	double dist2_lin(vec a, vec b) { return a.sq(b) <= eps? sq(a) : double(::sq(cross(a, b))) / a.sq(b); }
	double dist2_seg(vec a, vec b) { return a.dir((*this), b) == (b.dir((*this), a)) ? dist2_lin(a, b) : min(sq(a), sq(b)); }
};

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

vec scale(vec A, double x=1) {
	return A * (x / A.nr());
}

vector<vec> tang(vec A, cir C) {
	double d = A.nr(C.c);
	double alp = asin(C.r / d);
	vector<vec> ans;
	double x = sqrt(d * d - C.r * C.r);
	ans.pb(scale(C.c - A, x).rotate(alp) + A);
	ans.pb(scale(C.c - A, x).rotate(-alp) + A);
	return ans;
}

int main () {
	vec A, B;
	cir C;
	scanf("%lf %lf %lf %lf", &A.x, &A.y, &B.x, &B.y);
	scanf("%lf %lf %lf", &C.c.x, &C.c.y, &C.r);
	if(C.c.dist2_seg(A, B) >= C.r * C.r) { // eps? no
		printf("%.12f\n", A.nr(B));
		return 0;
	}
	vector<vec> tA = tang(A, C);
	vector<vec> tB = tang(B, C);
	double ans = 1/0.;
	for(vec ta : tA)
		for(vec tb : tB) {
			double cur = A.nr(ta) + tb.nr(B);
			cur += abs(C.arc_len(ta, tb));
			ans = min(ans, cur);
		}
	printf("%.12f\n", ans);
}
