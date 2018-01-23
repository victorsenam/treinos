#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood; cood eps = 0;
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
	vec c; cood r2;

	inline bool containsp (vec w) { return c.sq(w) < r2; }
	inline bool contains (vec w) { return c.sq(w) <= r2; }
	inline bool has_inter_lin(vec a, vec b) { return a.sq(b) <= eps? contains(a) : sq(c.cross(a, b)) <= r2 * a.sq(b) + eps; }
	inline bool has_inter_seg(vec a, vec b) {
		if(containsp(a) && containsp(b)) return false;
		return has_inter_lin(a, b) && (contains(a) || contains(b) || a.dir(c, b) * b.dir(c, a) != -1);
	}
};

void sim() {
	puts("YES");
	exit(0);
}

void solve(vec P, int n, vec p[], vec Q, int m, vec q[]) {
	for(int i = 0; i < n; i++) {
		vec X = p[i];
		cir C;
		C.c = Q - P + X;
		C.r2 = Q.sq(P);
		for(int j = 0; j < m; j++)
			if(C.has_inter_seg(q[j], q[(j + 1) % m]))
				sim();
	}
}

vec p[112345], q[112345];
int main () {
	int n, m, i;
	vec P, Q;
	scanf("%lld %lld", &P.x, &P.y);
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	scanf("%lld %lld", &Q.x, &Q.y);
	scanf("%d", &m);
	for(i = 0; i < m; i++)
		scanf("%lld %lld", &q[i].x, &q[i].y);
	solve(P, n, p, Q, m, q);
	solve(Q, m, q, P, n, p);
	puts("NO");
}
