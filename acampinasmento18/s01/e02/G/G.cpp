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
	inline bool operator < (vec o) { return (x!=o.x)?x<o.x:y<o.y; }
};
ostream & operator << (ostream & os, vec v) {
	return os << "(" << v.x << "," <<v.y << ")";
}

struct lin {
	cood a, b, c;
	lin () {} lin(cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a*s.x + b*s.y) {}

	vec nor () { return vec(a,b); }

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

inline pair<vec,vec> furt (vec * p, int n, vec d) {
	int s, t;
	if (p[1]*d < p[0]*d) {
		pair<vec,vec> res = furt(p, n, vec(0,0) - d);
		swap(res.first, res.second);
		return res;
	}
	// p[1]*d >= cur
	vec mn = p[0], mx = p[0];

	int lo = 1, hi = n;
	while (lo < hi) {
		int md = (lo+hi+1)/2;
		if (p[md]*d >= p[0]*d) lo = md;
		else hi = md-1;
	}

	int di = lo;

	lo = 1, hi = di-1;
	while (lo < hi) {
		int md = (lo+hi)/2;
		if (p[md]*d < p[md+1]*d) lo = md+1;
		else hi = md;
	}
	if (p[lo]*d >= mx*d) mx = p[lo];

	lo = di, hi = n-1;
	while (lo < hi) {
		int md = (lo+hi)/2;
		if (p[md]*d > p[md+1]*d) lo = md+1;
		else hi = md;
	}
	if (lo < n && p[lo]*d <= mn*d) mn = p[lo];

	return pair<vec,vec>(mn,mx);
}

inline int convex_hull (vec * v, int n, int border_in) {
	swap(v[0], *max_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0],a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	if (border_in) {
		int s = n-1;
		while (s>1 && v[s].ccw(v[s-1],v[0]) == 0) s--;
		for (int i = s; i < n-1-(i-s); i++) swap(v[i], v[n-1-(i-s)]);
	}
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= border_in) s--;
		swap(v[s++], v[i]);
	}
	return s;
}

const int N = 1e5+6;

int n, m;
vec v[N];
vec u[N];

template<typename T>
inline void rd(T &x) {
	char c;
	while(isspace(c = getchar()));
	x = (c - '0');
	while(!isspace(c = getchar()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int main () {
	scanf("%d", &n);
	m = n;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
		u[i] = v[i];
	}
	
	n = convex_hull(v,n,0);

	ll area = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < m; j++) {
			vec l = lin(v[i], v[j]).nor();
			pair<vec,vec> rs = furt(v,n,l);
			vec a = rs.first, b = rs.second;

			if (v[i].cross(a,v[j]) == 0 || v[i].cross(v[j],b) == 0) continue;
			area = max(area,v[i].cross(a,v[j]) + v[i].cross(v[j],b));
		}
	}

	printf("%lld.%lld\n", area/2, (area%2)*5);
}
